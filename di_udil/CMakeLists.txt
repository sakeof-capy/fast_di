set(LIBRARY_NAME udil_di)
add_library(${LIBRARY_NAME} INTERFACE)
target_link_libraries(${LIBRARY_NAME} INTERFACE utilities_di static_di)

if(FAST_DI_ENABLE_GLOBAL_STATIC_DI)
    message("FAST_DI_ENABLE_GLOBAL_STATIC_DI is defined; providing static UDIL...")
    target_compile_definitions(${LIBRARY_NAME} INTERFACE -DFAST_DI_ENABLE_GLOBAL_STATIC_DI)
else()
    message("FAST_DI_ENABLE_GLOBAL_STATIC_DI is not defined; providing dynamic UDIL...")
endif()

target_include_directories(${LIBRARY_NAME} INTERFACE
    $<BUILD_INTERFACE:
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/${LIBRARY_NAME}>
    $<INSTALL_INTERFACE:include/>
)
