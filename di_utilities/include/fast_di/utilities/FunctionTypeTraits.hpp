#ifndef FUNCTION_TYPE_TRAITS_HPP_
#define FUNCTION_TYPE_TRAITS_HPP_

#include "Pack.hpp"

namespace fast_di::utilities
{

template<typename T>
struct function_traits;

template<typename ReturnValue_, typename... Params_>
struct function_traits<ReturnValue_(Params_...)>
{
    using ReturnValue = ReturnValue_;
    using Params = pack<Params_...>;
};

template<typename Function>
using ReturnValueOf = typename function_traits<Function>::ReturnValue;

template<typename Function>
using ParamPackOf = typename function_traits<Function>::Params;

}

#endif //FUNCTION_TYPE_TRAITS_HPP_
