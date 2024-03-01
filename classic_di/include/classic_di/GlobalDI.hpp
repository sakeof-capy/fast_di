#ifndef GLOBALDI_HPP_
#define GLOBALDI_HPP_

#include "DIContainer.hpp"
#include "DIContainerBuilder.hpp"
#include <memory>

class GlobalDI final
{
private:
    GlobalDI() = default;
    GlobalDI(const GlobalDI&) = delete;
    GlobalDI(GlobalDI&&) = delete;
    GlobalDI& operator=(const GlobalDI&) = delete;
    GlobalDI& operator=(GlobalDI&&) = delete;

public:
    static DIContainerBuilder& builder()
    {
        return get_instance().builder_;
    }

    static std::unique_ptr<DIContainer> build_container()
    {
        return builder().build();
    }

    static GlobalDI& get_instance()
    {
        static GlobalDI global_di;
        return global_di;
    }

private:
    DIContainerBuilder builder_;
};

#endif //GLOBALDI_HPP_
