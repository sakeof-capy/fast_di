cmake_minimum_required(VERSION 3.5)
project(fast_di)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BENCHMARK_USE_BUNDLED_GTEST OFF)

add_subdirectory(di_utilities)
add_subdirectory(di_dynamic)
add_subdirectory(di_global)
add_subdirectory(tests)

