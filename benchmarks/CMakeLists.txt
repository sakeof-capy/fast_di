set(MODULE_NAME benchmarks)

add_executable(benchmarks_builder
    src/Builder.cpp
    src/BuilderMain.cpp
)

target_link_libraries(
    benchmarks_builder
    benchmark::benchmark
    dynamic_di
)

add_executable(benchmarks_container
    src/Container.cpp
    src/ContainerMain.cpp
)

target_link_libraries(
    benchmarks_container
    benchmark::benchmark
    dynamic_di
)

target_include_directories(benchmarks_builder PRIVATE
    $<BUILD_INTERFACE:
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/${MODULE_NAME}>
    $<INSTALL_INTERFACE:include/${MODULE_NAME}>
)

target_include_directories(benchmarks_container PRIVATE
    $<BUILD_INTERFACE:
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/${MODULE_NAME}>
    $<INSTALL_INTERFACE:include/${MODULE_NAME}>
)
