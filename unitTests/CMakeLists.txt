cmake_minimum_required(VERSION 3.25)

project(UnitTest LANGUAGES CXX)

set(POSITIVE_PATH_TESTS ptp_performanceTest.cpp)
set(NEGATIVE_PATH_TESTS
    ntp_vectorDupID.cpp  ntp_vectorDupName.cpp  ntp_vectorDupNameDupID.cpp
    ntp_arrayDupNameDupID.cpp ntp_arrayDupID.cpp ntp_arrayDupName.cpp
)

enable_testing()

foreach( testsourcefile ${POSITIVE_PATH_TESTS} )
    # Cut off the file extension and directory path
    get_filename_component( testname ${testsourcefile} NAME_WE )
    add_executable( ${testname} ${testsourcefile} )
    if(${testName} MATCHES "ptp_performanceTest")
        add_dependencies(ptp_performanceTest GeneratedHeader)
    endif()
    add_test(NAME ${testname} COMMAND ${testname})
    set_property(TEST ${testname} PROPERTY PASS_REGULAR_EXPRESSION "PASSED")
    set_property(TEST ${testname} PROPERTY FAIL_REGULAR_EXPRESSION "FAILED")
endforeach( testsourcefile ${POSITIVE_PATH_TESTS} )

foreach( testsourcefile ${NEGATIVE_PATH_TESTS} )
    # Cut off the file extension and directory path
    get_filename_component( testname ${testsourcefile} NAME_WE )
    add_executable( ${testname} ${testsourcefile} )
    add_test(NAME ${testname} COMMAND ${testname})
    set_property(TEST ${testname} PROPERTY PASS_REGULAR_EXPRESSION "missing;dupllicate;Duplicate")
    set_property(TEST ${testname} PROPERTY FAIL_REGULAR_EXPRESSION "FAILED")
endforeach( testsourcefile ${NEGATIVE_PATH_TESTS} )



