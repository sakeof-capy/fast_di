#ifndef DI_CONTAINER_BUILDER_HPP_
#define DI_CONTAINER_BUILDER_HPP_

#include <unordered_map>
#include <functional>
#include <vector>
#include <typeindex>
#include <memory>
#include "DIContainer.hpp"
#include "LifeCycle.hpp"

namespace fast_di::dynamic_di
{

template<LifeCycle LifeCycleType, typename Dependency>
class RegistrationBuilder;

class DIContainerBuilder
{
public:
    using Tag = typename DIContainer::Tag;

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
    ) {
        container_.add_singleton_dependency(
            dependency_key,
            container_.produce_singleton_creator<Dependency>(std::move(dependency_tags)),
            tag
        );

        return *this;
    }

    template<typename Dependency>
    DIContainerBuilder& register_transient_impl(
        std::type_index dependency_key,
        Tag tag,
        std::vector<Tag>&& dependency_tags
    ) {
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
    friend
    class RegistrationBuilder;
};

}

#include "RegistrationBuilder.hpp"

#endif //DI_CONTAINER_BUILDER_HPP_