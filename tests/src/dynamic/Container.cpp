#include <gtest/gtest.h>
#include "fast_di/dynamic/DIContainer.hpp"

TEST(dynamic, container)
{
    static_assert(std::same_as<DIContainer, DIContainer>);
}