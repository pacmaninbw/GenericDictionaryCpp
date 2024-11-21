cmake_minimum_required(VERSION 3.25)

project(TestDictionary LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

include_directories(. ./unitTests ./src/PerformanceTestGenerator)

if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3")
    # Work around visual studio restrictions
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)

elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    # Let the compiler find as many problems as possible. These flags are common to GCC and Clang
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")

    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        # for some range features and some C++23 features
        if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 12)
            message(FATAL_ERROR "GCC version must be at least 12!")
        endif()

        # for test coverage
        if(CMAKE_BUILD_TYPE MATCHES Debug)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
            set(LINK_LIBRARIES "{LINK_LINK_LIBRARIES} gcov")
        endif()
    endif()
endif()

add_subdirectory(src/PerformanceTestGenerator)
add_subdirectory(src/tests)
add_subdirectory(unitTests)

