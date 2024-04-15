#ifndef DI_CONTAINER_BUILDER_HPP_
#define DI_CONTAINER_BUILDER_HPP_

#include <unordered_map>
#include <functional>
#include <vector>
#include <typeindex>
#include <memory>
#include "DIContainer.hpp"

template<typename Dependency>
class SingletonBuilder;

class DIContainerBuilder
{
public:
    using Tag = typename DIContainer::Tag;

public:
    DIContainerBuilder() : container_ { std::make_unique<DIContainer>() } {}

public:
    template<typename Dependency>
    SingletonBuilder<Dependency> register_singleton() &&
    {
        return { *this };
//        return register_singleton_impl<Dependency>(std::move(*this), typeid(Interface), tag);
    }

    template<typename Dependency>
    SingletonBuilder<Dependency> register_singleton() &
    {
        return { *this };
//        return register_singleton_impl<Dependency>(*this, typeid(Interface), tag);
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
    template<typename Dependency, typename Self>
    static Self&& register_singleton_impl(Self&& self, std::type_index dependency_key, Tag tag)
    {
        self.container_->add_singleton_dependency(
            dependency_key,
            self.container_->template produce_singleton_creator<Dependency>(),
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

private:
    template<typename Dependency>
    friend class SingletonBuilder;
};

template<typename Dependency>
class SingletonBuilder
{
public:
    using Tag = typename DIContainerBuilder::Tag;

public:
    SingletonBuilder(DIContainerBuilder& builder_reference)
        : builder_reference_ { builder_reference }
        , dependency_key_ { typeid(Dependency) }
        , tag_ { DIContainer::DEFAULT_TAG }
    {}

public:
    template<typename Interface>
    SingletonBuilder& as_interface()
    {
        dependency_key_ = typeid(Interface);
        return *this;
    }

    SingletonBuilder& with_tag(Tag tag)
    {
        tag_ = tag;
        return *this;
    }

    template<typename Interface>
    SingletonBuilder& with_dependency_tag(Tag tag);

    DIContainerBuilder& done()
    {
        return DIContainerBuilder::template register_singleton_impl<Dependency>
        (
            builder_reference_,
            dependency_key_,
            tag_
        );
    }


private:
    DIContainerBuilder& builder_reference_;
    std::type_index dependency_key_;
    Tag tag_;
};

#endif //DI_CONTAINER_BUILDER_HPP_