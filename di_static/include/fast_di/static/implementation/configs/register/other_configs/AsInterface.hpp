#ifndef ASINTERFACE_HPP_
#define ASINTERFACE_HPP_

#include <type_traits>
#include "fast_di/utilities/TypeLists.hpp"

namespace fast_di::static_di
{

template<typename Interface>
struct AsInterface
{};

template<typename Interface, typename OtherConfig>
struct IsAsInterface : std::false_type
{};

template<typename Interface>
struct IsAsInterface<Interface, AsInterface<Interface>> : std::true_type
{};

template<typename Interface, typename OtherConfig>
constexpr bool is_as_interface_v = IsAsInterface<Interface, OtherConfig>::value;

template<typename Interface>
struct IsAsInterfaceCarrier
{
    template<typename OtherConfig>
    struct Predicate
    {
        constexpr static bool value = is_as_interface_v<Interface, OtherConfig>;
    };
};

template<typename Interface, typename OtherConfigsPack>
using FilterAllAsInterfaces = utilities::pack_filter_t<
    OtherConfigsPack,
    IsAsInterfaceCarrier<Interface>::template Predicate
>;

}

#endif //ASINTERFACE_HPP_
