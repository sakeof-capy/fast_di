#ifndef DI_CONTAINER_BUILDER_HPP_
#define DI_CONTAINER_BUILDER_HPP_

#include <unordered_map>
#include <functional>
#include <vector>
#include <typeindex>
#include <memory>
#include "DIContainer.hpp"

class DIContainerBuilder
{
private:
    using SingletonCreator = DIContainer::SingletonCreator;
    using TransientCreator = DIContainer::TransientCreator;

public:
    DIContainerBuilder() : container_ { std::make_unique<DIContainer>() } {}

public:
    template<typename Dependency, typename Interface = Dependency>
    auto&& register_singleton_params_deduced() &&
    {
        return register_singleton_with_auto_creator<Dependency, Interface>(std::move(*this));
    }

    template<typename Dependency, typename Interface = Dependency>
    auto&& register_singleton_params_deduced() &
    {
        return register_singleton_with_auto_creator<Dependency, Interface>(*this);
    }

    template<typename Dependency, typename Interface = Dependency>
    auto&& register_transient_params_deduced() &
    {
        return register_transient_with_auto_creator<Dependency, Interface>(*this);
    }

    template<typename Dependency, typename Interface = Dependency>
    auto&& register_transient_params_deduced() &&
    {
        return register_transient_with_auto_creator<Dependency, Interface>(std::move(*this));
    }

    std::unique_ptr<DIContainer> build() &&
    {
        std::unique_ptr<DIContainer> built_container = std::move(container_);
        container_ = std::make_unique<DIContainer>();
        return built_container;
    }

    std::unique_ptr<DIContainer> build() &
    {
        return std::make_unique<DIContainer>(*container_);
    }

private:
    template<typename Dependency, typename Interface, typename Self>
    static Self&& register_singleton_with_auto_creator(Self&& self)
    {
        return register_singleton_with_creator<Interface>
        (
            std::forward<Self>(self),
            self.container_->template produce_singleton_auto_creator<Dependency>()
        );
    }

    template<typename Dependency, typename Interface, typename Self>
    static Self&& register_transient_with_auto_creator(Self&& self)
    {
        return register_transient_with_creator<Interface>
        (
            std::forward<Self>(self),
            self.container_->template produce_transient_auto_creator<Dependency>()
        );
    }

private:
    template<typename Interface, typename Self>
    static Self&& register_singleton_with_creator(Self&& self, SingletonCreator&& creator)
    {
        self.container_->add_singleton_dependency(typeid(Interface), std::move(creator));
        return std::forward<Self>(self);
    }

    template<typename Interface, typename Self>
    static Self&& register_transient_with_creator(Self&& self, TransientCreator&& creator)
    {
        self.container_->add_transient_dependency(typeid(Interface), std::move(creator));
        return std::forward<Self>(self);
    }

private:
    std::unique_ptr<DIContainer> container_;
};

#endif //DI_CONTAINER_BUILDER_HPP_