cmake_minimum_required(VERSION 3.16)
project(JavaProjectAnalyzer)

set(CMAKE_CXX_STANDARD 17)

# Core library
add_library(core
    src/thread_pool.cpp
    src/analyzer.cpp
)

target_include_directories(core PUBLIC include)

# Main executable
add_executable(JavaProjectAnalyzer
    src/main.cpp
)

target_link_libraries(JavaProjectAnalyzer core)

set_target_properties(JavaProjectAnalyzer PROPERTIES
    OUTPUT_NAME "analyzer"
)

# GoogleTest
add_subdirectory(external/googletest)

# Tests
add_executable(Tests
    tests/test.cpp
)

target_link_libraries(Tests
    core
    gtest
    gtest_main
)

target_include_directories(Tests PRIVATE include)

set_target_properties(Tests PROPERTIES
    OUTPUT_NAME "tests"
)
