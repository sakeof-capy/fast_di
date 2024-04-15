file(GLOB SOURCES src/*.cpp)
set(EXECUTABLE_NAME smtp_bin)

add_executable(${EXECUTABLE_NAME} ${SOURCES})
target_link_libraries(${EXECUTABLE_NAME} database)
target_link_libraries(${EXECUTABLE_NAME} classic_di)