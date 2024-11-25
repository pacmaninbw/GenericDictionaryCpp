#include <array>
#include "commonFunctTest.h"
#include "GenericDictionary.h"
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

int main()
{
    std::string testTitle("Initized using Array: Expect Lookup Failures");

    std::clog << "\n" << testTitle << std::endl;
    std::cout<< "<CTestLabel>" << testTitle << "</CTestLabel>" << std::endl;

    std::array<TestDataPair, 17> positivePathArray = copyVecToArray(testPostivePathVec);

    try
    {
        GenericDictionary<TestFunctionalityEnumDict, std::string> dictionary(positivePathArray);

        // Constructor did not throw exception, test lookup functions
        auto checkID = dictionary.lookupID("Should not found");
        if (checkID.has_value())
        {
            std::cerr << "Found \"Should not found\"" << std::endl;
            return EXIT_FAILURE;
        }
        else
        {
            std::cerr << "Name not found in Dictionary: \"Functional Test Str 0\"" << std::endl;
        }

        auto checkName = dictionary.lookupName(static_cast<TestFunctionalityEnumDict>(ForceIDFail));
        if (checkName.has_value())
        {
            std::cerr << "Found \"ForceIDFail\"" << std::endl;
            return EXIT_FAILURE;
        }
        else
        {
            std::cerr << "ID not found in Dictionary: TestFunctionalityEnumDict::FunctionalTest_15" << std::endl;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << testTitle << " CAUGHT EXCEPTION: " << e.what() << "\n\n";
        std::clog.flush();
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}