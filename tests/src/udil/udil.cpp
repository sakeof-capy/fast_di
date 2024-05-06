#include <gtest/gtest.h>
#include <iostream>
#include "fast_di/udil/UDIL.hpp"
//#include "../../../di_udil/include/fast_di/udil/UDIL.hpp"

TEST(udil, basic)
{
    using namespace fast_di::udil;
    auto reg = RegisterSingleton<int>::WithConfigs{
        AsInterface<double>{},
        WithTag{ "some_tag" },
        WithTagOfDependencyAt<0> { "some_other_tag" },
        ConstructedWith<int&, double&>{}
    };
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