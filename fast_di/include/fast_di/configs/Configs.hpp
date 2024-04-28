#ifndef CONFIGS_HPP_
#define CONFIGS_HPP_

#include "fast_di/TypeLists.hpp"

namespace FastDI::Static
{

template<typename Config, typename Container, typename TypeBeingRetrieved>
class ConfigWrapper;

template<typename... OtherConfigs>
using WithConfigs = Utilities::TypeTraits::pack<OtherConfigs...>;

}

#include "fast_di/configs/register/Register.hpp"

#endif //CONFIGS_HPP_
