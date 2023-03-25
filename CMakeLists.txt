cmake_minimum_required(VERSION 3.16.3)

project(randeer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -pthread -march=native")
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/release)

file(
    GLOB_RECURSE SOURCES_FILES "src/randeer/*.cpp"
)

set(
    SOURCES
    ${SOURCES_FILES}
)

# file(
#     GLOB_RECURSE TEST_SOURCES_FILES "test/*.cpp"
# )

# set(
#     TEST_SOURCES
#     ${TEST_SOURCES_FILES}
# )

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

add_library(randeer ${SOURCES})
# add_executable(test ${TEST_SOURCES})
add_executable(test_foo test/main.cpp)

target_link_libraries(test_foo PRIVATE randeer)

enable_testing()

add_test(
    NAME test_foo
    COMMAND $<TARGET_FILE:test_foo>
)

install(TARGETS randeer DESTINATION /usr/lib/)
