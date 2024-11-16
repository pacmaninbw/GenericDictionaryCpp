cmake_minimum_required(VERSION 3.25)

project(testTest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(testTest testtest.cpp FunctionalityTests.cpp TestGenericDictionary.cpp)
add_dependencies(testTest GeneratedHeader)

target_include_directories(testTest
    PUBLIC ../..
    PRIVATE ./ ../PerformanceTestGenerator 
)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    if(CMAKE_BUILD_TYPE MATCHES Debug)
        target_link_libraries(testTest gcov)
    endif()
endif()

target_compile_features(testTest PUBLIC cxx_std_23)

if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    # warning level 4 and all warnings as errors
    target_compile_options(testTest PRIVATE /W4 /WX -D_CRT_SECURE_NO_WARNINGS)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        # require at least gcc 12 to get full C++20 support
        if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 12)
            message(FATAL_ERROR "GCC version must be at least 12!")
        endif()
    endif()
    # lots of warnings and all warnings as errors
    target_compile_options(testTest PRIVATE -Wall -Wextra -pedantic -Werror)
    if(CMAKE_BUILD_TYPE MATCHES Debug)
        target_compile_options(testTest PRIVATE -fprofile-arcs -ftest-coverage)
    endif()
endif()


