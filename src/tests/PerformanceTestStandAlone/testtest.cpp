#define DEBUG
#include "FunctionalityTests.h"
#include <iostream>
#include "../PerformanceTestGenerator/performanceTest.h"
#include "TestGenericDictionary.h"


int main(void)
{
	FunctionalityTests unitTest;
	if (!unitTest.executeAllTests())
    {
        return EXIT_FAILURE;
    }

    TestGenericDictionary genericDicionaryTest;
    if (!genericDicionaryTest.executeTests())
    {
        return EXIT_FAILURE;
    }

    std::cout << "EXECUTING PERFORMANCE TESTS\n\n";

    if (!performancetests())
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

