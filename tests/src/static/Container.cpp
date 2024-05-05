#include <gtest/gtest.h>

#include "entities/Decorator.hpp"
#include "entities/IntContainer.hpp"
#include "fast_di/static/FastDI.hpp"
#include "fast_di/utilities/TypeLists.hpp"

using fast_di::utilities::pack;
using fast_di::static_di::Register;
using fast_di::static_di::RegistrationTypes;
using fast_di::static_di::AsInterface;
using fast_di::static_di::WithConfigs;
using fast_di::static_di::config_predicate_v;
using fast_di::static_di::ConfigPredicateCarrier;

using DIContainer = fast_di::static_di::DIContainer
<
    Register<RegistrationTypes::SINGLETON, Implementation>,
    Register<RegistrationTypes::SINGLETON, Decorator>,
    Register<
        RegistrationTypes::SINGLETON,
        IntContainer,
        WithConfigs<
            AsInterface<IntContainerInterface>,
            AsInterface<IncrementorInterface>
        >
    >
>;

TEST(static_di, basic_retrieval)
{
    constexpr static auto& some = DIContainer::resolve<IntContainer>();
    static_assert(some.i_ == IntContainer::DEFAULT_VALUE);
}

TEST(static_di, composition_retrieval)
{
    constexpr static auto& some_dep2 = DIContainer::resolve<Decorator>();
    static_assert(some_dep2.do_something() == Decorator::DO_RESULT);
}

TEST(static_di, retrieval_with_interface)
{
    constexpr static const IntContainerInterface& int_container = DIContainer::resolve<IntContainerInterface>();
    static_assert(int_container.get_i() == IntContainer::DEFAULT_VALUE);

    constexpr static const IncrementorInterface& incrementor = DIContainer::resolve<IncrementorInterface>();
    static_assert(incrementor.increment() == IntContainer::DEFAULT_VALUE + 1u);
}

TEST(static_di, config_predicate_basic_verification)
{
    static_assert(config_predicate_v<Decorator, Register<RegistrationTypes::SINGLETON, Decorator>>);

    using SomeConfig = Register<RegistrationTypes::SINGLETON, Implementation>;
    static_assert(ConfigPredicateCarrier<Implementation>::template Predicate<SomeConfig>::value);
}

TEST(static_di, config_predicate_interface_verification)
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
