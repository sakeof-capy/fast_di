#ifndef DYNAMICUDIL_HPP_
#define DYNAMICUDIL_HPP_

#include <tuple>
#include <cassert>
#include "fast_di/dynamic/FastDI.hpp"

namespace fast_di::udil
{

template<typename... Configs>
auto form_di_container(std::tuple<Configs...> configs)
{
    fast_di::dynamic_di::DIContainerBuilder builder;

    auto inner = [&builder](auto config) {
        using DependencyType = typename decltype(config)::DependencyType;
        using InnerConfigsPack = typename decltype(config)::InnerConfigsPack;
        LifeCycle LifeCycleValue = config.LifeCycleTypeValue;
        auto inner_configs = config.inner_configs();

        apply_config_register<DependencyType>(
            builder, LifeCycleValue, InnerConfigsPack{}, inner_configs
        );
    };

    utilities::for_each_in_tuple(configs, inner);

    return builder.build();
}

#define DI_CONSTEXPR
#define DI_RESOLVED
#define DI_DYNAMIC_RESOLVED
#define DI_ASSERT(Condition) assert(Condition)
#define DI_DYNAMIC_ASSERT(Condition) DI_ASSERT(Condition)

}

#endif //DYNAMICUDIL_HPP_
