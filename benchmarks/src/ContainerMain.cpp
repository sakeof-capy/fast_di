#include <benchmark/benchmark.h>
#include "Container.hpp"

BENCHMARK(fast_di::benchmarks::small_singleton_resolution_bench);
BENCHMARK(fast_di::benchmarks::small_transient_resolution_bench);
BENCHMARK(fast_di::benchmarks::small_as_interface_resolution_bench);
BENCHMARK(fast_di::benchmarks::small_with_tag_resolution_bench);
BENCHMARK(fast_di::benchmarks::small_with_dependency_tag_resolution_bench);
BENCHMARK(fast_di::benchmarks::small_constructed_with_resolution_bench);
BENCHMARK(fast_di::benchmarks::small_mixed_configs_resolution_bench);
BENCHMARK(fast_di::benchmarks::average_singleton_resolution_bench);
BENCHMARK(fast_di::benchmarks::average_transient_resolution_bench);
BENCHMARK(fast_di::benchmarks::average_as_interface_resolution_bench);
BENCHMARK(fast_di::benchmarks::average_with_tag_resolution_bench);
BENCHMARK(fast_di::benchmarks::average_with_dependency_tag_resolution_bench);
BENCHMARK(fast_di::benchmarks::average_constructed_with_resolution_bench);
BENCHMARK(fast_di::benchmarks::average_mixed_configs_resolution_bench);
BENCHMARK(fast_di::benchmarks::big_singleton_resolution_bench);
BENCHMARK(fast_di::benchmarks::big_transient_resolution_bench);
BENCHMARK(fast_di::benchmarks::big_as_interface_resolution_bench);
BENCHMARK(fast_di::benchmarks::big_with_tag_resolution_bench);
BENCHMARK(fast_di::benchmarks::big_with_dependency_tag_resolution_bench);
BENCHMARK(fast_di::benchmarks::big_constructed_with_resolution_bench);
BENCHMARK(fast_di::benchmarks::big_mixed_configs_resolution_bench);
BENCHMARK(fast_di::benchmarks::two_level_resolution_bench);
BENCHMARK(fast_di::benchmarks::three_level_resolution_bench);

BENCHMARK_MAIN();
