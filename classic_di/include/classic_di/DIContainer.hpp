#ifndef DI_CONTAINER_HPP_
#define DI_CONTAINER_HPP_

#include <unordered_map>
#include <functional>
#include <vector>
#include <typeindex>
#include <memory>
#include <tuple>

#include <iostream>

#include "FunctionTypeTraits.hpp"

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
        print_transient_deps();


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

    void print_transient_deps() const
    {
        std::cout << "Transient Dependencies: ";
        for (auto& [a, b] : transient_dependency_creators_)
        {
            std::cout << a.name() << ' ';
        }
        std::cout << std::endl;
    }

private: // Producers for builder
    template<typename Dependency>
    SingletonCreator produce_singleton_creator() const
    {
        return []() {
            static Dependency instance{};
            return &instance;
        };
    }



    template<typename Dependency>
    TransientCreator produce_transient_creator() const
    {
        return [this]() {
            auto creator_args_pack = TypeTraits::ParamPackOf<decltype(Dependency::create)>{};
            auto resolved_creator_args = ResolveCreatorArgs(creator_args_pack);
            std::cout << "TUPLE SIZEE = " << std::tuple_size_v<decltype(resolved_creator_args)> << std::endl;
            return nullptr;//std::apply(std::make_shared<Dependency>, resolved_creator_args);
        };
    }

    std::tuple<> ResolveCreatorArgs(TypeTraits::pack<>) const
    {
        return std::make_tuple();
    }

    template<typename Dependency, typename... OtherDependencies>
    std::tuple<Dependency, OtherDependencies...> ResolveCreatorArgs(TypeTraits::pack<Dependency, OtherDependencies...>) const
    {
        return ResolveCreatorArgsImpl<Dependency>
            (
                TypeTraits::pack<>{},
                TypeTraits::pack<OtherDependencies...>{},
                std::tuple<>{}
            );
    }

    template
    <
        typename Dependency,
        typename... AccumulatedDependencies, template<typename...> typename AccumulatedDependenciesPack,
        typename... OtherDependencies, template<typename...> typename OtherDependenciesPack
    >
    std::tuple<Dependency, OtherDependencies...> ResolveCreatorArgsImpl
    (
        AccumulatedDependenciesPack<AccumulatedDependencies...> accumulated_dependencies_pack,
        OtherDependenciesPack<OtherDependencies...> other_dependencies_pack,
        std::tuple<AccumulatedDependencies...>&& accumulated_result
    ) const
    {
        std::cout << "CURRENT DEPENDENCY: " << typeid(Dependency).name() << std::endl;
        std::tuple<Dependency> resolved_dependency = std::make_tuple(resolve<Dependency>());
        auto concatenated_accumulator = std::tuple_cat(accumulated_result, std::move(resolved_dependency));

        if constexpr (sizeof...(OtherDependencies) > 0)
        {
            return ResolveCreatorArgsImpl<OtherDependencies...>(std::move(concatenated_accumulator));
        }
        else
        {
            return std::move(concatenated_accumulator);
        }
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

private:
    DIContainer() = default;
    friend DIContainerBuilder;

private:
    SingletonDependenciesMap singleton_dependencies_;
    TransientDependenciesMap transient_dependency_creators_;
    mutable std::vector<std::shared_ptr<void>> transient_instances;
};

#endif //DI_CONTAINER_HPP_