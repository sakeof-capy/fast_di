#ifndef REGISTRATIONBUILDER_HPP_
#define REGISTRATIONBUILDER_HPP_

#include "DIContainerBuilder.hpp"
#include "LifeCycle.hpp"

namespace fast_di::dynamic
{

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

private:
    static std::vector<Tag> vec_default()
    {
        using DependenciesPack = utilities::ParamPackOf<decltype(Dependency::create)>;
        std::size_t dependencies_count = utilities::pack_size_v<DependenciesPack>;
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
        using DependenciesPack = utilities::ParamPackOf<decltype(Dependency::create)>;

        if constexpr (!utilities::pack_contains_v <Interface&, DependenciesPack>)
        {
            throw std::runtime_error("Trying to assign tag to an inexistent dependency.");
        }

        const std::size_t index_of_interface = utilities::index_of_type_v<Interface&, DependenciesPack>;
        dependency_tags_[index_of_interface] = tag;

        return *this;
    }


    template<std::size_t DependencyIndex>
    RegistrationBuilder& with_dependency_tag_at(Tag tag)
    {
        using DependenciesPack = utilities::ParamPackOf<decltype(Dependency::create)>;
        static_assert(DependencyIndex<utilities::pack_size_v<DependenciesPack>, "Invalid Dependency Index");

        dependency_tags_[DependencyIndex] = tag;

        return *this;
    }

    DIContainerBuilder& done()
    {
        if constexpr (LifeCycleType == LifeCycle::Singleton)
        {
            return builder_reference_.register_singleton_impl<Dependency>(
                dependency_key_,
                tag_,
                std::move(dependency_tags_)
            );
        }
        else if (LifeCycleType == LifeCycle::Transient)
        {
            return builder_reference_.register_transient_impl<Dependency>(
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

}

#endif //REGISTRATIONBUILDER_HPP_
