cmake_minimum_required(VERSION 3.25)

project(createPerformanceTest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(createPerformanceTest main.cpp PerformanceTestGenerator.cpp TestParameters.cpp)

target_compile_features(createPerformanceTest PUBLIC cxx_std_23)

if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    # warning level 4 and all warnings as errors
    target_compile_options(createPerformanceTest PRIVATE /W3 /WX -D_CRT_SECURE_NO_WARNINGS)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        # require at least gcc 12 to get full C++20 support
        if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 12)
            message(FATAL_ERROR "GCC version must be at least 12!")
        endif()
    endif()
    # lots of warnings and all warnings as errors
    target_compile_options(createPerformanceTest PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

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
