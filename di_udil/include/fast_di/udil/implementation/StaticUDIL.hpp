#ifndef STATICUDIL_HPP_
#define STATICUDIL_HPP_

#include "fast_di/static/implementation/configs/Configs.hpp"

namespace fast_di::udil
{

constexpr fast_di::static_di::RegistrationTypes to_native_static_registration_type(
    const LifeCycle life_cycle
) {
    return fast_di::static_di::RegistrationTypes::SINGLETON;
}

template<typename InnerConfig>
struct ToNativeStaticConfig
{
    using type = int;
};

template<typename Interface>
struct ToNativeStaticConfig<AsInterface<Interface>>
{
    using type = static_di::AsInterface<Interface>;
};

template<typename InnerConfig>
using ToNativeStaticConfig_t = typename ToNativeStaticConfig<InnerConfig>::type;

template<LifeCycle LifeCycleType, typename Dependency, typename... InnerConfigs>
using FromCommonConfig = fast_di::static_di::Register<
    to_native_static_registration_type(LifeCycleType),
    Dependency,
    utilities::pack<ToNativeStaticConfig_t<InnerConfigs>...>
>;

}

#endif //STATICUDIL_HPP_
