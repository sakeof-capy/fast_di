#ifndef REGISTER_HPP_
#define REGISTER_HPP_

#include "../FunctionTypeTraits.hpp"

template<typename... Configs>
class DIContainer;

namespace FastDI::Static
{

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

};

template<typename Dependency, RegistrationTypes RegistrationType, typename... OtherConfigs>
constexpr bool matches_dependency(Register<RegistrationType, Dependency, OtherConfigs...>&&)
{
    return true;
}

}

#endif //REGISTER_HPP_
