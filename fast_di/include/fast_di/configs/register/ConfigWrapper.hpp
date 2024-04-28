#ifndef REGISTER_CONFIG_WRAPPER_HPP_
#define REGISTER_CONFIG_WRAPPER_HPP_

#include "fast_di/configs/Configs.hpp"

template<typename Dependency, typename Container, typename OtherConfigsPack>
class ConfigWrapper<Register<RegistrationTypes::SINGLETON, Dependency, OtherConfigsPack>, Container>
{
private:
    using DependencyArgs = Utilities::TypeTraits::ParamPackOf<decltype(Dependency::create)>;

public:
    static constexpr const Dependency& create()
    {
        return dependency;
    }

private:
    static constexpr Dependency dependency = std::apply(Dependency::create, Container::resolve_creator_args(DependencyArgs{}));
};


#endif //REGISTER_CONFIG_WRAPPER_HPP_
