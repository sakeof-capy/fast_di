#ifndef DICONTAINER_HPP_
#define DICONTAINER_HPP_

#include <optional>
#include "DIConfigHandler.hpp"
#include "TypeLists.hpp"
#include "configs/Register.hpp"

struct IntContainer
{
    constexpr explicit IntContainer(std::size_t i) : i_ { i } {}
    static constexpr IntContainer create()
    {
        return IntContainer(2u);
    }
    std::size_t i_;
};

//namespace FastDI::Static
//{

template<typename Config>
concept IsDIConfig = std::is_default_constructible_v<Config>;

template<IsDIConfig... Configs>
class DIContainer
{
private:
    using SelfType = DIContainer<Configs...>;

public:
    template<typename Dependency>
    static constexpr const Dependency& resolve()
    {
        using Utilities::TypeTraits::pack;
        using Utilities::TypeTraits::pack_filter_t;
        using Utilities::TypeTraits::pack_unpack_t;
        using Utilities::TypeTraits::index_of_type_v;

        using ConfigsMatchingTheDependencyPack = pack_filter_t<
            pack<Configs...>,
            ConfigPredicateCarrier<Dependency>::template Predicate
        >;

        static_assert(!std::same_as<pack<>, ConfigsMatchingTheDependencyPack>, "Dependency not registered.");

        using ConfigMatchingTheDependency = pack_unpack_t<ConfigsMatchingTheDependencyPack>;
        using WrappedConfig = ConfigWrapper<ConfigMatchingTheDependency, SelfType>;
        return WrappedConfig::create();
    }

public:
    template<typename... ArgTypes>
    static constexpr std::tuple<const ArgTypes&...> resolve_creator_args(Utilities::TypeTraits::pack<ArgTypes...>)
    {
        using namespace Utilities::TypeTraits;
        return map_to_tuple(pack<ArgTypes...>{}, []<typename Arg>() -> const Arg& {
            return resolve<std::remove_reference_t<Arg>>();
        });
    }
};

//}

#endif //DICONTAINER_HPP_
