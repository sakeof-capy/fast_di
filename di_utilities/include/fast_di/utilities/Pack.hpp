#ifndef DI_CONTAINERS_PACK_HPP
#define DI_CONTAINERS_PACK_HPP

#include <tuple>

namespace fast_di::utilities
{

template<typename...>
struct pack {};

using EmptyPack = pack<>;

template<typename Pack>
constexpr bool is_empty_pack = std::is_same_v<EmptyPack, Pack>;

template<typename...>
struct TupleFromPack;

template<typename... Types>
struct TupleFromPack<pack<Types...>>
{
    using Type = std::tuple<Types...>;
};

template<typename Pack>
using tuple_from_pack_t = TupleFromPack<Pack>::Type;

template<typename Pack>
constexpr std::size_t pack_size_v = std::tuple_size_v<tuple_from_pack_t<Pack>>;

template<typename Type, typename Pack>
struct pack_contains
    : std::false_type
{};

template<typename Type, typename TypeIter, typename... Types>
struct pack_contains<Type, pack<TypeIter, Types...>>
    : pack_contains<Type, pack<Types...>>
{};

template<typename Type, typename... Types>
struct pack_contains<Type, pack<Type, Types...>>
    : std::true_type
{};

template<typename Type, typename Pack>
constexpr bool pack_contains_v = pack_contains<Type, Pack>::value;

template<typename Type, typename Pack>
struct IndexOfType
    : std::integral_constant<std::size_t, static_cast<std::size_t>(-1)>
{};

template<typename Type, typename... Types>
struct IndexOfType<Type, pack<Type, Types...>>
    : std::integral_constant<std::size_t, 0>
{};

template<typename Type, typename TypeIter, typename... Types>
struct IndexOfType<Type, pack<TypeIter, Types...>>
    : std::integral_constant<std::size_t, 1u + IndexOfType<Type, pack<Types...>>::value>
{};

template<typename Type, typename Pack>
constexpr std::size_t index_of_type_v = IndexOfType<Type, Pack>::value;

template<typename Pack>
struct PackUnpack;

template<typename Type>
struct PackUnpack<pack<Type>>
{
    using type = Type;
};

template<typename Pack>
using pack_unpack_t = typename PackUnpack<Pack>::type;

}



#endif //DI_CONTAINERS_PACK_HPP
