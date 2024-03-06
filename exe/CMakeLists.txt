cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES src/*.cpp)
set(EXECUTABLE_NAME classic_di_exe)

add_executable(${EXECUTABLE_NAME} ${SOURCES}
        src/TaskController.cpp)
target_link_libraries(${EXECUTABLE_NAME} classic_di)