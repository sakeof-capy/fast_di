cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES src/*.cpp)
set(LIBRARY_NAME fast_di)

add_library(${LIBRARY_NAME} STATIC ${SOURCES})

target_include_directories(${LIBRARY_NAME} PRIVATE
        $<BUILD_INTERFACE:
        ${CMAKE_CURRENT_SOURCE_DIR}/include/private/${LIBRARY_NAME}
        ${CMAKE_CURRENT_SOURCE_DIR}/include/public/${LIBRARY_NAME}>
        $<INSTALL_INTERFACE:
        include/private/${LIBRARY_NAME}
        include/public/${LIBRARY_NAME}>
)