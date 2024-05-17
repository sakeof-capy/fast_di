#ifndef CONTAINER_HPP_
#define CONTAINER_HPP_

#include <benchmark/benchmark.h>

namespace fast_di::benchmarks
{

void small_singleton_resolution_bench(benchmark::State& state);
void small_transient_resolution_bench(benchmark::State& state);
void small_as_interface_resolution_bench(benchmark::State& state);
void small_with_tag_resolution_bench(benchmark::State& state);
void small_with_dependency_tag_resolution_bench(benchmark::State& state);
void small_constructed_with_resolution_bench(benchmark::State& state);
void small_mixed_configs_resolution_bench(benchmark::State& state);

void average_singleton_resolution_bench(benchmark::State& state);
void average_transient_resolution_bench(benchmark::State& state);
void average_as_interface_resolution_bench(benchmark::State& state);
void average_with_tag_resolution_bench(benchmark::State& state);
void average_with_dependency_tag_resolution_bench(benchmark::State& state);
void average_constructed_with_resolution_bench(benchmark::State& state);
void average_mixed_configs_resolution_bench(benchmark::State& state);

void big_singleton_resolution_bench(benchmark::State& state);
void big_transient_resolution_bench(benchmark::State& state);
void big_as_interface_resolution_bench(benchmark::State& state);
void big_with_tag_resolution_bench(benchmark::State& state);
void big_with_dependency_tag_resolution_bench(benchmark::State& state);
void big_constructed_with_resolution_bench(benchmark::State& state);
void big_mixed_configs_resolution_bench(benchmark::State& state);

void two_level_resolution_bench(benchmark::State& state);
void three_level_resolution_bench(benchmark::State& state);

}

#endif //CONTAINER_HPP_
