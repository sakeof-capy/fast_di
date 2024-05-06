#ifndef COMMONCONFIGS_HPP_
#define COMMONCONFIGS_HPP_

#include "fast_di/utilities/Pack.hpp"
#include <tuple>

namespace fast_di::udil
{

template<typename Dependency>
struct RegisterSingleton
{
    template<typename... InnerConfigs>
    struct WithConfigs
    {
        explicit constexpr WithConfigs(InnerConfigs... inner_configs)
            : inner_configs_{ inner_configs... }
        {}

    public:
        std::tuple<InnerConfigs...> inner_configs_;
    };
};

// Inner Configs

template<typename Interface>
struct AsInterface {};

struct WithTag
{
    const char* tag;
};

template<std::size_t Index>
struct WithTagOfDependencyAt
{
    const char* tag;
};

template<typename... Args>
struct ConstructedWith {};

}

#endif //COMMONCONFIGS_HPP_
