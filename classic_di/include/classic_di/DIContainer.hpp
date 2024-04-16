#ifndef DI_CONTAINER_HPP_
#define DI_CONTAINER_HPP_

#include <unordered_map>
#include <functional>
#include <vector>
#include <typeindex>
#include <memory>
#include <string>
#include <stdexcept>
#include <tuple>

#include "type_traits/FunctionTypeTraits.hpp"
#include "type_traits/TypeLists.hpp"



#include <iostream>

class DIContainerBuilder;

class DIContainer
{
private:
    using Tag = std::string_view;
    using SingletonCreator = std::function<void*(const DIContainer&)>;
    using TransientCreator = std::function<std::shared_ptr<void>(const DIContainer&)>;
    using TagsMappingSingletonVec = std::vector<std::tuple<Tag, SingletonCreator, std::type_index>>;
    using TagsMappingTransientVec = std::vector<std::tuple<Tag, TransientCreator, std::type_index>>;
    using SingletonDependenciesMap = std::unordered_map<std::type_index, TagsMappingSingletonVec>;
    using TransientDependenciesMap = std::unordered_map<std::type_index, TagsMappingTransientVec>;

public:
    template<typename Dependency>
    Dependency& resolve(Tag tag = DEFAULT_TAG) const
    {
        static_assert(!std::is_reference_v<Dependency>, "Cannot resolve a reference type.");
        return resolve_impl<Dependency>(tag);
    }

private:
    template<typename Dependency>
    Dependency& resolve_impl(Tag tag) const
    {
        std::string error_message = "Non-registered dependency: " +
                std::string(typeid(Dependency).name()) + " with tag: " + std::string(tag) + ":\n\t";

        try
        {
            return resolve_in<Dependency>(singleton_dependencies_, tag);
        }
        catch (const std::runtime_error& err)
        {
            error_message += err.what();
            error_message += "\n\t";
        }

        try
        {
            return resolve_in<Dependency>(transient_dependency_creators_, tag);
        }
        catch (const std::runtime_error& err)
        {
            error_message += err.what();
        }

        throw std::runtime_error(error_message);
    }

    template<typename Dependency, typename DependenciesMap>
    Dependency& resolve_in(DependenciesMap& dependencies_map, Tag tag) const
    {
        using MapIteratorType = typename DependenciesMap::const_iterator;
        using VecType = typename DependenciesMap::value_type::second_type;
        using VecIteratorType = typename VecType::const_iterator;
        using Creator = std::tuple_element_t<1, typename VecType::value_type>;

        MapIteratorType found_dependency_pair = dependencies_map.find(typeid(Dependency));

        if (found_dependency_pair == dependencies_map.cend())
        {
            throw std::runtime_error(std::string("Dependency not found in ") + typeid(DependenciesMap).name());
        }

        const VecType& found_mapping_vec = found_dependency_pair->second;
        VecIteratorType found_tagged_pair = std::find_if(
            found_mapping_vec.cbegin(),
            found_mapping_vec.cend(),
            [tag](const typename VecType::value_type& tag_pair) {
                return std::get<0>(tag_pair) == tag;
            }
        );

        if (found_tagged_pair != found_mapping_vec.cend())
        {
            const Creator& found_creator = std::get<1>(*found_tagged_pair);

            if constexpr (std::same_as<Creator, SingletonCreator>)
            {
                return create_singleton<Dependency>(found_creator);
            }
            else
            {
                return create_transient<Dependency>(found_creator);
            }
        }

        throw std::runtime_error(std::string("Dependency not found in ") + typeid(DependenciesMap).name());
    }

    template<typename Dependency>
    Dependency& create_singleton(const SingletonCreator& creator) const
    {
        void* ptr_to_singleton = creator(*this);
        return cast_to<Dependency>(ptr_to_singleton);
    }

    template<typename Dependency>
    Dependency& create_transient(const TransientCreator& creator) const
    {
        std::shared_ptr<void>& ptr_to_transient = transient_instances.emplace_back(creator(*this));
        return cast_to<Dependency>(ptr_to_transient);
    }

private: // Producers for builder
    template<typename Dependency>
    SingletonCreator produce_singleton_creator(std::vector<Tag>&& dependency_tags) const
    {
        return [dependency_tags = std::move(dependency_tags)](const DIContainer& self) mutable {
            auto creator_args_pack = TypeTraits::ParamPackOf<decltype(Dependency::create)>{};
            auto resolved_creator_args = self.resolve_creator_args(creator_args_pack, std::move(dependency_tags));
            static Dependency instance = std::apply(Dependency::create, resolved_creator_args);
            return &instance;
        };
    }

    template<typename Dependency>
    TransientCreator produce_transient_creator(std::vector<Tag>&& dependency_tags) const
    {
        return [dependency_tags = std::move(dependency_tags)](const DIContainer& self) mutable {
            auto creator_args_pack = TypeTraits::ParamPackOf<decltype(Dependency::create)>{};
            auto resolved_creator_args = self.resolve_creator_args(creator_args_pack, std::move(dependency_tags));
            return std::make_shared<Dependency>(std::apply(Dependency::create, resolved_creator_args));
        };
    }

    template<typename... ArgTypes>
    auto resolve_creator_args(TypeTraits::pack<ArgTypes...>, std::vector<Tag>&& dependency_tags) const
    {
        auto dependency_tag_iterator = dependency_tags.cbegin();
        return TypeTraits::map_to_tuple
        (
            TypeTraits::pack<ArgTypes...>{},
            [this, &dependency_tag_iterator]<typename Arg>() -> Arg& {
                Tag dependency_tag = *dependency_tag_iterator;
                Arg& resolved = resolve<std::remove_reference_t<Arg>>(dependency_tag);
                ++dependency_tag_iterator;
                return resolved;
            }
        );
    }

private: // Map fillers for builder
    void add_singleton_dependency
    (
        std::type_index interface_key,
        SingletonCreator&& creator,
        Tag tag,
        std::type_index dependency_key
    )
    {
        if (tag_exists(singleton_dependencies_, interface_key, tag))
        {
            throw std::runtime_error(std::string("Tag Already Exists."));
        }
        std::cout << "Registered singleton tag = " << tag << std::endl;
        singleton_dependencies_[interface_key].emplace_back(tag, std::move(creator), dependency_key);
    }

    void add_transient_dependency
    (
        std::type_index interface_key,
        TransientCreator&& creator,
        Tag tag,
        std::type_index dependency_key
    )
    {
        if (tag_exists(singleton_dependencies_, interface_key, tag))
        {
            throw std::runtime_error(std::string("Tag Already Exists."));
        }
        std::cout << "Registered transient tag = " << tag << std::endl;
        transient_dependency_creators_[interface_key].emplace_back( tag, std::move(creator), dependency_key);
    }

    template<typename Interceptor>
    void add_interceptor(std::type_index decoratee_type)
    {
        std::string error_message = "Interception error:\n\t";

        try
        {
            return add_interceptor_to_map<Interceptor>(singleton_dependencies_, decoratee_type);
        }
        catch (const std::runtime_error& err)
        {
            error_message += err.what();
            error_message += "\n\t";
        }

        try
        {
            return add_interceptor_to_map<Interceptor>(transient_dependency_creators_, decoratee_type);
        }
        catch (const std::runtime_error& err)
        {
            error_message += err.what();
        }

        throw std::runtime_error(error_message);
    }

    template<typename Interceptor, typename DependenciesMap>
    void add_interceptor_to_map(DependenciesMap& dependencies_map, std::type_index decoratee_type)
    {
        using MapIteratorType = typename DependenciesMap::iterator;
        using VecType = typename DependenciesMap::value_type::second_type;
        using Creator = std::tuple_element_t<1, typename VecType::value_type>;
        using DecorateeType = TypeTraits::head_of_pack<TypeTraits::ParamPackOf<decltype(Interceptor::create)>>;

        MapIteratorType found_dependency_pair = dependencies_map.find(decoratee_type);

        if (found_dependency_pair != dependencies_map.end())
        {
            VecType& tags_mapping_vec = found_dependency_pair->second;
            for (auto& [tag, creator, type_index] : tags_mapping_vec)
            {
                creator = [&creator](const DIContainer& self) {
                    //return Interceptor { cast_to<DecorateeType>(creator(self)) };
                    return creator(self);
                };
            }
        }
        else
        {
            for (auto& [interface_type_index, tags_mapping_vec] : dependencies_map)
            {
                for (auto& [tag, creator, type_index] : tags_mapping_vec)
                {
                    if (type_index == decoratee_type)
                    {
                        creator = [&creator](const DIContainer& self) {
                            //return Interceptor { cast_to<DecorateeType>(creator(self)) };
                            return creator(self);
                        };
                    }
                }
            }
        }

        throw std::runtime_error("Decoratee to intercept not found!");
    }

    template<typename Interceptor, typename Decoratee>
    SingletonCreator decorate(SingletonCreator& creator)
    {
//        return [&creator](const DIContainer& self) {
//            void* decoratee_ptr = creator(self);
//            Decoratee& decoratee = cast_to<Decoratee>(decoratee_ptr);
//            Interceptor
//        };
        return creator;
    }

    template<typename Interceptor, typename Decoratee>
    TransientCreator decorate(TransientCreator& creator)
    {
        return [&creator](const DIContainer& self) {
            std::shared_ptr<void> decoratee_ptr = creator(self);
            Decoratee& decoratee = cast_to<Decoratee>(decoratee_ptr);
            return std::make_shared<Interceptor>()
        };
    }

    template<typename To>
    static To& cast_to(void* ptr)
    {
        return *static_cast<To*>(ptr);
    }

    template<typename To>
    static To& cast_to(std::shared_ptr<void>& ptr)
    {
        return *std::static_pointer_cast<To>(ptr);
    }

    template<typename DependenciesMap>
    bool tag_exists(const DependenciesMap& dependencies_map, std::type_index dependency_key, Tag tag) const
    {
        using MapIterator = typename DependenciesMap::const_iterator;
        using VecType = typename DependenciesMap::value_type::second_type;
        using VecIteratorType = typename VecType::const_iterator;

        const MapIterator found_dependency_pair = dependencies_map.find(dependency_key);

        if (found_dependency_pair == dependencies_map.cend())
        {
            return false;
        }

        const VecType& found_tags_vector = found_dependency_pair->second;
        const VecIteratorType found_tagged_pair = std::find_if(
            found_tags_vector.cbegin(),
            found_tags_vector.cend(),
            [tag](const typename VecType::value_type& tag_pair) {
                return std::get<0>(tag_pair) == tag;
            }
        );

        return found_tagged_pair != found_tags_vector.cend();
    }

public:
    DIContainer() = default;
    friend DIContainerBuilder;

private:
    SingletonDependenciesMap singleton_dependencies_;
    TransientDependenciesMap transient_dependency_creators_;
    mutable std::vector<std::shared_ptr<void>> transient_instances;

public:
    static constexpr Tag DEFAULT_TAG = "DEFAULT_TAG";
};

#endif //DI_CONTAINER_HPP_