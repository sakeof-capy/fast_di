#ifndef DI_CONTAINER_HPP_
#define DI_CONTAINER_HPP_

#include <unordered_map>
#include <functional>
#include <vector>
#include <typeindex>
#include <memory>
#include <tuple>

#include "type_traits/FunctionTypeTraits.hpp"
#include "type_traits/TypeLists.hpp"

class DIContainerBuilder;

class DIContainer
{
private:
    using SingletonCreator = std::function<void*()>;
    using TransientCreator = std::function<std::shared_ptr<void>()>;
    using SingletonDependenciesMap = std::unordered_map<std::type_index, SingletonCreator>;
    using TransientDependenciesMap = std::unordered_map<std::type_index, TransientCreator>;

private:
    template<typename Dependency>
    Dependency& resolve_singleton(const std::function<void*()>& creator) const
    {
        void* ptr_to_singleton = creator();
        return *static_cast<Dependency*>(ptr_to_singleton);
    }

    template<typename Dependency>
    Dependency& resolve_transient(const std::function<std::shared_ptr<void>()>& creator) const
    {
        std::shared_ptr<void>& ptr_to_transient = transient_instances.emplace_back(creator());
        return *std::static_pointer_cast<Dependency>(ptr_to_transient);
    }

public:
    template<typename Dependency>
    Dependency& resolve() const
    {
        static_assert(!std::is_reference_v<Dependency>, "Cannot resolve a reference type.");
        return resolve_impl<Dependency>();
    }

private:
    template<typename Dependency>
    Dependency& resolve_impl() const
    {
        auto found = singleton_dependencies_.find(typeid(Dependency));
        if (found != singleton_dependencies_.cend())
        {
            return resolve_singleton<Dependency>(found->second);
        }

        auto transient_found = transient_dependency_creators_.find(typeid(Dependency));
        if (transient_found != transient_dependency_creators_.cend())
        {
            return resolve_transient<Dependency>(transient_found->second);
        }

        throw std::runtime_error("Non-registered dependency.");
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
    void add_singleton_dependency(std::type_index dependency_key, SingletonCreator&& producer)
    {
        singleton_dependencies_[dependency_key] = std::move(producer);
    }

    void add_transient_dependency(std::type_index dependency_key, TransientCreator&& creator)
    {
        transient_dependency_creators_[dependency_key] = std::move(creator);
    }

public:
    DIContainer() = default;
    friend DIContainerBuilder;

private:
    SingletonDependenciesMap singleton_dependencies_;
    TransientDependenciesMap transient_dependency_creators_;
    mutable std::vector<std::shared_ptr<void>> transient_instances;
};

#endif //DI_CONTAINER_HPP_