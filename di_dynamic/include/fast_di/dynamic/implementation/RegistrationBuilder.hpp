#ifndef REGISTRATIONBUILDER_HPP_
#define REGISTRATIONBUILDER_HPP_

#include "fast_di/utilities/FunctionTypeTraits.hpp"
#include "DIContainerBuilder.hpp"
#include "WrapWithCreatorIfNotCreatable.hpp"
#include "LifeCycle.hpp"

namespace fast_di::dynamic_di
{

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
            std::map<std::size_t, Tag>&& dependency_tags
        )
    >;

public:
    explicit RegistrationBuilder(DIContainerBuilder& builder_reference)
        : builder_reference_ { builder_reference }
        , registration_method_ { produce_registration_method<Dependency>() }
        , dependency_tags_{}
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

    template<std::size_t DependencyIndex>
    RegistrationBuilder& with_dependency_tag_at(Tag tag)
    {
        dependency_tags_[DependencyIndex] = tag;
        return *this;
    }

    template<typename... Args>
    RegistrationBuilder& constructed_with()
    {
        using TypeToBeInserted = wrapper::WrapWithCreatorIfNotCreatable<Dependency, Args...>;
        registration_method_ = produce_registration_method<TypeToBeInserted>();

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
        if constexpr (utilities::create_static_method_exists_and_is_unique_v<TypeToBeInserted>)
        {
            DIContainerBuilder& builder_reference = builder_reference_;

            return [&builder_reference] (
                std::type_index dependency_key,
                Tag tag,
                std::map<std::size_t, Tag>&& dependency_tags
            ) -> DIContainerBuilder& {
                const std::size_t size = utilities::pack_size_v<
                    utilities::ParamPackOf<decltype(TypeToBeInserted::create)>
                >;
                std::vector<Tag> dependency_tags_vector(size, DIContainer::DEFAULT_TAG);

                for (const auto& [index, dependency_tag] : dependency_tags)
                {
                    if (index >= dependency_tags_vector.size())
                    {
                        std::string error_message = "Index " + std::to_string(index) +
                            " is not a valid dependency index.";
                        throw std::runtime_error(error_message);
                    }

                    dependency_tags_vector[index] = dependency_tag;
                }

                if constexpr (LifeCycleType == LifeCycle::Singleton)
                {
                    return builder_reference.register_singleton_impl<TypeToBeInserted>(
                        dependency_key,
                        tag,
                        std::move(dependency_tags_vector)
                    );
                }
                else
                {
                    return builder_reference.register_transient_impl<TypeToBeInserted>(
                        dependency_key,
                        tag,
                        std::move(dependency_tags_vector)
                    );
                }
            };
        }
        else
        {
            return [] (
                std::type_index dependency_key,
                Tag tag,
                std::map<std::size_t, Tag>&& dependency_tags
            ) -> DIContainerBuilder& {
                throw std::runtime_error("Trying to register a type without create static method.");
            };
        }
    }

private:
    DIContainerBuilder& builder_reference_;
    RegistrationMethod registration_method_;
    std::map<std::size_t, Tag> dependency_tags_;
    std::type_index dependency_key_;
    Tag tag_;
};

}

#endif //REGISTRATIONBUILDER_HPP_
