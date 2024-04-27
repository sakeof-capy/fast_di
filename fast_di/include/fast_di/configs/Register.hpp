#ifndef REGISTER_HPP_
#define REGISTER_HPP_

#include "../FunctionTypeTraits.hpp"
#include "../ConfigPredicate.hpp"

//namespace FastDI::Static
//{

enum class RegistrationTypes
{
    SINGLETON
};

template<RegistrationTypes RegistrationType, typename Dependency, typename... OtherConfigs>
class Register;

template<typename Dependency, typename... OtherConfigs>
class Register<RegistrationTypes::SINGLETON, Dependency, OtherConfigs...>
{
public:
    constexpr Register() = default;
};

template<typename Dependency, typename Container, typename... OtherConfigs>
class ConfigWrapper<Register<RegistrationTypes::SINGLETON, Dependency, OtherConfigs...>, Container>
{
private:
    using DependencyArgs = Utilities::TypeTraits::ParamPackOf<decltype(Dependency::create)>;

public:
    static constexpr const Dependency& create()
    {
        return dependency;
    }

private:
    static constexpr Dependency dependency = std::apply(Dependency::create, Container::resolve_creator_args(DependencyArgs{}));
};

template<typename Dependency, RegistrationTypes RegistrationType>
struct ConfigPredicate<
    Dependency,
    Register<RegistrationType, Dependency>
> : std::true_type
{};

//}

#endif //REGISTER_HPP_
