#ifndef REGISTER_HPP_
#define REGISTER_HPP_

#include "fast_di/FunctionTypeTraits.hpp"
#include "fast_di/ConfigPredicate.hpp"

//namespace FastDI::Static
//{

enum class RegistrationTypes
{
    SINGLETON
};

template<RegistrationTypes RegistrationType, typename Dependency, typename OtherConfigsPack = Utilities::TypeTraits::pack<>>
class Register;

template<typename Dependency, typename OtherConfigsPack>
class Register<RegistrationTypes::SINGLETON, Dependency, OtherConfigsPack>
{
public:
    constexpr Register() = default;
};

//}

#include "fast_di/configs/register/ConfigWrapper.hpp"
#include "fast_di/configs/register/ConfigPredicate.hpp"

#endif //REGISTER_HPP_
