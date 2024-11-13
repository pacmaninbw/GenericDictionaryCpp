cmake_minimum_required(VERSION 3.25)

# Do not attempt to build in parallel using either --parallel or -j
# There can be a race codition between generating the performance test
# header file and building the tests.

project(TestDictionary LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src/PerformanceTestGenerator)
add_subdirectory(src/tests)

