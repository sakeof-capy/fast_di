#include <gtest/gtest.h>

#include "../../include/test/entities/Decorator.hpp"

TEST(StaticEntityTests, DecoratingTheImplementation)
{
    static constexpr Implementation dep1;
    static constexpr Decorator dep2 { dep1 };

    static_assert(dep1.do_something() == Implementation::DO_RESULT);
    static_assert(dep2.do_something() == Decorator::DO_RESULT);
}

TEST(DynamicEntityTests, DecoratingTheImplementation)
{
    Implementation dep1;
    Decorator dep2 { dep1 };

    ASSERT_STREQ(dep1.do_something(), Implementation::DO_RESULT);
    ASSERT_STREQ(dep2.do_something(), Decorator::DO_RESULT);
}
