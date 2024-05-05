#include <gtest/gtest.h>
#include "fast_di/utilities/TypeLists.hpp"

using fast_di::utilities::pack;
using fast_di::utilities::pack_filter_t;
using fast_di::utilities::pack_concatenate_t;

template<typename ToFind>
struct Finder
{
    template<typename Type>
    struct Predicate
    {
        static constexpr bool value = std::is_same_v<ToFind, Type>;
    };
};

struct SomeStruct { float i; };

TEST(static_type_traits, pack_filter_not_empty)
{
    using filtered1 = pack_filter_t<pack<void, int, void, int, SomeStruct>, std::is_void>;
    static_assert(std::same_as<filtered1, pack<void, void>>);

    using filtered2 = pack_filter_t<pack<void, int, void, int, SomeStruct>, Finder<void>::Predicate>;
    static_assert(std::same_as<filtered2, pack<void, void>>);

    using filtered3 = pack_filter_t<pack<void, int, void, SomeStruct, int>, Finder<void>::Predicate>;
    static_assert(std::same_as<filtered3, pack<void, void>>);

    using filtered4 = pack_filter_t<pack<void, int, void, SomeStruct, int>, Finder<int>::Predicate>;
    static_assert(std::same_as<filtered4, pack<int, int>>);

    using filtered5 = pack_filter_t<pack<void, int, void, SomeStruct, int>, Finder<SomeStruct>::Predicate>;
    static_assert(std::same_as<filtered5, pack<SomeStruct>>);
}

TEST(static_type_traits, pack_filter_empty)
{
    using filtered1 = pack_filter_t<pack<int, int, double, int, short, SomeStruct>, std::is_void>;
    static_assert(std::same_as<filtered1, pack<>>);

    using filtered2 = pack_filter_t<pack<void, int, void, int>, Finder<SomeStruct>::Predicate>;
    static_assert(std::same_as<filtered2, pack<>>);

    using filtered3 = pack_filter_t<pack<>, Finder<int>::Predicate>;
    static_assert(std::same_as<filtered3, pack<>>);
}

TEST(static_type_traits, for_each)
{
    using PackToIterateOver = pack<int, float>;

    constexpr static std::optional<int> maybe_int = for_each<int>(PackToIterateOver{}, []<typename T>() {
        if constexpr (std::same_as<float, T>) {
            return 2;
        }
    });

    static_assert(maybe_int.has_value());
    static_assert(maybe_int.value() == 2);

    constexpr static std::optional<long> maybe_long = for_each<long>(PackToIterateOver{}, []<typename T>() {
        if constexpr (std::same_as<SomeStruct, T>) {
            return 2;
        }
    });

    static_assert(!maybe_long.has_value());
}

TEST(static_type_traits, pack_concatenate)
{
    using concatenated = pack_concatenate_t<pack<int>, pack<float>>;
    static_assert(std::same_as<concatenated, pack<int, float>>);
}
