#include "Container.hpp"
#include "Entity.hpp"
#include "fast_di/dynamic/FastDI.hpp"

#include <cassert>

using fast_di::dynamic_di::DIContainerBuilder;
using fast_di::dynamic_di::DIContainer;

namespace fast_di::benchmarks
{

template<typename T>
static inline bool verify(T& entity)
{
    return entity.method() == ExpectedResultOf<T>;
}

template<typename T>
static inline void test_resolve(DIContainer& container)
{
    T& resolved = container.resolve<T>();
    benchmark::DoNotOptimize(resolved);
    assert(verify(resolved));
}

template<typename T>
static inline void test_resolve(
    DIContainer& container,
    std::string_view tag
) {
    T& resolved = container.resolve<T>(tag);
}

void small_singleton_resolution_bench(benchmark::State& state)
{
    DIContainer container = DIContainerBuilder{}
        .register_singleton<entity::Small>()
            .done()
        .build();

    for (auto _ : state)
    {
        test_resolve<entity::Small>(container);
    }
}

void small_transient_resolution_bench(benchmark::State& state)
{
    DIContainer container = DIContainerBuilder{}
        .register_transient<entity::Small>()
            .done()
        .build();

    for (auto _ : state)
    {
        test_resolve<entity::Small>(container);
    }
}

void small_as_interface_resolution_bench(benchmark::State& state)
{
    DIContainer container = DIContainerBuilder{}
        .register_singleton<entity::Small>()
            .as_interface<entity::Interface>()
            .done()
        .build();

    for (auto _ : state)
    {
        test_resolve<entity::Interface>(container);
    }
}

void small_with_tag_resolution_bench(benchmark::State& state)
{
    const std::string_view tag = "some_tag";
    DIContainer container = DIContainerBuilder{}
        .register_singleton<entity::Small>()
            .with_tag(tag)
            .done()
        .build();

    for (auto _ : state)
    {
        test_resolve<entity::Small>(container, tag);
    }
}

void small_with_dependency_tag_resolution_bench(benchmark::State& state)
{
    for (auto _ : state)
    {

    }
}

void small_constructed_with_resolution_bench(benchmark::State& state)
{
    for (auto _ : state)
    {

    }
}

void small_mixed_configs_resolution_bench(benchmark::State& state)
{
    for (auto _ : state)
    {

    }
}


void average_singleton_resolution_bench(benchmark::State& state)
{
    for (auto _ : state)
    {

    }
}

void average_transient_resolution_bench(benchmark::State& state)
{
    for (auto _ : state)
    {

    }
}

void average_as_interface_resolution_bench(benchmark::State& state)
{
    for (auto _ : state)
    {

    }
}

void average_with_tag_resolution_bench(benchmark::State& state)
{
    for (auto _ : state)
    {

    }
}

void average_with_dependency_tag_resolution_bench(benchmark::State& state)
{
    for (auto _ : state)
    {

    }
}

void average_constructed_with_resolution_bench(benchmark::State& state)
{
    for (auto _ : state)
    {

    }
}

void average_mixed_configs_resolution_bench(benchmark::State& state)
{
    for (auto _ : state)
    {

    }
}


void big_singleton_resolution_bench(benchmark::State& state)
{
    for (auto _ : state)
    {

    }
}

void big_transient_resolution_bench(benchmark::State& state)
{
    for (auto _ : state)
    {

    }
}

void big_as_interface_resolution_bench(benchmark::State& state)
{
    for (auto _ : state)
    {

    }
}

void big_with_tag_resolution_bench(benchmark::State& state)
{
    for (auto _ : state)
    {

    }
}

void big_with_dependency_tag_resolution_bench(benchmark::State& state)
{
    for (auto _ : state)
    {

    }
}

void big_constructed_with_resolution_bench(benchmark::State& state)
{
    for (auto _ : state)
    {

    }
}

void big_mixed_configs_resolution_bench(benchmark::State& state)
{
    for (auto _ : state)
    {

    }
}

void two_level_resolution_bench(benchmark::State& state)
{
    for (auto _ : state)
    {

    }
}

void three_level_resolution_bench(benchmark::State& state)
{
    for (auto _ : state)
    {

    }
}

}
