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

namespace FastDI::Static
{

template<typename Dependency, typename Config>
constexpr bool matches_dependency(Config&&)
{
    return false;
}

template<typename... Configs>
class DIContainer
{
public:
    template<typename Dependency>
    constexpr Dependency resolve() const
    {
        using Config = decltype(find_config<Dependency>());
        static_assert(!std::is_void_v<Config>, "Config not found.");
//        static_assert(std::same_as<Register<RegistrationTypes::SINGLETON, IntContainer>, Config>);
        auto config = find_config<Dependency>();
        return create(std::move(config));
    }

private:
    template<typename Dependency>
    constexpr Dependency create(Register<RegistrationTypes::SINGLETON, Dependency>&&) const
    {
        auto creator_args_pack = Utilities::TypeTraits::ParamPackOf<decltype(Dependency::create)>{};
        auto resolved_creator_args = resolve_creator_args(creator_args_pack);
        //static constinit Dependency instance = std::apply(Dependency::create, resolved_creator_args);
        Dependency instance = std::apply(Dependency::create, resolved_creator_args);
        return instance;
    }

    template<typename Dependency>
    constexpr auto find_config() const
    {
        using namespace Utilities::TypeTraits;
        return for_each(pack<Configs...>{}, []<typename Config>() {
            if constexpr (matches_dependency<Dependency>(Config{})) {
                return Config{};
            }
        });
    }

    template<typename... ArgTypes>
    constexpr auto resolve_creator_args(Utilities::TypeTraits::pack<ArgTypes...>) const
    {
        using namespace Utilities::TypeTraits;
        return map_to_tuple(pack<ArgTypes...>{}, [this]<typename Arg>() -> Arg {
            return resolve<std::remove_reference_t<Arg>>();
        });
    }

private:
    template<RegistrationTypes RegistrationType, typename Dependency, typename... OtherConfigs>
    friend class Register;
};


}

#endif //DICONTAINER_HPP_
