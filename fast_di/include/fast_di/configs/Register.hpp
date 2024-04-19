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
class Register<RegistrationTypes::SINGLETON, Dependency, OtherConfigs...> {};

template<typename Dependency, RegistrationTypes RegistrationType, typename... OtherConfigs>
struct ConfigPredicate<
    Dependency,
    Register<RegistrationType, Dependency, OtherConfigs...>
> : std::true_type
{};

//}

#endif //REGISTER_HPP_
