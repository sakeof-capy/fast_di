#ifndef FUNCTION_TYPE_TRAITS_HPP_
#define FUNCTION_TYPE_TRAITS_HPP_

namespace TypeTraits
{

template<typename...>
struct pack {};

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

//template<typename Head, typename... Tail>
//void print_type_names()
//{
//    std::cout << typeid(Head).name() << std::endl;
//
//    if constexpr (sizeof...(Tail) > 0)
//    {
//        print_type_names<Tail...>();
//    }
//}
//
//template<typename... Pack>
//void print_type_names_pack(pack<Pack...>)
//{
//    print_type_names<Pack...>();
//}
//
//template<typename T>
//void print_type_names_of_some_func()
//{
//    using params = typename function_traits<decltype(T::some_func)>::Params;
//    print_type_names_pack(params{});
//}

#endif //FUNCTION_TYPE_TRAITS_HPP_
