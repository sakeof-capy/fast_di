#include <gtest/gtest.h>

#include "../include/test/entities/Decorator.hpp"
#include "../include/test/entities/IntContainer.hpp"
#include "fast_di/DIContainer.hpp"
#include "fast_di/configs/Configs.hpp"
#include "fast_di/configs/register/other_configs/OtherConfigs.hpp"
#include "fast_di/TypeLists.hpp"

using Utilities::TypeTraits::pack;
using FastDI::Static::Register;
using FastDI::Static::RegistrationTypes;
using FastDI::Static::AsInterface;
using FastDI::Static::WithConfigs;
using FastDI::Static::config_predicate_v;
using FastDI::Static::ConfigPredicateCarrier;
using FastDI::Static::FilterAllWithTags;
using FastDI::Static::WithTag;


using DIContainer = FastDI::Static::DIContainer
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

TEST(StaticDiTests, BasicRetrieval)
{
    constexpr static auto& some = DIContainer::resolve<IntContainer>();
    static_assert(some.i_ == IntContainer::DEFAULT_VALUE);
}

TEST(StaticDiTests, CompositionRetrieval)
{
    constexpr static auto& some_dep2 = DIContainer::resolve<Decorator>();
    static_assert(some_dep2.do_something() == Decorator::DO_RESULT);
}

TEST(StaticDiTests, InterfaceRetrieval)
{
    constexpr static const IntContainerInterface& int_container = DIContainer::resolve<IntContainerInterface>();
    static_assert(int_container.get_i() == IntContainer::DEFAULT_VALUE);

    constexpr static const IncrementorInterface& incrementor = DIContainer::resolve<IncrementorInterface>();
    static_assert(incrementor.increment() == IntContainer::DEFAULT_VALUE + 1u);
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

void f(const char* tag)
{

}

TEST(StaticDiTests, FilterAllWithTags)
{
    using Configs = pack<
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
//    using SomeType = X<"abcc">;
//    using a = FilterAllWithTags<"asd", Configs>;
}
