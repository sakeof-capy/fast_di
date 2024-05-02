#ifndef DICONTAINER_HPP_
#define DICONTAINER_HPP_

#include "TypeLists.hpp"
#include "fast_di/configs/Configs.hpp"

namespace FastDI::Static
{

template<typename Config>
concept IsDIConfig = std::is_default_constructible_v<Config>;

template<IsDIConfig... Configs>
class DIContainer
{
private:
    static constexpr Tag DEFAULT_TAG = "STATIC_DEFAULT_TAG";

private:
    using SelfType = DIContainer<Configs...>;

    template<typename T>
    using remove_const_reference_t = std::remove_const_t<std::remove_reference_t<T>>;

public:
    template<typename Dependency>
    static constexpr const remove_const_reference_t<Dependency>& resolve(Tag tag = DEFAULT_TAG)
    {
        using Utilities::TypeTraits::pack;
        using Utilities::TypeTraits::pack_filter_t;
        using Utilities::TypeTraits::pack_unpack_t;
        using Utilities::TypeTraits::index_of_type_v;

        using ConfigsMatchingTheDependencyPack = pack_filter_t<
            pack<Configs...>,
            ConfigPredicateCarrier<remove_const_reference_t<Dependency>>::template Predicate
        >;

        static_assert(!std::same_as<pack<>, ConfigsMatchingTheDependencyPack>, "Dependency not registered.");

        using ConfigMatchingTheDependency = pack_unpack_t<ConfigsMatchingTheDependencyPack>;
        using WrappedConfig = ConfigWrapper<ConfigMatchingTheDependency, SelfType, Dependency>;

        return WrappedConfig::create(tag);
    }

public:
    template<typename... ArgTypes>
    static constexpr std::tuple<const ArgTypes&...> resolve_creator_args(Utilities::TypeTraits::pack<ArgTypes...>)
    {
        using namespace Utilities::TypeTraits;
        return map_to_tuple(pack<ArgTypes...>{}, []<typename Arg>() -> const Arg& {
            return resolve<remove_const_reference_t<Arg>>();
        });
    }

};

}

#endif //DICONTAINER_HPP_
