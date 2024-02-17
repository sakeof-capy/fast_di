#ifndef DI_CONTAINERS_PACK_HPP
#define DI_CONTAINERS_PACK_HPP

#include <tuple>

namespace TypeTraits
{

template<typename...>
struct pack {};

template<typename Pack>
constexpr bool is_empty_pack = std::is_same_v<pack<>, Pack>;

template<typename...>
struct TupleFromPack;

template<typename... Types>
struct TupleFromPack<pack<Types...>>
{
    using Type = std::tuple<Types...>;
};

template<typename... Types>
using tuple_from_pack_t = TupleFromPack<Types...>::Type;

}



#endif //DI_CONTAINERS_PACK_HPP
