set(LIBRARY_NAME static_di)
add_library(${LIBRARY_NAME} INTERFACE)

target_link_libraries(${LIBRARY_NAME} INTERFACE utilities_di)

target_include_directories(${LIBRARY_NAME} INTERFACE
    $<BUILD_INTERFACE:
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/${LIBRARY_NAME}>
    $<INSTALL_INTERFACE:include/>
)
