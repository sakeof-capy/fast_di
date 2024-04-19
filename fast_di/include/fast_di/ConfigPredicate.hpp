#ifndef CONFIGPREDICATE_HPP_
#define CONFIGPREDICATE_HPP_

#include <type_traits>

template<typename Dependency, typename Config>
struct ConfigPredicate : std::false_type
{};

template<typename Dependency, typename Config>
constexpr bool config_predicate_v = ConfigPredicate<Dependency, Config>::value;

template<typename Dependency>
struct ConfigPredicateCarrier
{
    template<typename Config>
    struct Predicate
    {
        constexpr static bool value = config_predicate_v<Dependency, Config>;
    };
};

#include "configs/Configs.hpp"

#endif //CONFIGPREDICATE_HPP_
