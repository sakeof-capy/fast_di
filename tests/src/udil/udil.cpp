#include <gtest/gtest.h>
#include <iostream>
#include "fast_di/udil/FastDI.hpp"

#include <type_traits>

struct Interface
{
    virtual ~Interface() = default;
    virtual int well_done() const = 0;
};

struct Implementor : Interface
{
    ~Implementor() override = default;
    virtual int well_done() const override
    {
        return 3;
    }
};

TEST(udil, form_container)
{
    using namespace fast_di::udil;

    std::tuple configs = {
        RegisterTransient<Implementor>::WithConfigs{
            AsInterface<Interface>{},
            WithTag{ "some_tag" },
            ConstructedWith<>{}
        }
    };
    auto container = fast_di::udil::form_di_container(configs);
    Interface& impl = container.resolve<Interface>("some_tag");
    ASSERT_EQ(impl.well_done(), 3);
}

TEST(udil, basic)
{

    using namespace fast_di::udil;
    auto reg = RegisterSingleton<int>::WithConfigs{
        AsInterface<double>{},
        WithTag{ "some_tag" },
        WithTagOfDependencyAt<0> { "some_other_tag" },
        ConstructedWith<int&, double&>{}
    };

#ifdef FAST_DI_ENABLE_GLOBAL_STATIC_DI
    using real_native = fast_di::static_di::Register<
        fast_di::static_di::RegistrationTypes::SINGLETON,
        int,
        fast_di::static_di::WithConfigs<
            fast_di::static_di::AsInterface<double>,
            fast_di::static_di::WithTag,
            fast_di::static_di::WithTagOfDependencyAt<0>,
            fast_di::static_di::ConstructedWith<int&, double&>
        >
    >;
    using static_native = typename decltype(reg)::StaticNativeConfig;
    static_assert(std::same_as<static_native, real_native>);
#endif

    auto reg_inner = reg.inner_configs_;
    auto as_interface = std::get<0>(reg_inner);
    auto with_tag = std::get<1>(reg_inner);
    auto with_tag_of_dep = std::get<2>(reg_inner);
    auto constructed_with = std::get<3>(reg_inner);
    bool a = std::same_as<decltype(as_interface), AsInterface<double>>;
    bool b = std::same_as<decltype(constructed_with), ConstructedWith<int&, double&>>;
    ASSERT_TRUE(a);
    ASSERT_TRUE(b);
    ASSERT_STREQ(with_tag.tag, "some_tag");
    ASSERT_STREQ(with_tag_of_dep.tag, "some_other_tag");
}

TEST(udil, into_tuple)
{
    using namespace fast_di::udil;
    std::tuple reg = {
        RegisterSingleton<int>::WithConfigs {
            AsInterface<double>{},
            WithTag{ "some_tag" },
            WithTagOfDependencyAt<0> { "some_other_tag" },
            ConstructedWith<int&, double&>{}
        }
    };

    auto reg_inner = std::get<0>(reg).inner_configs_;
    auto as_interface = std::get<0>(reg_inner);
    auto with_tag = std::get<1>(reg_inner);
    auto with_tag_of_dep = std::get<2>(reg_inner);
    auto constructed_with = std::get<3>(reg_inner);
    bool a = std::same_as<decltype(as_interface), AsInterface<double>>;
    bool b = std::same_as<decltype(constructed_with), ConstructedWith<int&, double&>>;
    ASSERT_TRUE(a);
    ASSERT_TRUE(b);
    ASSERT_STREQ(with_tag.tag, "some_tag");
    ASSERT_STREQ(with_tag_of_dep.tag, "some_other_tag");
}