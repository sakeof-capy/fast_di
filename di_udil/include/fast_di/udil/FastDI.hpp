#ifndef FASTDI_HPP_
#define FASTDI_HPP_

#include "implementation/LifeCycle.hpp"
#include "implementation/CommonInnerConfigs.hpp"

#ifdef FAST_DI_ENABLE_GLOBAL_STATIC_DI
#include "implementation/StaticUDIL.hpp"
#include "implementation/StaticConfigs.hpp"
#else
#include "implementation/DynamicUDIL.hpp"
#endif

#include "implementation/CommonConfigs.hpp"

#endif //FASTDI_HPP_
