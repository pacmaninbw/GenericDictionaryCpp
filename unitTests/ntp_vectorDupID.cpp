#include "commonFunctTest.h"
#include "GenericDictionary.h"
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

int main()
{
    std::string testTitle("Initized using Vector: multiple IDs");

    std::clog << "\n" << testTitle << std::endl;
    std::cout<< "<CTestLabel>" << testTitle << "</CTestLabel>" << std::endl;

    try
    {
        GenericDictionary<TestFunctionalityEnumDict, std::string> dictionary(testVecMultiID);

        auto checkID = dictionary.lookupID("Functional Test Str 0");
        TestFunctionalityEnumDict testEnum;
        if (checkID.has_value())
        {
            testEnum = *checkID;
            if (testEnum != TestFunctionalityEnumDict::FunctionalTest_0)
            {
                std::cerr << "Wrong enum value returned from Dictionary: expected 0 actual " << static_cast<std::size_t>(testEnum) << std::endl;
                return EXIT_FAILURE;
            }
        }
        else
        {
            std::cerr << "Name not found in Dictionary: \"Functional Test Str 0\"" << std::endl;
            return EXIT_FAILURE;
        }

        std::string testName;
        auto checkName = dictionary.lookupName(TestFunctionalityEnumDict::FunctionalTest_15);
        if (checkName.has_value())
        {
            testName = *checkName;
            if (testName != "Functional Test Str 15")
            {
                std::cerr << "Wrong name returned from Dictionary: expected \"Functional Test Str 15\" actual " << testName << std::endl;
                return EXIT_FAILURE;
            }
        }
        else
        {
            std::cerr << "ID not found in Dictionary: TestFunctionalityEnumDict::FunctionalTest_15" << std::endl;
            return EXIT_FAILURE;
        }
        // Should throw exception from constructor.
        return EXIT_FAILURE;
    }
    catch(const std::exception& e)
    {
        std::cerr << testTitle << " CAUGHT EXCEPTION: " << e.what() << "\n\n";
        std::clog.flush();
        return EXIT_FAILURE;
    }
    

    return EXIT_SUCCESS;
}