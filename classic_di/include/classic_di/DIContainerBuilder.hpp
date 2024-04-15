#ifndef DI_CONTAINER_BUILDER_HPP_
#define DI_CONTAINER_BUILDER_HPP_

#include <unordered_map>
#include <functional>
#include <vector>
#include <typeindex>
#include <memory>
#include "DIContainer.hpp"

enum class LifeCycle
{
    Singleton,
    Transient,
};

template<LifeCycle LifeCycleType, typename Dependency>
class RegistrationBuilder;

class DIContainerBuilder
{
public:
    using Tag = typename DIContainer::Tag;

public:
    DIContainerBuilder()
        : container_ { std::make_unique<DIContainer>() }
    {}

public:
    template<typename Dependency>
    RegistrationBuilder<LifeCycle::Singleton, Dependency> register_singleton()
    {
        return RegistrationBuilder<LifeCycle::Singleton, Dependency> { *this };
    }

    template<typename Dependency>
    RegistrationBuilder<LifeCycle::Transient, Dependency> register_transient()
    {
        return RegistrationBuilder<LifeCycle::Transient, Dependency> { *this };
    }

    std::unique_ptr<DIContainer> build() &
    {
        return std::make_unique<DIContainer>(*container_);
    }

private:
    template<typename Dependency>
    DIContainerBuilder& register_singleton_impl(std::type_index dependency_key, Tag tag)
    {
        container_->add_singleton_dependency(
            dependency_key,
            container_->produce_singleton_creator<Dependency>(),
            tag
        );

        return *this;
    }

    template<typename Dependency>
    DIContainerBuilder& register_transient_impl(std::type_index dependency_key, Tag tag)
    {
        container_->add_transient_dependency(
            dependency_key,
            container_->produce_transient_creator<Dependency>(),
            tag
        );

        return *this;
    }

private:
    std::unique_ptr<DIContainer> container_;

private:
    template<LifeCycle LifeCycleType, typename Dependency>
    friend class RegistrationBuilder;
};

template<LifeCycle LifeCycleType, typename Dependency>
class RegistrationBuilder
{
public:
    using Tag = typename DIContainerBuilder::Tag;

public:
    explicit RegistrationBuilder(DIContainerBuilder& builder_reference)
        : builder_reference_ { builder_reference }
        , dependency_key_ { typeid(Dependency) }
        , tag_ { DIContainer::DEFAULT_TAG }
    {}

public:
    template<typename Interface>
    RegistrationBuilder& as_interface()
    {
        dependency_key_ = typeid(Interface);
        return *this;
    }

    RegistrationBuilder& with_tag(Tag tag)
    {
        tag_ = tag;
        return *this;
    }

    template<typename Interface>
    RegistrationBuilder& with_dependency_tag(Tag tag);

    DIContainerBuilder& done()
    {
        switch (LifeCycleType)
        {
            case LifeCycle::Singleton:
                return builder_reference_.register_singleton_impl<Dependency>
                (
                    dependency_key_,
                    tag_
                );
            case LifeCycle::Transient:
                return builder_reference_.register_transient_impl<Dependency>
                (
                    dependency_key_,
                    tag_
                );
        }
    }

private:
    DIContainerBuilder& builder_reference_;
    std::type_index dependency_key_;
    Tag tag_;
};

#endif //DI_CONTAINER_BUILDER_HPP_