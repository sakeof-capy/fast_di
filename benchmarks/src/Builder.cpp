#include "Builder.hpp"
#include "Entity.hpp"
#include "fast_di/dynamic/FastDI.hpp"

using fast_di::dynamic_di::DIContainerBuilder;
using fast_di::dynamic_di::DIContainer;

namespace fast_di::benchmarks
{

template<typename T>
static bool verify(T& entity)
{
    return entity.method() == ExpectedResultOf<T>;
}

void single_singleton_registration_bench(benchmark::State& state)
{
    for (auto _ : state)
    {
        DIContainer container = DIContainerBuilder{}
            .register_singleton<entity::Dummy<0>>()
                .done()
            .build();

        benchmark::DoNotOptimize(container);
    }
}

void single_transient_registration_bench(benchmark::State& state)
{
    for (auto _ : state)
    {
        DIContainer container = DIContainerBuilder{}
            .register_transient<entity::Dummy<0>>()
                .done()
            .build();

        benchmark::DoNotOptimize(container);
    }
}

void single_as_interface_registration_bench(benchmark::State& state)
{
    for (auto _ : state)
    {
        DIContainer container = DIContainerBuilder{}
            .register_transient<entity::Dummy<0>>()
                .as_interface<entity::Interface>()
                .done()
            .build();

        benchmark::DoNotOptimize(container);
    }
}

void single_with_tag_registration_bench(benchmark::State& state)
{
    for (auto _ : state)
    {
        DIContainer container = DIContainerBuilder{}
            .register_transient<entity::Dummy<0>>()
                .with_tag("some_tag")
                .done()
            .build();

        benchmark::DoNotOptimize(container);
    }
}

void single_with_dependency_tag_registration_bench(benchmark::State& state)
{
    for (auto _ : state)
    {
        DIContainer container = DIContainerBuilder{}
            .register_transient<entity::Dummy<0, int>>()
                .with_tag_of_dependency_at<0>("some_tag")
                .done()
            .build();

        benchmark::DoNotOptimize(container);
    }
}

void single_constructed_with_registration_bench(benchmark::State& state)
{
    for (auto _ : state)
    {
        DIContainer container = DIContainerBuilder{}
            .register_transient<entity::Dummy<0, int, double, float, std::string>>()
                .constructed_with<int, double, float, std::string>()
                .done()
            .build();

        benchmark::DoNotOptimize(container);
    }
}

void single_mixed_configs_registration_bench(benchmark::State& state)
{
    for (auto _ : state)
    {
        DIContainer container = DIContainerBuilder{}
            .register_transient<entity::Dummy<0, int, double, float, std::string>>()
                .constructed_with<int, double, float, std::string>()
                .with_tag_of_dependency_at<1>("some_tag1")
                .with_tag("other_tag")
                .with_tag_of_dependency_at<0>("some_tag0")
                .as_interface<entity::Interface>()
                .with_tag_of_dependency_at<2>("some_tag2")
                .done()
            .build();

        benchmark::DoNotOptimize(container);
    }
}

void multiple_singleton_registration_bench(benchmark::State& state)
{
    for (auto _ : state)
    {
        DIContainer container = DIContainerBuilder{}
                .register_singleton<entity::Dummy<0>>().done()
                .register_singleton<entity::Dummy<1>>().done()
                .register_singleton<entity::Dummy<2>>().done()
                .register_singleton<entity::Dummy<3>>().done()
                .register_singleton<entity::Dummy<4>>().done()
                .register_singleton<entity::Dummy<5>>().done()
                .register_singleton<entity::Dummy<6>>().done()
                .register_singleton<entity::Dummy<7>>().done()
                .register_singleton<entity::Dummy<8>>().done()
                .register_singleton<entity::Dummy<9>>().done()
                .register_singleton<entity::Dummy<10>>().done()
                .register_singleton<entity::Dummy<11>>().done()
                .register_singleton<entity::Dummy<12>>().done()
                .register_singleton<entity::Dummy<13>>().done()
                .register_singleton<entity::Dummy<14>>().done()
                .register_singleton<entity::Dummy<15>>().done()
                .register_singleton<entity::Dummy<16>>().done()
            .build();

        benchmark::DoNotOptimize(container);
    }
}

void multiple_transient_registration_bench(benchmark::State& state)
{
    for (auto _ : state)
    {
        DIContainer container = DIContainerBuilder{}
            .register_transient<entity::Dummy<0>>().done()
            .register_transient<entity::Dummy<1>>().done()
            .register_transient<entity::Dummy<2>>().done()
            .register_transient<entity::Dummy<3>>().done()
            .register_transient<entity::Dummy<4>>().done()
            .register_transient<entity::Dummy<5>>().done()
            .register_transient<entity::Dummy<6>>().done()
            .register_transient<entity::Dummy<7>>().done()
            .register_transient<entity::Dummy<8>>().done()
            .register_transient<entity::Dummy<9>>().done()
            .register_transient<entity::Dummy<10>>().done()
            .register_transient<entity::Dummy<11>>().done()
            .register_transient<entity::Dummy<12>>().done()
            .register_transient<entity::Dummy<13>>().done()
            .register_transient<entity::Dummy<14>>().done()
            .register_transient<entity::Dummy<15>>().done()
            .register_transient<entity::Dummy<16>>().done()
            .build();

        benchmark::DoNotOptimize(container);
    }
}

void multiple_as_interface_registration_bench(benchmark::State& state)
{
    for (auto _ : state)
    {
        DIContainer container = DIContainerBuilder{}
            .register_singleton<entity::Dummy<0>>()
                .as_interface<entity::IdInterface<0>>()
                .done()
            .register_singleton<entity::Dummy<1>>()
                .as_interface<entity::IdInterface<1>>()
                .done()
            .register_singleton<entity::Dummy<2>>()
                .as_interface<entity::IdInterface<2>>()
                .done()
            .register_singleton<entity::Dummy<3>>()
                .as_interface<entity::IdInterface<3>>()
                .done()
            .register_singleton<entity::Dummy<4>>()
                .as_interface<entity::IdInterface<4>>()
                .done()
            .register_singleton<entity::Dummy<5>>()
                .as_interface<entity::IdInterface<5>>()
                .done()
            .register_singleton<entity::Dummy<6>>()
                .as_interface<entity::IdInterface<6>>()
                .done()
            .register_singleton<entity::Dummy<7>>()
                .as_interface<entity::IdInterface<7>>()
                .done()
            .register_singleton<entity::Dummy<8>>()
                .as_interface<entity::IdInterface<8>>()
                .done()
            .register_singleton<entity::Dummy<9>>()
                .as_interface<entity::IdInterface<9>>()
                .done()
            .register_singleton<entity::Dummy<10>>()
                .as_interface<entity::IdInterface<10>>()
                .done()
            .register_singleton<entity::Dummy<11>>()
                .as_interface<entity::IdInterface<11>>()
                .done()
            .register_singleton<entity::Dummy<12>>()
                .as_interface<entity::IdInterface<12>>()
                .done()
            .register_singleton<entity::Dummy<13>>()
                .as_interface<entity::IdInterface<13>>()
                .done()
            .register_singleton<entity::Dummy<14>>()
                .as_interface<entity::IdInterface<14>>()
                .done()
            .register_singleton<entity::Dummy<15>>()
                .as_interface<entity::IdInterface<15>>()
                .done()
            .register_singleton<entity::Dummy<16>>()
                .as_interface<entity::IdInterface<16>>()
                .done()
            .build();

        benchmark::DoNotOptimize(container);
    }
}

void multiple_with_tag_registration_bench(benchmark::State& state)
{
    for (auto _ : state)
    {
        DIContainer container = DIContainerBuilder{}
            .register_singleton<entity::Dummy<0>>()
                .with_tag("some_tag0")
                .done()
            .register_singleton<entity::Dummy<1>>()
                .with_tag("some_tag1")
                .done()
            .register_singleton<entity::Dummy<2>>()
                .with_tag("some_tag2")
                .done()
            .register_singleton<entity::Dummy<3>>()
                .with_tag("some_tag3")
                .done()
            .register_singleton<entity::Dummy<4>>()
                .with_tag("some_tag4")
                .done()
            .register_singleton<entity::Dummy<5>>()
                .with_tag("some_tag5")
                .done()
            .register_singleton<entity::Dummy<6>>()
                .with_tag("some_tag6")
                .done()
            .register_singleton<entity::Dummy<7>>()
                .with_tag("some_tag7")
                .done()
            .register_singleton<entity::Dummy<8>>()
                .with_tag("some_tag8")
                .done()
            .register_singleton<entity::Dummy<9>>()
                .with_tag("some_tag9")
                .done()
            .register_singleton<entity::Dummy<10>>()
                .with_tag("some_tag10")
                .done()
            .register_singleton<entity::Dummy<11>>()
                .with_tag("some_tag11")
                .done()
            .register_singleton<entity::Dummy<12>>()
                .with_tag("some_tag12")
                .done()
            .register_singleton<entity::Dummy<13>>()
                .with_tag("some_tag13")
                .done()
            .register_singleton<entity::Dummy<14>>()
                .with_tag("some_tag14")
                .done()
            .register_singleton<entity::Dummy<15>>()
                .with_tag("some_tag15")
                .done()
            .register_singleton<entity::Dummy<16>>()
                .with_tag("some_tag16")
                .done()
            .build();

        benchmark::DoNotOptimize(container);
    }
}

void multiple_with_dependency_tag_registration_bench(benchmark::State& state)
{
    for (auto _ : state)
    {
        DIContainer container = DIContainerBuilder{}
            .register_transient<entity::Dummy<0, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int>>()
                .with_tag_of_dependency_at<0>("some_tag0")
                .done()
            .register_transient<entity::Dummy<1, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int>>()
                .with_tag_of_dependency_at<1>("some_tag1")
                .done()
            .register_transient<entity::Dummy<2, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int>>()
                .with_tag_of_dependency_at<2>("some_tag2")
                .done()
            .register_transient<entity::Dummy<3, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int>>()
                .with_tag_of_dependency_at<3>("some_tag3")
                .done()
            .register_transient<entity::Dummy<4, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int>>()
                .with_tag_of_dependency_at<4>("some_tag4")
                .done()
            .register_transient<entity::Dummy<5, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int>>()
                .with_tag_of_dependency_at<5>("some_tag5")
                .done()
            .register_transient<entity::Dummy<6, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int>>()
                .with_tag_of_dependency_at<6>("some_tag6")
                .done()
            .register_transient<entity::Dummy<7, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int>>()
                .with_tag_of_dependency_at<7>("some_tag7")
                .done()
            .register_transient<entity::Dummy<8, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int>>()
                .with_tag_of_dependency_at<8>("some_tag8")
                .done()
            .register_transient<entity::Dummy<9, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int>>()
                .with_tag_of_dependency_at<9>("some_tag9")
                .done()
            .register_transient<entity::Dummy<10, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int>>()
                .with_tag_of_dependency_at<10>("some_tag10")
                .done()
            .register_transient<entity::Dummy<11, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int>>()
                .with_tag_of_dependency_at<11>("some_tag11")
                .done()
            .register_transient<entity::Dummy<12, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int>>()
                .with_tag_of_dependency_at<12>("some_tag12")
                .done()
            .register_transient<entity::Dummy<13, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int>>()
                .with_tag_of_dependency_at<13>("some_tag13")
                .done()
            .register_transient<entity::Dummy<14, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int>>()
                .with_tag_of_dependency_at<14>("some_tag14")
                .done()
            .register_transient<entity::Dummy<15, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int>>()
                .with_tag_of_dependency_at<15>("some_tag15")
                .done()
            .register_transient<entity::Dummy<16, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int>>()
                .with_tag_of_dependency_at<16>("some_tag16")
                .done()
            .build();

        benchmark::DoNotOptimize(container);
    }
}

void multiple_constructed_with_registration_bench(benchmark::State& state)
{
    for (auto _ : state)
    {
        DIContainer container = DIContainerBuilder{}
            .register_singleton<entity::Dummy<0, int, double, float, int, int, double, float, int, int, double, float, int, int, double, float, int>>()
                .constructed_with<int, double, float, int, int, double, float, int, int, double, float, int, int, double, float, int>()
                .done()
            .register_singleton<entity::Dummy<1, int, double, float, int, int, double, float, int, int, double, float, int, int, double, float, int>>()
                .constructed_with<int, double, float, int, int, double, float, int, int, double, float, int, int, double, float, int>()
                .done()
            .register_singleton<entity::Dummy<2, int, double, float, int, int, double, float, int, int, double, float, int, int, double, float, int>>()
                .constructed_with<int, double, float, int, int, double, float, int, int, double, float, int, int, double, float, int>()
                .done()
            .register_singleton<entity::Dummy<3, int, double, float, int, int, double, float, int, int, double, float, int, int, double, float, int>>()
                .constructed_with<int, double, float, int, int, double, float, int, int, double, float, int, int, double, float, int>()
                .done()
            .register_singleton<entity::Dummy<4, int, double, float, int, int, double, float, int, int, double, float, int, int, double, float, int>>()
                .constructed_with<int, double, float, int, int, double, float, int, int, double, float, int, int, double, float, int>()
                .done()
            .register_singleton<entity::Dummy<5, int, double, float, int, int, double, float, int, int, double, float, int, int, double, float, int>>()
                .constructed_with<int, double, float, int, int, double, float, int, int, double, float, int, int, double, float, int>()
                .done()
            .register_singleton<entity::Dummy<6, int, double, float, int, int, double, float, int, int, double, float, int, int, double, float, int>>()
                .constructed_with<int, double, float, int, int, double, float, int, int, double, float, int, int, double, float, int>()
                .done()
            .register_singleton<entity::Dummy<7, int, double, float, int, int, double, float, int, int, double, float, int, int, double, float, int>>()
                .constructed_with<int, double, float, int, int, double, float, int, int, double, float, int, int, double, float, int>()
                .done()
            .register_singleton<entity::Dummy<8, int, double, float, int, int, double, float, int, int, double, float, int, int, double, float, int>>()
                .constructed_with<int, double, float, int, int, double, float, int, int, double, float, int, int, double, float, int>()
                .done()
            .register_singleton<entity::Dummy<9, int, double, float, int, int, double, float, int, int, double, float, int, int, double, float, int>>()
                .constructed_with<int, double, float, int, int, double, float, int, int, double, float, int, int, double, float, int>()
                .done()
            .register_singleton<entity::Dummy<10, int, double, float, int, int, double, float, int, int, double, float, int, int, double, float, int>>()
                .constructed_with<int, double, float, int, int, double, float, int, int, double, float, int, int, double, float, int>()
                .done()
            .register_singleton<entity::Dummy<11, int, double, float, int, int, double, float, int, int, double, float, int, int, double, float, int>>()
                .constructed_with<int, double, float, int, int, double, float, int, int, double, float, int, int, double, float, int>()
                .done()
            .register_singleton<entity::Dummy<12, int, double, float, int, int, double, float, int, int, double, float, int, int, double, float, int>>()
                .constructed_with<int, double, float, int, int, double, float, int, int, double, float, int, int, double, float, int>()
                .done()
            .register_singleton<entity::Dummy<13, int, double, float, int, int, double, float, int, int, double, float, int, int, double, float, int>>()
                .constructed_with<int, double, float, int, int, double, float, int, int, double, float, int, int, double, float, int>()
                .done()
            .register_singleton<entity::Dummy<14, int, double, float, int, int, double, float, int, int, double, float, int, int, double, float, int>>()
                .constructed_with<int, double, float, int, int, double, float, int, int, double, float, int, int, double, float, int>()
                .done()
            .register_singleton<entity::Dummy<15, int, double, float, int, int, double, float, int, int, double, float, int, int, double, float, int>>()
                .constructed_with<int, double, float, int, int, double, float, int, int, double, float, int, int, double, float, int>()
                .done()
            .register_singleton<entity::Dummy<16, int, double, float, int, int, double, float, int, int, double, float, int, int, double, float, int>>()
                .constructed_with<int, double, float, int, int, double, float, int, int, double, float, int, int, double, float, int>()
                .done()
            .build();

        benchmark::DoNotOptimize(container);
    }
}

}
