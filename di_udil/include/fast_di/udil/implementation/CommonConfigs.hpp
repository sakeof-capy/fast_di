#ifndef COMMONCONFIGS_HPP_
#define COMMONCONFIGS_HPP_

#include "fast_di/utilities/Pack.hpp"
#include "fast_di/static/implementation/configs/Configs.hpp"
#include <tuple>

namespace fast_di::udil
{

template<LifeCycle LifeCycleType, typename Dependency>
struct Register
{
    template<typename... InnerConfigs>
    struct WithConfigs
    {
        explicit constexpr WithConfigs(InnerConfigs... inner_configs)
            : inner_configs_{ inner_configs... }
        {}

#ifdef FAST_DI_ENABLE_GLOBAL_STATIC_DI
        using StaticNativeConfig = hidden::FromCommonConfig<LifeCycleType, Dependency, InnerConfigs...>;
#endif
        static constexpr LifeCycle LifeCycleTypeValue = LifeCycleType;
        using DependencyType = Dependency;
        using InnerConfigsPack = utilities::pack<InnerConfigs...>;

        const std::tuple<InnerConfigs...>& inner_configs() const
        {
            return inner_configs_;
        }

    public:
        std::tuple<InnerConfigs...> inner_configs_;
    };
};

template<typename Dependency>
using RegisterSingleton = Register<LifeCycle::SINGLETON, Dependency>;

template<typename Dependency>
using RegisterTransient = Register<LifeCycle::TRANSIENT, Dependency>;

}

#endif //COMMONCONFIGS_HPP_
