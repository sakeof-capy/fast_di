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
    using Tag = const char*;
    using SingletonCreator = std::function<void*()>;
    using TransientCreator = std::function<std::shared_ptr<void>()>;
    using SingletonDependenciesMap = std::unordered_map<std::type_index, std::pair<Tag, SingletonCreator>>;
    using TransientDependenciesMap = std::unordered_map<std::type_index, std::pair<Tag, TransientCreator>>;

private:
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
        auto found = singleton_dependencies_.find(typeid(Dependency));
        Tag found_tag = found->second.first;
        if (found != singleton_dependencies_.cend() && found_tag == tag)
        {
            const SingletonCreator& found_creator = found->second.second;
            std::cout << "HEREHERE" << std::endl;
            return create_singleton<Dependency>(found_creator);
        }

        auto transient_found = transient_dependency_creators_.find(typeid(Dependency));
        Tag transient_found_tag = transient_found->second.first;
        if (transient_found != transient_dependency_creators_.cend() && transient_found_tag == tag)
        {
            const TransientCreator& found_creator = transient_found->second.second;
            return create_transient<Dependency>(found_creator);
        }

        throw std::runtime_error("BPODSKFPSD");

//        std::string error_message = "Non-registered dependency: " + std::string(typeid(Dependency).name()) + ":\n\t";
//
//        try
//        {
//            return resolve_in<Dependency>(singleton_dependencies_, tag);
//        }
//        catch (const std::runtime_error& err)
//        {
//            error_message += err.what();
//            error_message += "\n\t";
//        }
//
//        try
//        {
//            return resolve_in<Dependency>(transient_dependency_creators_, tag);
//        }
//        catch (const std::runtime_error& err)
//        {
//            error_message += err.what();
//        }
//
//        throw std::runtime_error(error_message);
    }

    template<typename Dependency, typename DependenciesMap>
    Dependency& resolve_in(DependenciesMap& dependencies_map, Tag tag) const
    {
        using IteratorType = typename DependenciesMap::const_iterator;
        using Creator = typename DependenciesMap::value_type::second_type::second_type;

        IteratorType found = dependencies_map.find(typeid(Dependency));
        Tag found_tag = found->second.first;

        if (found != dependencies_map.cend() && found_tag == tag)
        {
            const Creator& found_creator = found->second.second;

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
            std::cout << "BEFORE4" << std::endl;
            return resolve<std::remove_reference_t<Arg>>();
        });
    }

private: // Map fillers for builder
    void add_singleton_dependency(std::type_index dependency_key, SingletonCreator&& producer, Tag tag = DEFAULT_TAG)
    {
        singleton_dependencies_[dependency_key] = { tag, std::move(producer) };
    }

    void add_transient_dependency(std::type_index dependency_key, TransientCreator&& creator, Tag tag = DEFAULT_TAG)
    {
        transient_dependency_creators_[dependency_key] = { tag, std::move(creator)};
    }

public:
    DIContainer() = default;
    friend DIContainerBuilder;

private:
    SingletonDependenciesMap singleton_dependencies_;
    TransientDependenciesMap transient_dependency_creators_;
    mutable std::vector<std::shared_ptr<void>> transient_instances;

private:
    static constexpr Tag DEFAULT_TAG = "";
};

#endif //DI_CONTAINER_HPP_