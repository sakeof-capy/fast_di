set(LIBRARY_NAME global_di)
add_library(${LIBRARY_NAME} INTERFACE)

if(FAST_DI_ENABLE_GLOBAL_STATIC_DI)
    message("FAST_DI_ENABLE_GLOBAL_STATIC_DI is defined; linking global static...")
    target_compile_definitions(${LIBRARY_NAME} INTERFACE -DFAST_DI_ENABLE_GLOBAL_STATIC_DI)
    target_link_libraries(${LIBRARY_NAME} INTERFACE static_di)
else()
    message("FAST_DI_ENABLE_GLOBAL_STATIC_DI is not defined; linking global dynamic...")
    target_link_libraries(${LIBRARY_NAME} INTERFACE dynamic_di)
endif()

target_include_directories(${LIBRARY_NAME} INTERFACE
    $<BUILD_INTERFACE:
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/${LIBRARY_NAME}>
    $<INSTALL_INTERFACE:include/>
)
