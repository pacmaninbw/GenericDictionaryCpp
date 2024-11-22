#include "commonFunctTest.h"
#include "GenericDictionary.h"
#include <exception>
#include <initializer_list>
#include <iostream>
#include <stdexcept>
#include <string>

int main()
{
    std::string testTitle("Initized using Initialization List: Expect Lookup Failures");

    std::clog << "\n" << testTitle << std::endl;
    std::cout<< "<CTestLabel>" << testTitle << "</CTestLabel>" << std::endl;

    try
    {
        GenericDictionary<TestFunctionalityEnumDict, std::string> dictionary(
            {
                {TestFunctionalityEnumDict::FunctionalTest_0, "Functional Test Str 0"},
                {TestFunctionalityEnumDict::FunctionalTest_1, "Functional Test Str 1"},
                {TestFunctionalityEnumDict::FunctionalTest_2, "Functional Test Str 2"},
                {TestFunctionalityEnumDict::FunctionalTest_3, "Functional Test Str 3"},
                {TestFunctionalityEnumDict::FunctionalTest_4, "Functional Test Str 4"},
                {TestFunctionalityEnumDict::FunctionalTest_5, "Functional Test Str 5"},
                {TestFunctionalityEnumDict::FunctionalTest_6, "Functional Test Str 6"},
                {TestFunctionalityEnumDict::FunctionalTest_7, "Functional Test Str 7"},
                {TestFunctionalityEnumDict::FunctionalTest_8, "Functional Test Str 8"},
                {TestFunctionalityEnumDict::FunctionalTest_9, "Functional Test Str 9"},
                {TestFunctionalityEnumDict::FunctionalTest_10, "Functional Test Str 10"},
                {TestFunctionalityEnumDict::FunctionalTest_11, "Functional Test Str 11"},
                {TestFunctionalityEnumDict::FunctionalTest_12, "Functional Test Str 12"},
                {TestFunctionalityEnumDict::FunctionalTest_13, "Functional Test Str 13"},
                {TestFunctionalityEnumDict::FunctionalTest_14, "Functional Test Str 14"},
                {TestFunctionalityEnumDict::FunctionalTest_15, "Functional Test Str 15"},
                {TestFunctionalityEnumDict::FunctionalTest_16, "Functional Test Str 16"}
            }
        );

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