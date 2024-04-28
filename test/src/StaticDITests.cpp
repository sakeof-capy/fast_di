#include <gtest/gtest.h>

#include "../include/test/entities/Decorator.hpp"
#include "fast_di/DIContainer.hpp"
#include "fast_di/configs/register/Register.hpp"
#include "fast_di/TypeLists.hpp"

TEST(StaticDiTests, Container)
{
    using namespace Utilities::TypeTraits;

    using DIContainer = DIContainer
    <
            Register<RegistrationTypes::SINGLETON, Implementation>,
            Register<RegistrationTypes::SINGLETON, Decorator>,
            Register<RegistrationTypes::SINGLETON, IntContainer>
    >;

    constexpr static auto& some = DIContainer::resolve<IntContainer>();
    static_assert(some.i_ == 2u);

    constexpr static auto& some_dep2 = DIContainer::resolve<Decorator>();
    static_assert(some_dep2.do_something() == Decorator::DO_RESULT);
}

TEST(StaticDiTests, ConfigPredicate)
{
    static_assert(ConfigPredicate<Decorator, Register<RegistrationTypes::SINGLETON, Decorator>>::value);

    using SomeConfig = Register<RegistrationTypes::SINGLETON, Implementation>;
    static_assert(ConfigPredicateCarrier<Implementation>::template Predicate<SomeConfig>::value);
}
