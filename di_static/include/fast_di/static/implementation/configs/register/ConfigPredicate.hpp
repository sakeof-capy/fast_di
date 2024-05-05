#ifndef REGISTER_CONFIG_PREDICATE_HPP_
#define REGISTER_CONFIG_PREDICATE_HPP_

#include "other_configs/OtherConfigs.hpp"
#include "fast_di/utilities/TypeLists.hpp"

namespace fast_di::static_di
{

template<typename Dependency, RegistrationTypes RegistrationType, typename OtherConfigsPack>
struct ConfigPredicate<
    Dependency,
    Register<RegistrationType, Dependency, OtherConfigsPack>
> : std::true_type
{};

template<typename Interface, typename Dependency, RegistrationTypes RegistrationType, typename OtherConfigsPack>
struct ConfigPredicate<
    Interface,
    Register<RegistrationType, Dependency, OtherConfigsPack>
> :
    std::conditional_t<
        std::same_as<FilterAllAsInterfaces<Interface, OtherConfigsPack>, utilities::EmptyPack>,
        std::false_type,
        std::true_type
    >
{};

}

#endif //REGISTER_CONFIG_PREDICATE_HPP_
