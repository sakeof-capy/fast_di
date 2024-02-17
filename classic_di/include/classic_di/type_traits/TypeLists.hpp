#ifndef DI_CONTAINERS_TYPELISTS_HPP
#define DI_CONTAINERS_TYPELISTS_HPP

#include "Pack.hpp"
#include "FunctionTypeTraits.hpp"

namespace TypeTraits
{

namespace Private
{

template
<
    typename Processor,
    typename Head,
    typename... Tail
>
constexpr void for_each_impl(Processor&& processor)
{
    processor.template operator()<Head>();

    if constexpr (sizeof...(Tail) > 0)
    {
        for_each_impl<Processor, Tail...>(std::forward<Processor>(processor));
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

template<typename Head, typename...>
using HeadOf = Head;

template
<
    typename... TypeList, template<typename...> typename Pack,
    typename Processor
>
constexpr void for_each(Pack<TypeList...>&&, Processor&& processor)
{
    Private::for_each_impl<Processor, TypeList...>(std::forward<Processor>(processor));
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
