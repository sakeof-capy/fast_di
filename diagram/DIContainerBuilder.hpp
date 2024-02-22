#ifndef DI_CONTAINER_BUILDER_HPP_
#define DI_CONTAINER_BUILDER_HPP_

#include <unordered_map>
#include <functional>
#include <vector>
#include <typeindex>
#include <memory>

#include <iostream>

#include "DIContainer.hpp"

class DIContainerBuilder
{
public:
    DIContainerBuilder() : container_ { std::make_unique<DIContainer>() } {}

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

    std::unique_ptr<DIContainer> build() &&
    {
        std::unique_ptr<DIContainer> built_container = std::move(container_);
        container_ = std::make_unique<DIContainer>();
        return built_container;
    }

    std::unique_ptr<DIContainer>  build() &
    {
        return std::make_unique<DIContainer>(*container_);
    }

private:
    template<typename Dependency, typename Interface, typename Self>
    Self&& register_singleton_impl(Self&& self)
    {
        self.container_->add_singleton_dependency(typeid(Interface), container_->produce_singleton_creator<Dependency>());
        return std::forward<Self>(self);
    }

    template<typename Dependency, typename Interface, typename Self>
    Self&& register_transient_impl(Self&& self)
    {
        self.container_->add_transient_dependency(typeid(Interface), container_->produce_transient_creator<Dependency>());
        return std::forward<Self>(self);
    }

private:
    std::unique_ptr<DIContainer> container_;
};

#endif //DI_CONTAINER_BUILDER_HPP_