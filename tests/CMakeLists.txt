include(FetchContent)

cmake_policy(SET CMP0135 NEW)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

IF (WIN32)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
ENDIF()

FetchContent_MakeAvailable(googletest)

enable_testing()

set(EXECUTABLE_NAME tests)
file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(${EXECUTABLE_NAME} ${SOURCES})
target_link_libraries(
    ${EXECUTABLE_NAME}
    GTest::gtest_main
    utilities_di
    dynamic_di
    static_di
    global_di
)

target_include_directories(${EXECUTABLE_NAME} PRIVATE
    $<BUILD_INTERFACE:
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/${EXECUTABLE_NAME}>
    $<INSTALL_INTERFACE:include/${EXECUTABLE_NAME}>
)

include(GoogleTest)
gtest_discover_tests(tests)
