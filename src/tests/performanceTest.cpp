#include <iostream>
#include "performanceTest.h"


int main(void)
{
    std::cout << "EXECUTING PERFORMANCE TESTS\n\n";

    if (!performancetests())
    {
        return EXIT_FAILURE;
    }
    std::cout.flush();

    return EXIT_SUCCESS;
}

