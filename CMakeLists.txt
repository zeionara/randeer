cmake_minimum_required(VERSION 3.16.3)

project(randeer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -pthread -march=native")
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/release)

file(
    GLOB_RECURSE SOURCES_FILES "randeer/*.cpp"
)

set(
    SOURCES
    ${SOURCES_FILES}
)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

add_library(randeer ${SOURCES})

install(TARGETS randeer DESTINATION /usr/lib/)

