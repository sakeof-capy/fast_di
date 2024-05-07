#ifndef DYNAMICCONFIGS_HPP_
#define DYNAMICCONFIGS_HPP_

#include "fast_di/dynamic/FastDI.hpp"
#include "fast_di/udil/implementation/CommonConfigs.hpp"
#include "fast_di/udil/implementation/CommonInnerConfigs.hpp"

namespace fast_di::udil
{

template<
    fast_di::dynamic_di::LifeCycle LifeCycleType,
    typename Dependency,
    typename Interface
>
void apply_config(
    fast_di::dynamic_di::RegistrationBuilder<LifeCycleType, Dependency>& builder,
    AsInterface<Interface>
) {
    builder.template as_interface<Interface>();
}

template<
    fast_di::dynamic_di::LifeCycle LifeCycleType,
    typename Dependency
>
void apply_config(
    fast_di::dynamic_di::RegistrationBuilder<LifeCycleType, Dependency>& builder,
    WithTag with_tag_config
) {
    builder.with_tag(with_tag_config.tag);
}

template<
    fast_di::dynamic_di::LifeCycle LifeCycleType,
    typename Dependency,
    std::size_t Index
>
void apply_config(
    fast_di::dynamic_di::RegistrationBuilder<LifeCycleType, Dependency>& builder,
    WithTagOfDependencyAt<Index> with_tag_config
) {
    builder.template with_tag_of_dependency_at<Index>(with_tag_config.tag);
}

template<
    fast_di::dynamic_di::LifeCycle LifeCycleType,
    typename Dependency,
    typename... Args
>
void apply_config(
    fast_di::dynamic_di::RegistrationBuilder<LifeCycleType, Dependency>& builder,
    ConstructedWith<Args...> constructed_with_config
) {
    builder.template constructed_with<Args...>();
}

template<typename Dependency, typename... InnerConfigs>
void apply_config_register(
    fast_di::dynamic_di::DIContainerBuilder& builder,
    LifeCycle LifeCycleType,
    utilities::pack<InnerConfigs...>,
    std::tuple<InnerConfigs...> inner_configs
) {
    switch (LifeCycleType) {
        case LifeCycle::SINGLETON: {
            auto registration_builder = builder.register_singleton<Dependency>();
            auto inner = [&registration_builder](auto inner_config) {
                apply_config(registration_builder, inner_config);
            };
            utilities::for_each_in_tuple(inner_configs, inner);
            registration_builder.done();
            return;
        }
        case LifeCycle::TRANSIENT: {
            auto registration_builder =  builder.register_transient<Dependency>();
            auto inner = [&registration_builder](auto inner_config) {
                apply_config(registration_builder, inner_config);
            };
            utilities::for_each_in_tuple(inner_configs, inner);
            registration_builder.done();
            return;
        }
    };
}

}

#endif //DYNAMICCONFIGS_HPP_
