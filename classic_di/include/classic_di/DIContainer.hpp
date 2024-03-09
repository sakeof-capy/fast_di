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
    using SingletonCreator = std::function<void*()>;
    using TransientCreator = std::function<std::shared_ptr<void>()>;
    using TagsMappingSingletonVec = std::vector<std::pair<Tag, SingletonCreator>>;
    using TagsMappingTransientVec = std::vector<std::pair<Tag, TransientCreator>>;
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
        using Creator = typename VecType::value_type::second_type;

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
                return tag_pair.first == tag;
            }
        );

        if (found_tagged_pair != found_mapping_vec.cend())
        {
            const Creator& found_creator = found_tagged_pair->second;

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
    Dependency& create_singleton(const std::function<void*()>& creator) const
    {
        void* ptr_to_singleton = creator();
        return *static_cast<Dependency*>(ptr_to_singleton);
    }

    template<typename Dependency>
    Dependency& create_transient(const std::function<std::shared_ptr<void>()>& creator) const
    {
        std::shared_ptr<void>& ptr_to_transient = transient_instances.emplace_back(creator());
        return *std::static_pointer_cast<Dependency>(ptr_to_transient);
    }

private: // Producers for builder
    template<typename Dependency>
    SingletonCreator produce_singleton_creator() const
    {
        return [this]() {
            auto creator_args_pack = TypeTraits::ParamPackOf<decltype(Dependency::create)>{};
            auto resolved_creator_args = ResolveCreatorArgs(creator_args_pack);
            static Dependency instance = std::apply(Dependency::create, resolved_creator_args);
            return &instance;
        };
    }

    template<typename Dependency>
    TransientCreator produce_transient_creator() const
    {
        return [this]() {
            auto creator_args_pack = TypeTraits::ParamPackOf<decltype(Dependency::create)>{};
            auto resolved_creator_args = ResolveCreatorArgs(creator_args_pack);
            return std::make_shared<Dependency>(std::apply(Dependency::create, resolved_creator_args));
        };
    }

    template<typename... ArgTypes>
    auto ResolveCreatorArgs(TypeTraits::pack<ArgTypes...>) const
    {
        return TypeTraits::map_to_tuple(TypeTraits::pack<ArgTypes...>{}, [this]<typename Arg>() -> Arg& {
            return resolve<std::remove_reference_t<Arg>>();
        });
    }

private: // Map fillers for builder
    void add_singleton_dependency(std::type_index dependency_key, SingletonCreator&& creator, Tag tag)
    {
        if (tag_exists(singleton_dependencies_, dependency_key, tag))
        {
            throw std::runtime_error(std::string("Tag Already Exists."));
        }
        std::cout << "Registered singleton tag = " << tag << std::endl;
        singleton_dependencies_[dependency_key].emplace_back( tag, std::move(creator));
    }

    void add_transient_dependency(std::type_index dependency_key, TransientCreator&& creator, Tag tag)
    {
        if (tag_exists(singleton_dependencies_, dependency_key, tag))
        {
            throw std::runtime_error(std::string("Tag Already Exists."));
        }
        std::cout << "Registered transient tag = " << tag << std::endl;
        transient_dependency_creators_[dependency_key].emplace_back( tag, std::move(creator));
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
                return tag_pair.first == tag;
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

private:
    static constexpr Tag DEFAULT_TAG = "DEFAULT_TAG";
};

#endif //DI_CONTAINER_HPP_