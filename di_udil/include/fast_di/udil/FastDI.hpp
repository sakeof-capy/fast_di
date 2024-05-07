#ifndef FASTDI_UDIL_HPP_
#define FASTDI_UDIL_HPP_

#include "implementation/LifeCycle.hpp"
#include "implementation/CommonInnerConfigs.hpp"

#ifdef FAST_DI_ENABLE_GLOBAL_STATIC_DI
#include "implementation/StaticConfigs.hpp"
#include "implementation/StaticUDIL.hpp"
#else
#include "implementation/DynamicUDIL.hpp"
#include "implementation/DynamicConfigs.hpp"
#endif

#include "implementation/CommonConfigs.hpp"
#include "implementation/CommonUDIL.hpp"

#endif //FASTDI_UDIL_HPP_
