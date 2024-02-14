#include <unordered_map>
#include <functional>
#include <vector>
#include <typeindex>
#include <memory>

#include "DIContainer.hpp"

#include <iostream>

class DIContainerBuilder
{
private:
    using SingletonDependenciesMap = std::unordered_map<std::type_index, std::function<void*()>>;
    using TransientDependenciesMap = std::unordered_map<std::type_index, std::function<std::shared_ptr<void>()>>;

public:

    template<typename Dependency, typename Interface = Dependency>
    decltype(auto) register_singleton() &&
    {
        return register_singleton_impl<Dependency, Interface>(std::move(*this));
    }

    template<typename Dependency, typename Interface = Dependency>
    decltype(auto) register_singleton() &
    {
        return register_singleton_impl<Dependency, Interface>(*this);
    }

    template<typename Dependency, typename Interface = Dependency>
    decltype(auto) register_transient() &
    {
        return register_transient_impl<Dependency, Interface>(*this);
    }

    template<typename Dependency, typename Interface = Dependency>
    decltype(auto) register_transient() &&
    {
        return register_transient_impl<Dependency, Interface>(std::move(*this));
    }

    DIContainer build() &&
    {
        return DIContainer { std::move(singleton_dependencies_),
                             std::move(transient_dependency_creators_) };
    }

    DIContainer build() &
    {
        SingletonDependenciesMap singleton_dependencies { singleton_dependencies_ };
        TransientDependenciesMap transient_dependency_creators { transient_dependency_creators_ };
        return DIContainer { std::move(singleton_dependencies),
                             std::move(transient_dependency_creators) };
    }

private:

    template<typename Dependency, typename Interface, typename Self>
    Self&& register_singleton_impl(Self&& self)
    {
        self.singleton_dependencies_[std::type_index(typeid(Interface))] = []() {
            static Dependency instance{};
            return &instance;
        };
        return std::forward<Self>(self);
    }

    template<typename Dependency, typename Interface, typename Self>
    Self&& register_transient_impl(Self&& self)
    {
        self.transient_dependency_creators_[std::type_index(typeid(Interface))] = []() {
            return std::make_shared<Dependency>();
        };
        return std::forward<Self>(self);
    }

private:
    SingletonDependenciesMap singleton_dependencies_;
    TransientDependenciesMap transient_dependency_creators_;
};