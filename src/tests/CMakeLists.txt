cmake_minimum_required(VERSION 3.25)

project(testTest LANGUAGES CXX)

add_executable(testTest testtest.cpp FunctionalityTests.cpp TestGenericDictionary.cpp)
add_dependencies(testTest GeneratedHeader)

add_executable(perfTest performanceTest.cpp)
add_dependencies(perfTest GeneratedHeader)

enable_testing()

add_test(NAME testTest COMMAND testTest)

set_property(TEST testTest PROPERTY PASS_REGULAR_EXPRESSION "PASSED")
set_property(TEST testTest PROPERTY FAIL_REGULAR_EXPRESSION "FAILED")

add_test(NAME perfTest COMMAND testTest)

set_property(TEST perfTest PROPERTY PASS_REGULAR_EXPRESSION "PASSED")
set_property(TEST perfTest PROPERTY FAIL_REGULAR_EXPRESSION "FAILED")


