cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LIBRARY_NAME global_di)
set(DI_TARGET_EXAMPLE_NAME di_target_example)

add_executable(RUN_EXAMPLE src/main.cpp src/DITargetExample.cpp)
target_link_libraries(RUN_EXAMPLE PUBLIC classic_di)
add_executable(${DI_TARGET_EXAMPLE_NAME} src/DITargetExample.cpp)
target_link_libraries(${DI_TARGET_EXAMPLE_NAME} PUBLIC classic_di)

#add_library(${LIBRARY_NAME} INTERFACE)
#target_include_directories(${LIBRARY_NAME}
#        INTERFACE
#        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#        $<INSTALL_INTERFACE:include>
#)

