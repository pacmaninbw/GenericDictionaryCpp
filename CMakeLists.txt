cmake_minimum_required(VERSION 3.25)

project(TestDictionary LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src/PerformanceTestGenerator)
add_subdirectory(src/tests)

