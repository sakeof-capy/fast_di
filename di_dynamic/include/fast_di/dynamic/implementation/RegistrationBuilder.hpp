#ifndef REGISTRATIONBUILDER_HPP_
#define REGISTRATIONBUILDER_HPP_

#include "DIContainerBuilder.hpp"
#include "WrapWithCreatorIfNotCreatable.hpp"
#include "LifeCycle.hpp"




#include <iostream>

namespace fast_di::dynamic_di
{


template<typename T>
auto has_create(int*) -> utilities::ParamPackOf<decltype(T::create)>
{return {};}

template<typename T>
auto has_create(...) -> int
{return 0;}

template<typename T>
constexpr bool has_create_v = !std::same_as<decltype(has_create<T>(nullptr)), int>;

template<LifeCycle LifeCycleType, typename Dependency>
class RegistrationBuilder
{
public:
    using Tag = typename DIContainerBuilder::Tag;

private:
    using RegistrationMethod = std::function<
        DIContainerBuilder&(
            std::type_index dependency_key,
            Tag tag,
            std::vector<Tag>&& dependency_tags
        )
    >;

    using DependencyTagsVecProvider = std::function<std::vector<Tag>()>;

public:
    explicit RegistrationBuilder(DIContainerBuilder& builder_reference)
        : builder_reference_ { builder_reference }
        , registration_method_ { produce_registration_method<Dependency>() }
        , vec_provider_(get_vec_provider<Dependency>())
        , dependency_tags_ { vec_provider_() }
        , dependency_key_ { typeid(Dependency) }
        , tag_ { DIContainer::DEFAULT_TAG }
    {}

private:

    template<typename TypeToBeInserted>
    static DependencyTagsVecProvider get_vec_provider()
    {
        return []() {
            if constexpr (has_create_v<TypeToBeInserted>) {
                const std::size_t dependencies_count = utilities::pack_size_v<utilities::ParamPackOf<decltype(TypeToBeInserted::create)>>;
                return std::vector<Tag>(dependencies_count, DIContainer::DEFAULT_TAG);
            }
            else
            {
                return std::vector<Tag>{};
            }
        };
    }

    static std::vector<Tag> dependency_tags_vec(const std::size_t dependencies_count)
    {
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

    template<typename... Args>
    RegistrationBuilder& constructed_with()
    {
        using TypeToBeInserted = wrapper::WrapWithCreatorIfNotCreatable<Dependency, Args...>;
        registration_method_ = produce_registration_method<TypeToBeInserted>();
        dependency_tags_ = get_vec_provider<TypeToBeInserted>()();

        return *this;
    }

    DIContainerBuilder& done()
    {
        return registration_method_(
            dependency_key_,
            tag_,
            std::move(dependency_tags_)
        );
    }

private:
    template<typename TypeToBeInserted>
    RegistrationMethod produce_registration_method()
    {
        if constexpr (has_create_v<TypeToBeInserted>)
        {
            DIContainerBuilder& builder_reference = builder_reference_;

            return [&builder_reference] (
                std::type_index dependency_key,
                Tag tag,
                std::vector<Tag>&& dependency_tags
            ) -> DIContainerBuilder& {
                if constexpr (LifeCycleType == LifeCycle::Singleton)
                {
                    return builder_reference.register_singleton_impl<TypeToBeInserted>(
                        dependency_key,
                        tag,
                        std::move(dependency_tags)
                    );
                }
                else
                {
                    return builder_reference.register_transient_impl<TypeToBeInserted>(
                        dependency_key,
                        tag,
                        std::move(dependency_tags)
                    );
                }
            };
        }
        else
        {
            return [] (
                std::type_index dependency_key,
                Tag tag,
                std::vector<Tag>&& dependency_tags
            ) -> DIContainerBuilder& {
                throw std::runtime_error("Trying to register a type without create");
            };
        }


    }

private:
    DIContainerBuilder& builder_reference_;
    RegistrationMethod registration_method_;
    DependencyTagsVecProvider vec_provider_;
    std::vector<Tag> dependency_tags_;
    std::type_index dependency_key_;
    Tag tag_;
};

}

#endif //REGISTRATIONBUILDER_HPP_
