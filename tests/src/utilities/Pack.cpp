#include <gtest/gtest.h>
#include "fast_di/utilities/Pack.hpp"
#include "SomeInclude.hpp"

TEST(utilities, pack_test)
{
    using namespace fast_di::utilities;
    using SomePack = pack<int, float, double, ToTest>;
    static_assert(pack_size_v<SomePack> == 4);
}