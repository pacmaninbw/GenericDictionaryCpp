#define GD_UNIT_TEST
#define DEBUG

#include <array>
#include "FunctionalityTests.h"
#include "../../include/GenericDictionary.h"
#include <exception>
#include <initializer_list>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

enum class TestAdditions
{
	NewAdd_Invalid_enum_Value,
	NewAddValue_1,
	NewAddValue_2,
	NewAddValue_3,
	NewAddValue_4,
	NewAddValue_5,
	NewAddValue_6,
	NewAddValue_7,
	NewAddValue_8,
	NewAddValue_9,
	NewAddValue_10,
	NewAddValue_11,
	NewAddValue_12,
	NewAddValue_13,
	NewAddValue_14,
	NewAddValue_15,
	NewAddValue_16,
	NewAddLast_Enum
};

std::vector<GenricDictionaryDataPair<TestAdditions, std::string>> newAddtestVec = 
{
	{TestAdditions::NewAddValue_1, "New funct 1"},
	{TestAdditions::NewAddValue_2, "New funct 2"},
	{TestAdditions::NewAddValue_3, "New funct 3"},
	{TestAdditions::NewAddValue_4, "New funct 4"},
	{TestAdditions::NewAddValue_5, "New funct 5"},
	{TestAdditions::NewAddValue_6, "New funct 6"},
	{TestAdditions::NewAddValue_7, "New funct 7"},
	{TestAdditions::NewAddValue_8, "New funct 8"},
	{TestAdditions::NewAddValue_9, "New funct 9"},
	{TestAdditions::NewAddValue_10, "New funct 10"},
	{TestAdditions::NewAddValue_11, "New funct 11"},
	{TestAdditions::NewAddValue_12, "New funct 12"},
	{TestAdditions::NewAddValue_13, "New funct 13"},
	{TestAdditions::NewAddValue_14, "New funct 14"},
	{TestAdditions::NewAddValue_15, "New funct 15"},
	{TestAdditions::NewAddValue_16, "New funct 16"}
};

static bool didConstructionWork(
    std::string testName,
    GenericDictionary<TestAdditions, std::string> dictionary,
    std::size_t itemToTest
) noexcept
{
    bool testPassed = true;
    std::vector<GenricDictionaryDataPair<TestAdditions, std::string>> userInput = dictionary.getUserInput();
    std::size_t idIntVal = static_cast<std::size_t>(userInput[itemToTest].id);
    std::string strVal = userInput[itemToTest].names;

    std::cout << "\ttesting " << testName << ".getNames(" << idIntVal << "), expected output is " << strVal << "\n";
    if (dictionary.getNames(userInput[itemToTest].id) != strVal)
    {
        std::cerr << "\t" << testName << ".getNames(" << idIntVal << ") FAILED\n";
        testPassed = false;
    }
    else
    {
        std::cout << "\t" << testName << ".getNames(" << idIntVal << ") PASSED\n";
    }

    std::cout << "\ttesting " << testName << ".getIds(" << strVal << "), expected output is "
    << idIntVal << "\n";

    if (dictionary.getIds(strVal) != userInput[itemToTest].id)
    {
        std::cerr << "\t" << testName << ".getIds(" << strVal << ") FAILED\n";
        testPassed = false;
    }
    else
    {
        std::cout << "\t" << testName << ".getIds(" << strVal << ") PASSED\n";
    }

    return testPassed;
}

bool FunctionalityTests::executeAllTests() noexcept
{
    bool allTestsPassed = true;

    if (!defaultConstructorSelfTests())
    {
        allTestsPassed = false;
    }

    if (!defaultConstructorAddVector())
    {
        allTestsPassed = false;
    }

    if (!defaultConstructorAddArray())
    {
        allTestsPassed = false;
    }

    if (!defaultConstructorAddInitializerList())
    {
        allTestsPassed = false;
    }

    if (!limitsConstructorAddVector())
    {
        allTestsPassed = false;
    }

    if (!limitsConstructorAddArray())
    {
        allTestsPassed = false;
    }

    if (!limitsConstructorAddInitializerList())
    {
        allTestsPassed = false;
    }

    std::cout << "FUNCTIONAL TEST EXECUTION COMPLETE\n\n";

    return allTestsPassed;
}

bool FunctionalityTests::defaultConstructorSelfTests() noexcept
{
    bool testPassed = true;

    return testPassed;
}

bool FunctionalityTests::defaultConstructorAddVector() noexcept
{
    bool testPassed = true;

    std::cout << "testing testMyNewAdditions Default Constructor\n";
    GenericDictionary<TestAdditions, std::string> testMyNewAdditions;
    std::cout << "testing testMyNewAdditions.addAllDefinitions(TestAdditions::NewAdd_Invalid_enum_Value, TestAdditions::NewAddLast_Enum, newAddtestVec)\n";
    if (testMyNewAdditions.addAllDefinitions(TestAdditions::NewAdd_Invalid_enum_Value, TestAdditions::NewAddLast_Enum, newAddtestVec))
    {
        testPassed = didConstructionWork("testMyNewAdditions", testMyNewAdditions, 1);
    }
    else
    {
        std::cerr << "\ttesting testMyNewAdditions.addAllDefinitions(newAddtestVec) FAILED\n";
        testPassed = false;
#ifdef DEBUG
        testMyNewAdditions.debugDumpData();
        testMyNewAdditions.debugDumpUserList();
#endif
    }

    return testPassed;
}

bool FunctionalityTests::defaultConstructorAddArray() noexcept
{
    bool testPassed = true;

	std::array<GenricDictionaryDataPair<TestAdditions, std::string>,16> newAddArray;
    std::size_t i = 0;
	for (auto tdata: newAddtestVec)
	{
		newAddArray[i] = tdata;
        ++i;
	}

    std::cout << "\ntesting Constructor with limits\n";
    GenericDictionary<TestAdditions, std::string> testArray;
    std::cout << "\ttesting testArray.addAllDefinitions(invalid_id, last_id, newAddArray)\n";
    if (testArray.addAllDefinitions(TestAdditions::NewAdd_Invalid_enum_Value, TestAdditions::NewAddLast_Enum, newAddArray))
    {
        testPassed = didConstructionWork("testArray", testArray, 15);
    }
    else
    {
        std::cerr << "\ttesting testArray.addAllDefinitions(newAddArray) FAILED\n";
        testPassed = false;
#ifdef DEBUG
        testArray.debugDumpData();
        testArray.debugDumpUserList();
#endif
    }

    return testPassed;
}

bool FunctionalityTests::defaultConstructorAddInitializerList() noexcept
{
    bool testPassed = true;

    std::cout << "\ntesting usingInitList addAllDefinitions() Default Constructor\n";
    GenericDictionary<TestAdditions, std::string> usingInitList;
    std::cout << "testing usingInitList.addAllDefinitions(invalid_id, last_id, initialization list)\n";
    if (usingInitList.addAllDefinitions(TestAdditions::NewAdd_Invalid_enum_Value, TestAdditions::NewAddLast_Enum,
    {
		{TestAdditions::NewAddValue_1, "New funct 1"},
		{TestAdditions::NewAddValue_2, "New funct 2"},
		{TestAdditions::NewAddValue_3, "New funct 3"},
		{TestAdditions::NewAddValue_4, "New funct 4"},
		{TestAdditions::NewAddValue_5, "New funct 5"},
		{TestAdditions::NewAddValue_6, "New funct 6"},
		{TestAdditions::NewAddValue_7, "New funct 7"},
		{TestAdditions::NewAddValue_8, "New funct 8"},
		{TestAdditions::NewAddValue_9, "New funct 9"},
		{TestAdditions::NewAddValue_10, "New funct 10"},
		{TestAdditions::NewAddValue_11, "New funct 11"},
		{TestAdditions::NewAddValue_12, "New funct 12"},
		{TestAdditions::NewAddValue_13, "New funct 13"},
		{TestAdditions::NewAddValue_14, "New funct 14"},
		{TestAdditions::NewAddValue_15, "New funct 15"},
		{TestAdditions::NewAddValue_16, "New funct 16"}}
	))
    {
        testPassed = didConstructionWork("usingInitList", usingInitList, 10);
    }
    else
    {
        std::cerr << "\ttesting usingInitList.addAllDefinitions(initialization list) FAILED\n";
        testPassed = false;
#ifdef DEBUG
        usingInitList.debugDumpData();
        usingInitList.debugDumpUserList();
#endif
    }

    std::cout << "\n";

    return testPassed;
}

bool FunctionalityTests::limitsConstructorAddVector() noexcept
{
    bool testPassed = true;

    std::cout << "testing testMyNewAdditions Limits Only Constructor\n";
    GenericDictionary<TestAdditions, std::string> testMyNewAdditions(TestAdditions::NewAdd_Invalid_enum_Value, TestAdditions::NewAddLast_Enum);
    std::cout << "testing testMyNewAdditions.addAllDefinitions(newAddtestVec)\n";
    if (testMyNewAdditions.addAllDefinitions(newAddtestVec))
    {
        testPassed = didConstructionWork("testMyNewAdditions", testMyNewAdditions, 1);
    }
    else
    {
        std::cerr << "\ttesting testMyNewAdditions.addAllDefinitions(newAddtestVec) FAILED\n";
        testPassed = false;
#ifdef DEBUG
        testMyNewAdditions.debugDumpData();
        testMyNewAdditions.debugDumpUserList();
#endif
    }

    return testPassed;
}

bool FunctionalityTests::limitsConstructorAddArray() noexcept
{
    bool testPassed = true;

	std::array<GenricDictionaryDataPair<TestAdditions, std::string>,16> newAddArray;
    std::size_t i = 0;
	for (auto tdata: newAddtestVec)
	{
		newAddArray[i] = tdata;
        ++i;
	}

    std::cout << "\ntesting Constructor with limits\n";
    GenericDictionary<TestAdditions, std::string> testArray(TestAdditions::NewAdd_Invalid_enum_Value, TestAdditions::NewAddLast_Enum);
    std::cout << "\ttesting testArray.addAllDefinitions(newAddArray)\n";
    if (testArray.addAllDefinitions(newAddArray))
    {
        testPassed = didConstructionWork("testArray", testArray, 15);
    }
    else
    {
        std::cerr << "\ttesting testArray.addAllDefinitions(newAddArray) FAILED\n";
        testPassed = false;
#ifdef DEBUG
        testArray.debugDumpData();
        testArray.debugDumpUserList();
#endif
    }

    return testPassed;
}

bool FunctionalityTests::limitsConstructorAddInitializerList() noexcept
{
    bool testPassed = true;

    std::cout << "\ntesting usingInitList addAllDefinitions() Limits Only Constructor\n";
    GenericDictionary<TestAdditions, std::string> usingInitList(TestAdditions::NewAdd_Invalid_enum_Value, TestAdditions::NewAddLast_Enum);
    std::cout << "testing usingInitList.addAllDefinitions(initialization list)\n";
    if (usingInitList.addAllDefinitions({
		{TestAdditions::NewAddValue_1, "New funct 1"},
		{TestAdditions::NewAddValue_2, "New funct 2"},
		{TestAdditions::NewAddValue_3, "New funct 3"},
		{TestAdditions::NewAddValue_4, "New funct 4"},
		{TestAdditions::NewAddValue_5, "New funct 5"},
		{TestAdditions::NewAddValue_6, "New funct 6"},
		{TestAdditions::NewAddValue_7, "New funct 7"},
		{TestAdditions::NewAddValue_8, "New funct 8"},
		{TestAdditions::NewAddValue_9, "New funct 9"},
		{TestAdditions::NewAddValue_10, "New funct 10"},
		{TestAdditions::NewAddValue_11, "New funct 11"},
		{TestAdditions::NewAddValue_12, "New funct 12"},
		{TestAdditions::NewAddValue_13, "New funct 13"},
		{TestAdditions::NewAddValue_14, "New funct 14"},
		{TestAdditions::NewAddValue_15, "New funct 15"},
		{TestAdditions::NewAddValue_16, "New funct 16"}}
	))
    {
        testPassed = didConstructionWork("usingInitList", usingInitList, 10);
    }
    else
    {
        std::cerr << "\ttesting usingInitList.addAllDefinitions(initialization list) FAILED\n";
        testPassed = false;
#ifdef DEBUG
        usingInitList.debugDumpData();
        usingInitList.debugDumpUserList();
#endif
    }

    std::cout << "\n";

    return testPassed;
}

