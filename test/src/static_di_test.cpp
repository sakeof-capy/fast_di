#include <gtest/gtest.h>
#include "fast_di/DIContainer.hpp"
#include "fast_di/configs/Register.hpp"
#include "fast_di/TypeLists.hpp"

class SomeInt
{
public:
    constexpr virtual ~SomeInt() = default;

public:
    constexpr virtual const char* do_something() const = 0;
};

class SomeDep1 : public SomeInt
{
public:
    constexpr SomeDep1() = default;

    static constexpr SomeDep1 create()
    {
        return {};
    }

public:
    constexpr const char* do_something() const override
    {
        return DO_RESULT;
    }

public:
    static constexpr const char* DO_RESULT = "RESULT_OF_DO";
};

class SomeDep2 : public SomeInt
{
public:
    explicit constexpr SomeDep2(const SomeDep1& doer)
        : doer_ { doer }
    {}

    static constexpr SomeDep2 create(const SomeDep1& doer)
    {
        return SomeDep2 { doer };
    }

public:
    constexpr const char* do_something() const override
    {
        if (doer_.do_something() == SomeDep1::DO_RESULT)
        {
            return DO_RESULT;
        }
        else
        {
            return "WRONG_RESULT";
        }
    }

private:
    const SomeDep1& doer_;

public:
    static constexpr const char* DO_RESULT = "RESULT_OF_DO2222";
};

template<typename ToFind>
struct Finder
{
    template<typename Type>
    struct Predicate
    {
        static constexpr bool value = std::is_same_v<ToFind, Type>;
    };
};


TEST(ConstexprDiTest, DI)
{
    static constexpr SomeDep1 dep1;
    static constexpr SomeDep2 dep2 { dep1 };

    static_assert(dep1.do_something() == SomeDep1::DO_RESULT);
    static_assert(dep2.do_something() == SomeDep2::DO_RESULT);

    ASSERT_EQ(dep1.do_something(), SomeDep1::DO_RESULT);
    ASSERT_EQ(dep2.do_something(), SomeDep2::DO_RESULT);

    using namespace FastDI::Static;
    /*FastDI::Static::*/DIContainer
    <
        Register<RegistrationTypes::SINGLETON, SomeDep1>,
        Register<RegistrationTypes::SINGLETON, SomeDep2>,
        Register<RegistrationTypes::SINGLETON, IntContainer>
    > container;


    constexpr static auto some = container.resolve<IntContainer>();
    static_assert(some.i_ == 2u);

    using namespace Utilities::TypeTraits;
    constexpr static int r = for_each<int>(pack<int, float>{}, []<typename T>() {
        if constexpr (std::same_as<float, T>)
        {
            return 2;
        }
    }).value();
    static_assert(r == 2);
    ASSERT_EQ(r, 2);

    using concatenated = pack_concatenate_t<pack<int>, pack<float>>;
    static_assert(std::same_as<concatenated, pack<int, float>>);

    using filtered = pack_filter_t<pack<void, int, void, int>, std::is_void>;
    static_assert(std::same_as<filtered, pack<void, void>>);

    using filtered = pack_filter_t<pack<void, int, void, int>, Finder<void>::Predicate>;
    static_assert(std::same_as<filtered, pack<void, void>>);

    using SomeConfig = Register<RegistrationTypes::SINGLETON, SomeDep1>;
    static_assert(ConfigPredicateCarrier<SomeDep1>::template Predicate<SomeConfig>::value);
}
