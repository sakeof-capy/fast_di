cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES
        src/*
        src/command/*
        src/command/user/*.cpp)
set(LIBRARY_NAME database)

add_library(${LIBRARY_NAME} ${SOURCES})
target_include_directories(${LIBRARY_NAME} PUBLIC ./include/)

target_link_libraries(${LIBRARY_NAME} classic_di)