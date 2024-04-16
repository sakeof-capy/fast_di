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
        : container_ {}
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

    DIContainer build()
    {
        return container_;
    }

private:
    template<typename Dependency>
    DIContainerBuilder& register_singleton_impl
    (
        std::type_index dependency_key,
        Tag tag,
        std::vector<Tag>&& dependency_tags
    )
    {
        container_.add_singleton_dependency(
            dependency_key,
            container_.produce_singleton_creator<Dependency>(std::move(dependency_tags)),
            tag
        );

        return *this;
    }

    template<typename Dependency>
    DIContainerBuilder& register_transient_impl
    (
        std::type_index dependency_key,
        Tag tag,
        std::vector<Tag>&& dependency_tags
    )
    {
        container_.add_transient_dependency(
            dependency_key,
            container_.produce_transient_creator<Dependency>(std::move(dependency_tags)),
            tag
        );

        return *this;
    }

private:
    DIContainer container_;

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
        , dependency_tags_ { vec_default() }
        , dependency_key_ { typeid(Dependency) }
        , tag_ { DIContainer::DEFAULT_TAG }
    {}

    static std::vector<Tag> vec_default()
    {
        using DependenciesPack = TypeTraits::ParamPackOf<decltype(Dependency::create)>;
        std::size_t dependencies_count = TypeTraits::pack_size_v<DependenciesPack>;
        return std::vector<Tag>(dependencies_count, DIContainer::DEFAULT_TAG);
    }

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
    RegistrationBuilder& with_dependency_tag(Tag tag)
    {
        using DependenciesPack = TypeTraits::ParamPackOf<decltype(Dependency::create)>;

        if constexpr (!TypeTraits::pack_contains_v<Interface&, DependenciesPack>)
        {
            throw std::runtime_error("Trying to assign tag to an inexistent dependency.");
        }

        const std::size_t index_of_interface = TypeTraits::index_of_type_v<Interface&, DependenciesPack>;
        dependency_tags_[index_of_interface] = tag;

        return *this;
    }

    DIContainerBuilder& done()
    {
        switch (LifeCycleType)
        {
            case LifeCycle::Singleton:
                return builder_reference_.register_singleton_impl<Dependency>
                (
                    dependency_key_,
                    tag_,
                    std::move(dependency_tags_)
                );
            case LifeCycle::Transient:
                return builder_reference_.register_transient_impl<Dependency>
                (
                    dependency_key_,
                    tag_,
                    std::move(dependency_tags_)
                );
        }
    }

private:
    DIContainerBuilder& builder_reference_;
    std::vector<Tag> dependency_tags_;
    std::type_index dependency_key_;
    Tag tag_;
};

#endif //DI_CONTAINER_BUILDER_HPP_