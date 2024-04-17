cmake_minimum_required(VERSION 3.5)
project(FAST_DI_LIBS VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(utilities)
add_subdirectory(classic_di)
add_subdirectory(fast_di)
add_subdirectory(exe)
add_subdirectory(smtp_server)
add_subdirectory(global_di)
add_subdirectory(test)