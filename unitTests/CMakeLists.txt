cmake_minimum_required(VERSION 3.25)

project(UnitTest LANGUAGES CXX)

enable_testing()

add_executable(ptp_perfTest ptp_performanceTest.cpp)
add_dependencies(ptp_perfTest GeneratedHeader)

add_test(NAME ptp_perfTest COMMAND ptp_perfTest)
set_property(TEST ptp_perfTest PROPERTY PASS_REGULAR_EXPRESSION "PASSED")
set_property(TEST ptp_perfTest PROPERTY FAIL_REGULAR_EXPRESSION "FAILED")

# add_executable(arrayMultiNameMultiID ntp_arrayDupNameDupID.cpp)
# add_test(NAME arrayMultiNameMultiID COMMAND arrayMultiNameMultiID)
# set_property(TEST arrayMultiNameMultiID PROPERTY PASS_REGULAR_EXPRESSION "missing;dupllicate;Duplicate")
# set_property(TEST arrayMultiNameMultiID PROPERTY FAIL_REGULAR_EXPRESSION "FAILED")



