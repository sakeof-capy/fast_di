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
        return IntContainer(2);
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
public:
    template<typename Dependency>
    constexpr Dependency resolve() const
    {
        using Utilities::TypeTraits::pack;
        using Utilities::TypeTraits::pack_filter_t;
        using Utilities::TypeTraits::pack_unpack_t;

        using ConfigsMatchingTheDependencyPack = pack_filter_t<
            pack<Configs...>,
            ConfigPredicateCarrier<Dependency>::template Predicate
        >;
        static_assert(!std::same_as<pack<>, ConfigsMatchingTheDependencyPack>, "Dependency not registered.");

        using ConfigMatchingTheDependency = pack_unpack_t<ConfigsMatchingTheDependencyPack>;
        return create(ConfigMatchingTheDependency{});
    }

private:
    template<typename... ArgTypes>
    constexpr auto resolve_creator_args(Utilities::TypeTraits::pack<ArgTypes...>) const
    {
        using namespace Utilities::TypeTraits;
        return map_to_tuple(pack<ArgTypes...>{}, [this]<typename Arg>() -> Arg {
            return resolve<std::remove_reference_t<Arg>>();
        });
    }

    template<typename Dependency>
    constexpr Dependency create(Register<RegistrationTypes::SINGLETON, Dependency>&&) const
    {
        auto creator_args_pack = Utilities::TypeTraits::ParamPackOf<decltype(Dependency::create)>{};
        auto resolved_creator_args = resolve_creator_args(creator_args_pack);
        //static constinit Dependency instance = std::apply(Dependency::create, resolved_creator_args);
        Dependency instance = std::apply(Dependency::create, resolved_creator_args);
        return instance;
    }



private:
    std::tuple<Configs...> configs_;
};


//}

#endif //DICONTAINER_HPP_
