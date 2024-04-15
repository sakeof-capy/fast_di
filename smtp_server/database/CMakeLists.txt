include(FetchContent)

file(GLOB SOURCES
        src/*.cpp
        #src/connection/*.cpp
        src/command/*.cpp
        src/command/user/*.cpp)
set(LIBRARY_NAME database)

add_library(${LIBRARY_NAME} ${SOURCES})
target_include_directories(${LIBRARY_NAME} PUBLIC ./include/)

target_link_libraries(${LIBRARY_NAME} INTERFACE classic_di)

#find_package(libpqxx)
#if (libpqxx_FOUND)
#    target_link_libraries(${LIBRARY_NAME} PRIVATE libpqxx::pqxx)
#else()
#    FetchContent_Declare(
#            libpqxx
#            GIT_REPOSITORY https://github.com/jtv/libpqxx.git
#            GIT_TAG a6b1d60e74c1427c8ac2324b85cd4a0dc2068332
#    )
#
#    set(PQXX_LIBRARIES pqxx_static)
#
#    FetchContent_MakeAvailable(libpqxx)
#
#    target_link_libraries(${LIBRARY_NAME} PRIVATE "${PQXX_LIBRARIES}")
#endif()