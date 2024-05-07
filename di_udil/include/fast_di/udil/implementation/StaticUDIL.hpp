#ifndef STATICUDIL_HPP_
#define STATICUDIL_HPP_

#include "fast_di/static/FastDI.hpp"
#include <tuple>
#include <cassert>

namespace fast_di::udil
{

template<typename... Configs>
constexpr auto form_di_container(std::tuple<Configs...> configs)
{
    using Container = static_di::DIContainer<typename Configs::StaticNativeConfig...>;
    return Container{};
}

#define DI_CONSTEXPR constexpr
#define DI_RESOLVED DI_CONSTEXPR
#define DI_DYNAMIC_RESOLVED
#define DI_ASSERT(Condition) static_assert(Condition)
#define DI_DYNAMIC_ASSERT(Condition) assert(Condition)

}

#endif //STATICUDIL_HPP_
