set(EXECUTABLE_NAME benchmarks)
file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(${EXECUTABLE_NAME} ${SOURCES})
target_link_libraries(
    ${EXECUTABLE_NAME}
    benchmark::benchmark
    dynamic_di
)

target_include_directories(${EXECUTABLE_NAME} PRIVATE
    $<BUILD_INTERFACE:
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/${EXECUTABLE_NAME}>
    $<INSTALL_INTERFACE:include/${EXECUTABLE_NAME}>
)
