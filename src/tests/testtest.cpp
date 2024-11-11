#define DEBUG
#include "FunctionalityTests.h"
#include <iostream>
#include "performanceTest.h"
#include "TestGenericDictionary.h"


int main(void)
{
	if (!executeAllFuntionalTests())
    {
        return EXIT_FAILURE;
    }

    TestGenericDictionary genericDicionaryTest;
    if (!genericDicionaryTest.executeTests())
    {
        return EXIT_FAILURE;
    }
    std::cout.flush();

    std::cout << "EXECUTING PERFORMANCE TESTS\n\n";

    if (!performancetests())
    {
        return EXIT_FAILURE;
    }
    std::cout.flush();

    return EXIT_SUCCESS;
}

