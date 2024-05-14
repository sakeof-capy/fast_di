#include <benchmark/benchmark.h>
#include "Builder.hpp"

BENCHMARK(fast_di::benchmarks::single_singleton_registration_bench);
BENCHMARK(fast_di::benchmarks::single_transient_registration_bench);
BENCHMARK(fast_di::benchmarks::single_as_interface_registration_bench);
BENCHMARK(fast_di::benchmarks::single_with_tag_registration_bench);
BENCHMARK(fast_di::benchmarks::single_with_dependency_tag_registration_bench);
BENCHMARK(fast_di::benchmarks::single_constructed_with_registration_bench);
BENCHMARK(fast_di::benchmarks::single_mixed_configs_registration_bench);
BENCHMARK(fast_di::benchmarks::multiple_singleton_registration_bench);
BENCHMARK(fast_di::benchmarks::multiple_transient_registration_bench);
BENCHMARK(fast_di::benchmarks::multiple_as_interface_registration_bench);
BENCHMARK(fast_di::benchmarks::multiple_with_tag_registration_bench);
BENCHMARK(fast_di::benchmarks::multiple_with_dependency_tag_registration_bench);
BENCHMARK(fast_di::benchmarks::multiple_constructed_with_registration_bench);

BENCHMARK_MAIN();