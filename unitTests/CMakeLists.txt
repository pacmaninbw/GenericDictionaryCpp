cmake_minimum_required(VERSION 3.25)

project(UnitTest LANGUAGES CXX)

set(POSITIVE_PATH_TESTS ptp_vector.cpp ptp_array.cpp ptp_initList.cpp )
set(NEGATIVE_PATH_TESTS
    ntp_initListDupNameDupID.cpp ntp_initListDupID.cpp ntp_initListDupName.cpp
    ntp_vectorDupID.cpp  ntp_vectorDupName.cpp  ntp_vectorDupNameDupID.cpp
    ntp_arrayDupNameDupID.cpp ntp_arrayDupID.cpp ntp_arrayDupName.cpp
    ntp_arrayLookupFail.cpp ntp_vectorLookupFail.cpp ntp_initListLookupFail.cpp
)

enable_testing()

# Special case because of the dependency on the performanceTest.h header file.
add_executable(ptp_performanceTest ptp_performanceTest.cpp commonFunctTest.cpp)
add_dependencies(ptp_performanceTest GeneratedHeader)
add_test(NAME ptp_performanceTest COMMAND ptp_performanceTest)
set_property(TEST ptp_performanceTest PROPERTY PASS_REGULAR_EXPRESSION "PASSED")
set_property(TEST ptp_performanceTest PROPERTY FAIL_REGULAR_EXPRESSION "FAILED;missing;duplicate;Duplicate;Wrong enum;Name not found;Wrong name;ID not found")

foreach( testsourcefile ${POSITIVE_PATH_TESTS} )
    # Cut off the file extension and directory path
    get_filename_component( testname ${testsourcefile} NAME_WE )
    add_executable( ${testname} ${testsourcefile} commonFunctTest.cpp)
    add_test(NAME ${testname} COMMAND ${testname})
    set_property(TEST ${testname} PROPERTY PASS_REGULAR_EXPRESSION "PASSED")
    set_property(TEST ${testname} PROPERTY FAIL_REGULAR_EXPRESSION "FAILED;missing;duplicate;Duplicate;Wrong enum;Name not found;Wrong name;ID not found")
endforeach( testsourcefile ${POSITIVE_PATH_TESTS} )

foreach( testsourcefile ${NEGATIVE_PATH_TESTS} )
    # Cut off the file extension and directory path
    get_filename_component( testname ${testsourcefile} NAME_WE )
    add_executable( ${testname} ${testsourcefile} commonFunctTest.cpp )
    add_test(NAME ${testname} COMMAND ${testname})
    set_property(TEST ${testname} PROPERTY PASS_REGULAR_EXPRESSION "missing;duplicate;Duplicate;Wrong enum;Name not found;Wrong name;ID not found")
    set_property(TEST ${testname} PROPERTY FAIL_REGULAR_EXPRESSION "FAILED")
endforeach( testsourcefile ${NEGATIVE_PATH_TESTS} )



