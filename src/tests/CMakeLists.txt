cmake_minimum_required(VERSION 3.25)

project(UnitTest LANGUAGES CXX)

add_executable(arrayMultiNameMultiID arrayMultiNameMultiID.cpp)
add_test(NAME arrayMultiNameMultiID COMMAND arrayMultiNameMultiID)
set_property(TEST arrayMultiNameMultiID PROPERTY PASS_REGULAR_EXPRESSION "PASSED")
set_property(TEST arrayMultiNameMultiID PROPERTY FAIL_REGULAR_EXPRESSION "FAILED")

add_executable(testTest testtest.cpp FunctionalityTests.cpp TestGenericDictionary.cpp)
add_dependencies(testTest GeneratedHeader)

add_executable(perfTest performanceTest.cpp)
add_dependencies(perfTest GeneratedHeader)

enable_testing()

add_test(NAME testTest COMMAND testTest)

set_property(TEST testTest PROPERTY PASS_REGULAR_EXPRESSION "PASSED")
set_property(TEST testTest PROPERTY FAIL_REGULAR_EXPRESSION "FAILED")

add_test(NAME perfTest COMMAND perfTest)

set_property(TEST perfTest PROPERTY PASS_REGULAR_EXPRESSION "PASSED")
set_property(TEST perfTest PROPERTY FAIL_REGULAR_EXPRESSION "FAILED")


