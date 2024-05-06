#ifndef STATICCONFIGS_HPP_
#define STATICCONFIGS_HPP_

#include "fast_di/static/implementation/configs/Configs.hpp"

namespace fast_di::udil::hidden
{

constexpr fast_di::static_di::RegistrationTypes to_native_static_registration_type(
    const LifeCycle life_cycle
) {
    switch (life_cycle)
    {
        case LifeCycle::SINGLETON:
            return fast_di::static_di::RegistrationTypes::SINGLETON;
        case LifeCycle::TRANSIENT:
            return fast_di::static_di::RegistrationTypes::TRANSIENT;
    }
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

template<>
struct ToNativeStaticConfig<WithTag>
{
    using type = static_di::WithTag;
};

template<std::size_t Index>
struct ToNativeStaticConfig<WithTagOfDependencyAt<Index>>
{
using type = static_di::WithTagOfDependencyAt<Index>;
};

template<typename... Args>
struct ToNativeStaticConfig<ConstructedWith<Args...>>
{
using type = static_di::ConstructedWith<Args...>;
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

#endif //STATICCONFIGS_HPP_
