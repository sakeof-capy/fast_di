#ifndef DI_CONTAINERS_TYPELISTS_HPP
#define DI_CONTAINERS_TYPELISTS_HPP

#include "Pack.hpp"
#include "FunctionTypeTraits.hpp"
#include <optional>

namespace fast_di::utilities
{

template<typename ReturnType>
using ForEachReturnType = std::conditional_t<
    std::is_void_v<ReturnType>,
    void,
    std::optional<ReturnType>
>;

template<typename Pack>
struct PackLast;

template<typename Type>
struct PackLast<pack<Type>>
{
    using type = Type;
};

template<typename Type, typename... Types>
struct PackLast<pack<Type, Types...>>
{
    using type = typename PackLast<Types...>::type;
};

template<typename Pack>
using pack_last_t = typename PackLast<Pack>::type;

template<typename Type, typename Pack>
struct PackAppend;

template<typename Type, typename... Types>
struct PackAppend<Type, pack<Types...>>
{
    using type = pack<Type, Types...>;
};

template<typename Type, typename Pack>
using pack_append_t = typename PackAppend<Type, Pack>::type;

//template<typename... Types>


template<typename... Packs>
struct PackConcatenate;

template<typename... Types>
struct PackConcatenate<pack<Types...>>
{
    using type = pack<Types...>;
};

template<typename... Types1, typename... Types2, typename... RestPacks>
struct PackConcatenate<pack<Types1...>, pack<Types2...>, RestPacks...>
{
    using type = typename PackConcatenate<pack<Types1..., Types2...>, RestPacks...>::type;
};

template<typename... Packs>
using pack_concatenate_t = typename PackConcatenate<Packs...>::type;

template<typename Pack, template<typename> typename Predicate>
struct PackFilter;

template<template<typename> typename Predicate>
struct PackFilter<pack<>, Predicate>
{
    using type = pack<>;
};

template<template<typename> typename Predicate, typename Type, typename... Types>
struct PackFilter<pack<Type, Types...>, Predicate>
{
    using type = std::conditional_t<
            Predicate<Type>::value,
            pack_concatenate_t<pack<Type>, typename PackFilter<pack<Types...>, Predicate>::type>,
            typename PackFilter<pack<Types...>, Predicate>::type
    >;
};

template<typename Pack, template<typename> typename Predicate>
using pack_filter_t = typename PackFilter<Pack, Predicate>::type;

namespace Private
{

template
<
    typename ReturnType,
    typename Processor,
    typename Head,
    typename... Tail
>
constexpr ForEachReturnType<ReturnType> for_each_impl(Processor&& processor)
{
    if constexpr (!std::is_void_v<decltype(processor.template operator()<Head>())>)
    {
        return processor.template operator()<Head>();
    }
    else
    {
        processor.template operator()<Head>();
    }

    if constexpr (sizeof...(Tail) > 0)
    {
        return for_each_impl<ReturnType, Processor, Tail...>(std::forward<Processor>(processor));
    }
    else
    {
        return std::nullopt;
    }
}

template
<
    typename Mapper,
    typename AccumulatedResult
>
constexpr auto map_to_tuple_impl(pack<>, Mapper&&, AccumulatedResult&& accumulator)
{
    return std::forward<AccumulatedResult>(accumulator);
}

template
<
    typename Mapper,
    typename AccumulatedResult,
    typename Head, typename... TypeList
>
constexpr auto map_to_tuple_impl(pack<Head, TypeList...>, Mapper&& mapper, AccumulatedResult&& accumulator)
    //-> std::tuple<ReturnValueOf<Mapper<Head>>, ReturnValueOf<Mapper<TypeList>>...>
{
    decltype(auto) mapped_value = mapper.template operator()<Head>();
    std::tuple<decltype(mapped_value)> mapped_head(mapped_value);
    auto head_concatenated_with_accumulator = std::tuple_cat(accumulator, mapped_head);

    if constexpr (sizeof... (TypeList) > 0)
    {
        return map_to_tuple_impl
        (
            pack<TypeList...>{},
            std::forward<Mapper>(mapper),
            std::move(head_concatenated_with_accumulator)
        );
    }
    else
    {
        return std::move(head_concatenated_with_accumulator);
    }
}

}


template
<
    typename ReturnType,
    typename... TypeList, template<typename...> typename Pack,
    typename Processor
>
constexpr ForEachReturnType<ReturnType> for_each(Pack<TypeList...>&&, Processor&& processor)
{
    return Private::for_each_impl<ReturnType, Processor, TypeList...>(std::forward<Processor>(processor));
}

template
<
    typename... TypeList, template<typename...> typename Pack,
    typename Mapper
>
constexpr auto map_to_tuple(Pack<TypeList...>&&, Mapper&& mapper) //-> std::tuple<ReturnValueOf<decltype(Mapper::template operator()<TypeList>)>...>
{
    using EmptyTupleType = std::tuple<>;
    return Private::map_to_tuple_impl(pack<TypeList...>{}, std::forward<Mapper>(mapper), EmptyTupleType{});
}

}

#endif //DI_CONTAINERS_TYPELISTS_HPP
