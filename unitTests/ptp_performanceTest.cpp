#include <iostream>
#include "performanceTest.h"


int main(void)
{
    std::cout << "EXECUTING PERFORMANCE TESTS\n\n";

    std::string testTitle("All performance tests");

    std::clog << "\n" << testTitle << std::endl;
    std::cout<< "<CTestLabel>" << testTitle << "</CTestLabel>" << std::endl;


    if (!performancetests())
    {
        return EXIT_FAILURE;
    }
    std::cout.flush();

    return EXIT_SUCCESS;
}

