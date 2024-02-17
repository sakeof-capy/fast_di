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
    template<typename> typename Processor,
    typename Current,
    typename... Other
>
constexpr void for_each_impl()
{
    Processor<Current>();

    if constexpr (sizeof...(Other) > 0)
    {
        for_each_impl<Other...>();
    }
}
#include <iostream>
template
<
    typename Mapper,
    typename AccumulatedResult,
    typename Head, typename... TypeList
>
constexpr auto map_to_tuple_impl(Mapper&& mapper, AccumulatedResult&& accumulator)
    //-> std::tuple<ReturnValueOf<Mapper<Head>>, ReturnValueOf<Mapper<TypeList>>...>
{
    auto mapped_value = mapper.template operator()<Head>();
    std::cout << "Mapped value = " << mapped_value << std::endl;
    std::tuple<decltype(mapped_value)> mapped_head(mapped_value);
    auto head_concatenated_with_accumulator = std::tuple_cat(accumulator, mapped_head);

    if constexpr (sizeof... (TypeList) > 0)
    {
        return map_to_tuple_impl
        <
            Mapper,
            decltype(head_concatenated_with_accumulator),
            TypeList...
        >
        (
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
    template<typename> typename Processor,
    typename... TypeList
>
constexpr void for_each()
{
    Private::for_each_impl<Processor, TypeList...>();
}

template
<
    template<typename> typename Processor,
    typename... TypeList
>
constexpr void for_each_in_pack(pack<TypeList...>)
{
    Private::for_each_impl<Processor, TypeList...>();
}

template
<
    typename... TypeList, template<typename> typename Pack,
    typename Mapper
>
constexpr auto map_to_tuple(Pack<TypeList...>&&, Mapper&& mapper) //-> std::tuple<ReturnValueOf<decltype(Mapper::template operator()<TypeList>)>...>
{
    using EmptyTupleType = std::tuple<>;
    return Private::map_to_tuple_impl<decltype(mapper), EmptyTupleType, TypeList...>(std::forward<Mapper>(mapper), EmptyTupleType{});
}



}

#endif //DI_CONTAINERS_TYPELISTS_HPP
