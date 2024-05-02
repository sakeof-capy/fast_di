#ifndef WITHTAG_HPP_
#define WITHTAG_HPP_

#include <type_traits>

#include "fast_di/TypeLists.hpp"
#include "fast_di/Tag.hpp"

namespace FastDI::Static
{

template<Tag SomeTag>
struct WithTag {};

template<Tag SomeTag, typename OtherConfig>
struct IsWithTag : std::false_type
{};

template<Tag SomeTag>
struct IsWithTag<SomeTag, WithTag<SomeTag>> : std::true_type
{};

template<Tag SomeTag, typename OtherConfig>
constexpr bool is_with_tag_v = IsWithTag<SomeTag, OtherConfig>::value;

template<Tag SomeTag>
struct IsWithTagCarrier
{
    template<typename OtherConfig>
    struct Predicate
    {
        constexpr static bool value = is_with_tag_v<SomeTag, OtherConfig>;
    };
};

template<Tag SomeTag, typename OtherConfigsPack>
using FilterAllWithTags = Utilities::TypeTraits::pack_filter_t<
    OtherConfigsPack,
    IsWithTagCarrier<SomeTag>::template Predicate
>;

}

#endif //WITHTAG_HPP_
