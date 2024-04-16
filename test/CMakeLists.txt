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

file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(tests ${SOURCES})
target_link_libraries(
    tests
    GTest::gtest_main
    classic_di
)

include(GoogleTest)
gtest_discover_tests(tests)
