cmake_minimum_required(VERSION 3.5)
project(fast_di)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(FAST_DI_ENABLE_GLOBAL_STATIC_DI "Enable Static Di" ON)

add_subdirectory(di_utilities)
add_subdirectory(di_static)
add_subdirectory(di_dynamic)
add_subdirectory(di_udil)
add_subdirectory(di_global)
add_subdirectory(tests)
