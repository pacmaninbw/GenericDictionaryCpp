cmake_minimum_required(VERSION 3.25)

project(createPerformanceTest LANGUAGES CXX)

add_executable(createPerformanceTest main.cpp PerformanceTestGenerator.cpp TestParameters.cpp)

add_custom_command(
  OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/performanceTest.h
  COMMAND createPerformanceTest --output-file ${CMAKE_CURRENT_SOURCE_DIR}/performanceTest.h --test-count 3 --radix-16 --test-size 10 --test-size 20 --test-size ff --both-tests
  COMMENT "Generating performanceTest.h header file"
  VERBATIM
)

add_custom_target(
  GeneratedHeader ALL
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/performanceTest.h
)
