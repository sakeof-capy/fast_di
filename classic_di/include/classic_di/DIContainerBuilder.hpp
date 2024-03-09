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
public:
    using Tag = typename DIContainer::Tag;

public:
    DIContainerBuilder() : container_ { std::make_unique<DIContainer>() } {}

public:
    template<typename Dependency, typename Interface = Dependency>
    auto&& register_singleton(Tag tag = DIContainer::DEFAULT_TAG) &&
    {
        return register_singleton_impl<Dependency, Interface>(std::move(*this), tag);
    }

    template<typename Dependency, typename Interface = Dependency>
    auto&& register_singleton(Tag tag = DIContainer::DEFAULT_TAG) &
    {
        return register_singleton_impl<Dependency, Interface>(*this, tag);
    }

    template<typename Dependency, typename Interface = Dependency>
    auto&& register_transient(Tag tag = DIContainer::DEFAULT_TAG) &
    {
        return register_transient_impl<Dependency, Interface>(*this, tag);
    }

    template<typename Dependency, typename Interface = Dependency>
    auto&& register_transient(Tag tag = DIContainer::DEFAULT_TAG) &&
    {
        return register_transient_impl<Dependency, Interface>(std::move(*this), tag);
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
    Self&& register_singleton_impl(Self&& self, Tag tag)
    {
        self.container_->add_singleton_dependency(
            typeid(Interface),
            container_->produce_singleton_creator<Dependency>(),
            tag
        );

        return std::forward<Self>(self);
    }

    template<typename Dependency, typename Interface, typename Self>
    Self&& register_transient_impl(Self&& self, Tag tag)
    {
        self.container_->add_transient_dependency(
            typeid(Interface),
            container_->produce_transient_creator<Dependency>(),
            tag
        );

        return std::forward<Self>(self);
    }

private:
    std::unique_ptr<DIContainer> container_;
};

#endif //DI_CONTAINER_BUILDER_HPP_