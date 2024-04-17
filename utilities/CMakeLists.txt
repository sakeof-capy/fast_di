set(LIBRARY_NAME di_utilities)

add_library(${LIBRARY_NAME} INTERFACE)

target_include_directories(${LIBRARY_NAME}
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)