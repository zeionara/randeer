cmake_minimum_required(VERSION 3.16.3)

project(randeer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -pthread -march=native")
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/release)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

# Set up the core library

file(
    GLOB_RECURSE SOURCES_FILES "src/randeer/*.cpp"
)

set(
    SOURCES
    ${SOURCES_FILES}
)

add_library(randeer ${SOURCES})

install(TARGETS randeer DESTINATION /usr/lib/)

# Set up tests

enable_testing()

function(push_test name path)
    add_executable(${name} test/${path})
    target_link_libraries(${name} PRIVATE randeer)
    add_test(NAME ${name} COMMAND ${name})
endfunction()

function(push_test name)
    add_executable(${name} test/${name}.cpp)
    target_link_libraries(${name} PRIVATE randeer)
    add_test(NAME ${name} COMMAND ${name})
endfunction()

# push_test(LcgRandomizationState LcgRandomizationState.cpp)
push_test(LcgRandomizationState)
push_test(JavaLikeLcgRandomizationState)
push_test(ShiftingRandomizer)
