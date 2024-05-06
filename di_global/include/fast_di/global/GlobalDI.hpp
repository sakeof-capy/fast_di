#ifndef GLOBALDI_HPP_
#define GLOBALDI_HPP_

#ifndef FAST_DI_ENABLE_GLOBAL_STATIC_DI
#else

#include "fast_di/dynamic/FastDI.hpp"
#include <memory>

namespace fast_di::global_di
{

class GlobalDI final
{
private:
    GlobalDI() = default;

public:
    GlobalDI(const GlobalDI&) = delete;
    GlobalDI(GlobalDI&&) = delete;
    GlobalDI& operator=(const GlobalDI&) = delete;
    GlobalDI& operator=(GlobalDI&&) = delete;

public:
    static dynamic_di::DIContainerBuilder& builder()
    {
        return get_instance().builder_;
    }

    static dynamic_di::DIContainer build_container()
    {
        return builder().build();
    }

    static GlobalDI& get_instance()
    {
        static GlobalDI global_di;
        return global_di;
    }

private:
    dynamic_di::DIContainerBuilder builder_;
};

#define DI_DYNAMIC_SUBSCRIBER_FOR(Dependency) \
void subscribe_##Dependency()

}
#endif

#endif //GLOBALDI_HPP_
