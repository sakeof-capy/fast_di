#ifndef BUILDER_HPP_
#define BUILDER_HPP_

#include <benchmark/benchmark.h>

namespace fast_di::benchmarks
{

void single_singleton_registration_bench(benchmark::State& state);
void single_transient_registration_bench(benchmark::State& state);
void single_as_interface_registration_bench(benchmark::State& state);
void single_with_tag_registration_bench(benchmark::State& state);
void single_with_dependency_tag_registration_bench(benchmark::State& state);
void single_constructed_with_registration_bench(benchmark::State& state);

void single_mixed_configs_registration_bench(benchmark::State& state);

void multiple_singleton_registration_bench(benchmark::State& state);
void multiple_transient_registration_bench(benchmark::State& state);
void multiple_as_interface_registration_bench(benchmark::State& state);
void multiple_with_tag_registration_bench(benchmark::State& state);
void multiple_with_dependency_tag_registration_bench(benchmark::State& state);
void multiple_constructed_with_registration_bench(benchmark::State& state);

}

#endif //BUILDER_HPP_
