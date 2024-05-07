#ifndef STATICUDIL_HPP_
#define STATICUDIL_HPP_

#include "fast_di/static/FastDI.hpp"
#include <tuple>

namespace fast_di::udil
{

template<typename... Configs>
auto form_di_container(std::tuple<Configs...> configs)
{
    using Container = static_di::DIContainer<typename Configs::StaticNativeConfig...>;
    return Container{};
}

}

#endif //STATICUDIL_HPP_
