#ifndef GLOBALDI_HPP_
#define GLOBALDI_HPP_

#ifdef FAST_DI_ENABLE_GLOBAL_STATIC_DI
#include "fast_di/static/DIContainer.hpp"
#else
#include "include/fast_di/dynamic/implementation/DIContainer.hpp"
#endif

#endif //GLOBALDI_HPP_
