#ifndef REGISTER_HPP_
#define REGISTER_HPP_

#include "fast_di/utilities/FunctionTypeTraits.hpp"
#include "fast_di/static/implementation/configs/ConfigPredicate.hpp"

namespace fast_di::static_di
{

enum class RegistrationTypes
{
    SINGLETON,
    TRANSIENT,
};

template<
    RegistrationTypes RegistrationType,
    typename Dependency,
    typename OtherConfigsPack = utilities::pack<>
>
class Register{};

}

#include "ConfigWrapper.hpp"
#include "ConfigPredicate.hpp"

#endif //REGISTER_HPP_
