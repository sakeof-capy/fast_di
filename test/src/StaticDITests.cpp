#include <gtest/gtest.h>

#include "../include/test/entities/Decorator.hpp"
#include "../include/test/entities/IntContainer.hpp"
#include "fast_di/DIContainer.hpp"
#include "fast_di/configs/Configs.hpp"
#include "fast_di/TypeLists.hpp"

using Utilities::TypeTraits::pack;

TEST(StaticDiTests, Container)
{
    using DIContainer = DIContainer
    <
        Register<RegistrationTypes::SINGLETON, Implementation>,
        Register<RegistrationTypes::SINGLETON, Decorator>,
        Register<
            RegistrationTypes::SINGLETON,
            IntContainer,
            WithConfigs<
                AsInterface<IntContainerInterface>
            >
        >
    >;

    constexpr static auto& some = DIContainer::resolve<IntContainer>();
    static_assert(some.i_ == IntContainer::DEFAULT_VALUE);

    constexpr static auto& some_dep2 = DIContainer::resolve<Decorator>();
    static_assert(some_dep2.do_something() == Decorator::DO_RESULT);

    constexpr static const IntContainerInterface& int_container = DIContainer::resolve<IntContainerInterface>();
    static_assert(int_container.get_i() == IntContainer::DEFAULT_VALUE);
}

TEST(StaticDiTests, ConfigPredicate)
{
    static_assert(config_predicate_v<Decorator, Register<RegistrationTypes::SINGLETON, Decorator>>);

    using SomeConfig = Register<RegistrationTypes::SINGLETON, Implementation>;
    static_assert(ConfigPredicateCarrier<Implementation>::template Predicate<SomeConfig>::value);
}

TEST(StaticDiTests, ConfigPredicateAsInterface)
{
    using SomeConfig = Register<
        RegistrationTypes::SINGLETON,
        Implementation,
        WithConfigs<
            AsInterface<Interface>
        >
    >;

    static_assert(config_predicate_v<Interface, SomeConfig>);
}
