#ifndef CONFIGS_HPP_
#define CONFIGS_HPP_

#include "fast_di/utilities/TypeLists.hpp"

namespace fast_di::static_di
{

template<typename Config, typename Container, typename TypeBeingRetrieved>
class ConfigWrapper;

template<typename... OtherConfigs>
using WithConfigs = utilities::pack<OtherConfigs...>;

}

#include "register/Register.hpp"

#endif //CONFIGS_HPP_
