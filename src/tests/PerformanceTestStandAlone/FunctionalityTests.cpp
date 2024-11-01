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

/*
 * Positive Path Test Data
 */
static std::vector<GenricDictionaryDataPair<TestAdditions, std::string>> newAddtestVec = 
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

/*
 * Negative Path Test Data
 */
static std::vector<GenricDictionaryDataPair<TestAdditions, std::string>> testVecMultiNameMultiID = 
{
	{TestAdditions::NewAddValue_1, "New funct 1"},
	{TestAdditions::NewAddValue_2, "New funct 2"},
	{TestAdditions::NewAddValue_5, "New funct 2"},
	{TestAdditions::NewAddValue_4, "New funct 5"},
	{TestAdditions::NewAddValue_5, "New funct 5"},
	{TestAdditions::NewAddValue_6, "New funct 6"},
	{TestAdditions::NewAddValue_7, "New funct 7"},
	{TestAdditions::NewAddValue_8, "New funct 8"},
	{TestAdditions::NewAddValue_10, "New funct 9"},
	{TestAdditions::NewAddValue_10, "New funct 10"},
	{TestAdditions::NewAddValue_11, "New funct 1"},
	{TestAdditions::NewAddValue_12, "New funct 2"},
	{TestAdditions::NewAddValue_13, "New funct 13"},
	{TestAdditions::NewAddValue_14, "New funct 14"},
	{TestAdditions::NewAddValue_15, "New funct 15"},
	{TestAdditions::NewAddValue_16, "New funct 6"}
};

static std::vector<GenricDictionaryDataPair<TestAdditions, std::string>> testVecMultiName = 
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
	{TestAdditions::NewAddValue_11, "New funct 1"},
	{TestAdditions::NewAddValue_12, "New funct 2"},
	{TestAdditions::NewAddValue_13, "New funct 13"},
	{TestAdditions::NewAddValue_14, "New funct 14"},
	{TestAdditions::NewAddValue_15, "New funct 15"},
	{TestAdditions::NewAddValue_16, "New funct 6"}
};

static std::vector<GenricDictionaryDataPair<TestAdditions, std::string>> testVecMultiID = 
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
	{TestAdditions::NewAddValue_1, "New funct 10"},
	{TestAdditions::NewAddValue_2, "New funct 11"},
	{TestAdditions::NewAddValue_12, "New funct 12"},
	{TestAdditions::NewAddValue_13, "New funct 13"},
	{TestAdditions::NewAddValue_14, "New funct 14"},
	{TestAdditions::NewAddValue_5, "New funct 15"},
	{TestAdditions::NewAddValue_16, "New funct 16"}
};

static bool didConstructionWork(
    std::string testName,
    GenericDictionary<TestAdditions, std::string>& dictionary,
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

static bool defaultExpectFailureRange(std::string dictionaryName, std::string tname, std::string rangeName, std::ranges::input_range auto &&testRange) noexcept
{
    bool testPassed = true;
    std::string addTitle(dictionaryName +
        ".addAllDefinitions(TestAdditions::NewAdd_Invalid_enum_Value, TestAdditions::NewAddLast_Enum, "
         + rangeName + ")");

    std::cout << "testing " << dictionaryName << " Default Constructor - " << tname << "\n";
    GenericDictionary<TestAdditions, std::string> testDictionary;
    std::cout << "testing " << addTitle << "\n";

// Negative Path - error message expected
    if (testDictionary.addAllDefinitions(TestAdditions::NewAdd_Invalid_enum_Value, TestAdditions::NewAddLast_Enum, testRange))
    {
        std::cerr << "testing " << addTitle << " FAILED\n";
        testPassed = false;
#ifdef DEBUG
        testDictionary.debugDumpData();
        testDictionary.debugDumpUserList();
#endif
        didConstructionWork(dictionaryName, testDictionary, 1);
    }
    else
    {
        std::cout << "testing " << addTitle << " PASSED\n\n";
        testPassed = true;
    }

    std::cout.flush();

    return testPassed;
}

static bool defaultExpectSuccessRange(std::string dictionaryName, std::string tname, std::string rangeName, std::ranges::input_range auto &&testRange) noexcept
{
    bool testPassed = true;
    std::string addTitle(dictionaryName +
        ".addAllDefinitions(TestAdditions::NewAdd_Invalid_enum_Value, TestAdditions::NewAddLast_Enum, "
         + rangeName + ")");

    std::cout << "testing " << dictionaryName << " Default Constructor - " << tname << "\n";
    GenericDictionary<TestAdditions, std::string> testDictionary;

    std::cout << "testing " << addTitle << "\n";
    if (testDictionary.addAllDefinitions(TestAdditions::NewAdd_Invalid_enum_Value, TestAdditions::NewAddLast_Enum, testRange))
    {
        testPassed = didConstructionWork(dictionaryName, testDictionary, 1);
        if (testPassed)
        {
            std::cout << "testing " << addTitle << " PASSED\n\n";
        }
    }
    else
    {
        std::cerr << "testing " << addTitle << " FAILED\n";
        testPassed = false;
#ifdef DEBUG
        testDictionary.debugDumpData();
        testDictionary.debugDumpUserList();
#endif
    }

    return testPassed;
}

static bool limitsExpectFailureRange(std::string dictionaryName, std::string tname, std::string rangeName, std::ranges::input_range auto &&testRange) noexcept
{
    bool testPassed = true;
    std::string addTitle(dictionaryName + ".addAllDefinitions(" + rangeName + ")");

    std::cout << "testing " << dictionaryName << " Limits Only Constructor - " << tname << "\n";
    GenericDictionary<TestAdditions, std::string> testDictionary(TestAdditions::NewAdd_Invalid_enum_Value, TestAdditions::NewAddLast_Enum);
    std::cout << "testing " << addTitle << "\n";

// Negative Path - error message expected
    if (testDictionary.addAllDefinitions(testRange))
    {
        std::cerr << "testing " << addTitle << " FAILED\n";
        testPassed = false;
#ifdef DEBUG
        testDictionary.debugDumpData();
        testDictionary.debugDumpUserList();
#endif
        didConstructionWork(dictionaryName, testDictionary, 1);
    }
    else
    {
        std::cout << "testing " << addTitle << " PASSED\n\n";
        testPassed = true;
    }

    std::cout.flush();

    return testPassed;
}

static bool limitsExpectSuccessRange(std::string dictionaryName, std::string tname, std::string rangeName, std::ranges::input_range auto &&testRange) noexcept
{
    bool testPassed = true;
    std::string addTitle(dictionaryName + ".addAllDefinitions(" + rangeName + ")");

    std::cout << "testing " << dictionaryName << " Limits Only Constructor - " << tname << "\n";
    GenericDictionary<TestAdditions, std::string> testDictionary(TestAdditions::NewAdd_Invalid_enum_Value, TestAdditions::NewAddLast_Enum);
    std::cout << "testing " << addTitle << "\n";
    if (testDictionary.addAllDefinitions(testRange))
    {
        testPassed = didConstructionWork(dictionaryName, testDictionary, 1);
        if (testPassed)
        {
            std::cout << "testing " << addTitle << " PASSED\n\n";
        }
    }
    else
    {
        std::cerr << "testing " << addTitle << " FAILED\n";
        testPassed = false;
#ifdef DEBUG
        testDictionary.debugDumpData();
        testDictionary.debugDumpUserList();
#endif
    }

    return testPassed;
}

static bool defaultExpectSuccessArray(
    std::string dictionaryName,
    std::string tname,
    std::string rangeName,
    std::vector<GenricDictionaryDataPair<TestAdditions, std::string>> testVec
) noexcept
{
	std::array<GenricDictionaryDataPair<TestAdditions, std::string>,16> testArray;
    std::size_t i = 0;
	for (auto tdata: testVec)
	{
		testArray[i] = tdata;
        ++i;
	}

    return defaultExpectSuccessRange(dictionaryName, tname, rangeName, testArray);
}

static bool defaultExpectFailArray(
    std::string dictionaryName,
    std::string tname,
    std::string rangeName,
    std::vector<GenricDictionaryDataPair<TestAdditions, std::string>> testVec
) noexcept
{
	std::array<GenricDictionaryDataPair<TestAdditions, std::string>,16> testArray;
    std::size_t i = 0;
	for (auto tdata: testVec)
	{
		testArray[i] = tdata;
        ++i;
	}

    return defaultExpectFailureRange(dictionaryName, tname, rangeName, testArray);
}

static bool limitsExpectSuccessArray(
    std::string dictionaryName,
    std::string tname,
    std::string rangeName,
    std::vector<GenricDictionaryDataPair<TestAdditions, std::string>> testVec
) noexcept
{
	std::array<GenricDictionaryDataPair<TestAdditions, std::string>,16> testArray;
    std::size_t i = 0;
	for (auto tdata: testVec)
	{
		testArray[i] = tdata;
        ++i;
	}

    return limitsExpectSuccessRange(dictionaryName, tname, rangeName, testArray);
}

static bool limitsExpectFailArray(
    std::string dictionaryName,
    std::string tname,
    std::string rangeName,
    std::vector<GenricDictionaryDataPair<TestAdditions, std::string>> testVec
) noexcept
{
	std::array<GenricDictionaryDataPair<TestAdditions, std::string>,16> testArray;
    std::size_t i = 0;
	for (auto tdata: testVec)
	{
		testArray[i] = tdata;
        ++i;
	}

    return limitsExpectFailureRange(dictionaryName, tname, rangeName, testArray);
}

static bool defaultConstructorSelfTests() noexcept
{
    bool testPassed = true;

    return testPassed;
}

static bool defaultConstructorAddVector() noexcept
{
    return defaultExpectSuccessRange("testMyNewAdditions", "Adding definitions by vector", "newAddtestVec", newAddtestVec);
}

static bool defaultConstructorAddArray() noexcept
{
    return defaultExpectSuccessArray("testArray", "Adding definitions by array", "newAddArray", newAddtestVec);
}

static bool defaultConstructorAddInitializerList() noexcept
{
    bool testPassed = true;

    std::cout << "testing usingInitList addAllDefinitions() Default Constructor\n";
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
        if (testPassed)
        {
            std::cout << "testing usingInitList.addAllDefinitions(invalid_id, last_id, initialization list) PASSED\n";
        }
    }
    else
    {
        std::cerr << "testing usingInitList.addAllDefinitions(initialization list) FAILED\n";
        testPassed = false;
#ifdef DEBUG
        usingInitList.debugDumpData();
        usingInitList.debugDumpUserList();
#endif
    }

    std::cout << "\n";

    return testPassed;
}

static bool limitsConstructorAddVector() noexcept
{
    return limitsExpectSuccessRange("testVector", "add definitions by vector", "newAddtestVec", newAddtestVec);
}

static bool limitsConstructorAddArray() noexcept
{
    return limitsExpectSuccessArray("testArray", "add definitions by array", "newAddArray", newAddtestVec);
}

static bool limitsConstructorAddInitializerList() noexcept
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
        if (testPassed)
        {
            std::cout << "testing usingInitList.addAllDefinitions(initialization list) PASSED\n";
        }
    }
    else
    {
        std::cerr << "testing usingInitList.addAllDefinitions(initialization list) FAILED\n";
        testPassed = false;
#ifdef DEBUG
        usingInitList.debugDumpData();
        usingInitList.debugDumpUserList();
#endif
    }

    std::cout << "\n";

    return testPassed;
}


static bool defaultConstAddVecMultiID() noexcept
{
    return (defaultExpectFailureRange("AddultiID", "Duplicate IDs", "testVecMultiID", testVecMultiID));
}

static bool defaultConstAddVecMultiName() noexcept
{
    return (defaultExpectFailureRange("AddultiName", "Duplicate Names", "testVecMultiName", testVecMultiName));
}

static bool defaultConstAddVecMultiIDMultiName() noexcept
{
    return (defaultExpectFailureRange("AddultiNameID", "Duplicate Names Duplicate IDs", "testVecMultiNameMultiID", testVecMultiNameMultiID));
}

static bool defaultConstAddArrMultiID() noexcept
{
    return (defaultExpectFailArray("AddArrayMultiID", "Duplicate IDs", "testArrayMultiID", testVecMultiID));
}

static bool defaultConstAddArrMultiName() noexcept
{
    return (defaultExpectFailArray("AddArrayMultiName", "Duplicate Names in Array", "testArrMultiName", testVecMultiName));
}

static bool defaultConstAddArrMultiIDMultiName() noexcept
{
    return (defaultExpectFailArray("AddArrayMultiIdMultiName", "Duplicate Names Duplicate IDs in Array", "testArrMultiNameMultiID", testVecMultiNameMultiID));
}


static bool limitsConstAddVecMultiID() noexcept
{
    return (limitsExpectFailureRange("AddVecMultiID", "Duplicate IDs in Array", "testVecMultiID", testVecMultiID));
}

static bool limitsConstAddVecMultiName() noexcept
{
    return (limitsExpectFailureRange("AddVectorMultiNames", "Duplicate Names in Vector", "testVecMultiName", testVecMultiName));
}

static bool limitsConstAddVecMultiIDMultiName() noexcept
{
    return (limitsExpectFailureRange("AddVectorMultiIDMultiNames", "Duplicate IDs Duplicate Names in Vector", "testVecMultiNameMultiID", testVecMultiNameMultiID));
}

static bool limitsConstAddArrMultiID() noexcept
{
    return (limitsExpectFailArray("AddArrayMultiID", "Duplicate IDs in Array", "testArrayMultiID", testVecMultiID));
}

static bool limitsConstAddArrMultiName() noexcept
{
    return (limitsExpectFailArray("AddArrayMultiNames", "Duplicate Names in Array", "testArrMultiName", testVecMultiName));
}

static bool limitsConstAddArrMultiIDMultiName() noexcept
{
    return (limitsExpectFailArray("AddArrayMultiIDMultiNames", "Duplicate IDs Duplicate Names in Array", "testArrMultiNameMultiID", testVecMultiNameMultiID));
}

static bool defaultConstAddInitListMultiID() noexcept
{
    bool testPassed = true;

    std::cout << "\ntesting addAllDefinitions() Default Constructor Multiple IDs in Initialization List \n";
    GenericDictionary<TestAdditions, std::string> usingInitList;
    std::cout << "testing usingInitList.addAllDefinitions(TestAdditions::NewAdd_Invalid_enum_Value, TestAdditions::NewAddLast_Enum,initialization list)\n";
    if (usingInitList.addAllDefinitions(TestAdditions::NewAdd_Invalid_enum_Value, TestAdditions::NewAddLast_Enum, {
        {TestAdditions::NewAddValue_1, "New funct 1"},
        {TestAdditions::NewAddValue_2, "New funct 2"},
        {TestAdditions::NewAddValue_3, "New funct 3"},
        {TestAdditions::NewAddValue_4, "New funct 4"},
        {TestAdditions::NewAddValue_5, "New funct 5"},
        {TestAdditions::NewAddValue_6, "New funct 6"},
        {TestAdditions::NewAddValue_7, "New funct 7"},
        {TestAdditions::NewAddValue_8, "New funct 8"},
        {TestAdditions::NewAddValue_9, "New funct 9"},
        {TestAdditions::NewAddValue_1, "New funct 10"},
        {TestAdditions::NewAddValue_2, "New funct 11"},
        {TestAdditions::NewAddValue_12, "New funct 12"},
        {TestAdditions::NewAddValue_13, "New funct 13"},
        {TestAdditions::NewAddValue_14, "New funct 14"},
        {TestAdditions::NewAddValue_5, "New funct 15"},
        {TestAdditions::NewAddValue_16, "New funct 16"}
    }))
    {
        std::cerr << "testing using InitList addAllDefinitions() Default Constructor Multiple IDs in Initialization List FAILED\n";
        testPassed = false;
#ifdef DEBUG
        usingInitList.debugDumpData();
        usingInitList.debugDumpUserList();
#endif

        testPassed = didConstructionWork("usingInitList", usingInitList, 10);
    }
    else
    {
        std::cout << "testing  using InitList addAllDefinitions() Default Constructor Multiple IDs Initialization List PASSED\n";
        testPassed = true;
    }

    std::cout << std::endl; // flush output buffer

    return testPassed;
}

static bool defaultConstAddInitListMultiName() noexcept
{
    bool testPassed = true;

    std::cout << "\ntesting addAllDefinitions() Default Constructor Multiple Names in Initialization List \n";
    GenericDictionary<TestAdditions, std::string> usingInitList;
    std::cout << "testing usingInitList.addAllDefinitions(TestAdditions::NewAdd_Invalid_enum_Value, TestAdditions::NewAddLast_Enum,initialization list)\n";
    if (usingInitList.addAllDefinitions(TestAdditions::NewAdd_Invalid_enum_Value, TestAdditions::NewAddLast_Enum, {
        {TestAdditions::NewAddValue_1, "New funct 1"},
        {TestAdditions::NewAddValue_2, "New funct 2"},
        {TestAdditions::NewAddValue_5, "New funct 2"},
        {TestAdditions::NewAddValue_4, "New funct 5"},
        {TestAdditions::NewAddValue_5, "New funct 5"},
        {TestAdditions::NewAddValue_6, "New funct 6"},
        {TestAdditions::NewAddValue_7, "New funct 7"},
        {TestAdditions::NewAddValue_8, "New funct 8"},
        {TestAdditions::NewAddValue_10, "New funct 9"},
        {TestAdditions::NewAddValue_10, "New funct 10"},
        {TestAdditions::NewAddValue_11, "New funct 1"},
        {TestAdditions::NewAddValue_12, "New funct 2"},
        {TestAdditions::NewAddValue_13, "New funct 13"},
        {TestAdditions::NewAddValue_14, "New funct 14"},
        {TestAdditions::NewAddValue_15, "New funct 15"},
        {TestAdditions::NewAddValue_16, "New funct 6"}
    }))
    {
        std::cerr << "testing using InitList addAllDefinitions() Default Constructor Multiple Names in Initialization List FAILED\n";
        testPassed = false;
#ifdef DEBUG
        usingInitList.debugDumpData();
        usingInitList.debugDumpUserList();
#endif

        testPassed = didConstructionWork("usingInitList", usingInitList, 10);
    }
    else
    {
        std::cout << "testing  using InitList addAllDefinitions() Default Constructor Multiple Names Initialization List PASSED\n";
        testPassed = true;
    }

    std::cout << std::endl; // flush output buffer

    return testPassed;
}

static bool defaultConstAddInitListMultiIDMultiName() noexcept
{
    bool testPassed = true;

    std::cout << "\ntesting addAllDefinitions() Default Constructor Multiple IDs Multiple Names in Initialization List \n";
    GenericDictionary<TestAdditions, std::string> usingInitList;
    std::cout << "testing usingInitList.addAllDefinitions(TestAdditions::NewAdd_Invalid_enum_Value, TestAdditions::NewAddLast_Enum,initialization list)\n";
    if (usingInitList.addAllDefinitions(TestAdditions::NewAdd_Invalid_enum_Value, TestAdditions::NewAddLast_Enum, {
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
        {TestAdditions::NewAddValue_11, "New funct 1"},
        {TestAdditions::NewAddValue_12, "New funct 2"},
        {TestAdditions::NewAddValue_13, "New funct 13"},
        {TestAdditions::NewAddValue_14, "New funct 14"},
        {TestAdditions::NewAddValue_15, "New funct 15"},
        {TestAdditions::NewAddValue_16, "New funct 6"}
    }))
    {
        std::cerr << "testing using InitList addAllDefinitions() Default Constructor Muliple IDs Multiple Names in Initialization List FAILED\n";
        testPassed = false;
#ifdef DEBUG
        usingInitList.debugDumpData();
        usingInitList.debugDumpUserList();
#endif

        testPassed = didConstructionWork("usingInitList", usingInitList, 10);
    }
    else
    {
        std::cout << "testing  using InitList addAllDefinitions() Default Constructor Multiple IDs Multiple Names Initialization List PASSED\n";
        testPassed = true;
    }

    std::cout << std::endl; // flush output buffer

    return testPassed;
}

static bool limitsConstAddInitListMultiID() noexcept
{
    bool testPassed = true;

    std::cout << "\ntesting addAllDefinitions() Limits Only Constructor Multiple IDs in Initialization List \n";
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
        {TestAdditions::NewAddValue_1, "New funct 10"},
        {TestAdditions::NewAddValue_2, "New funct 11"},
        {TestAdditions::NewAddValue_12, "New funct 12"},
        {TestAdditions::NewAddValue_13, "New funct 13"},
        {TestAdditions::NewAddValue_14, "New funct 14"},
        {TestAdditions::NewAddValue_5, "New funct 15"},
        {TestAdditions::NewAddValue_16, "New funct 16"}
    }))
    {
        std::cerr << "testing using InitList addAllDefinitions() Limits Only  Constructor Multiple IDs in Initialization List FAILED\n";
        testPassed = false;
#ifdef DEBUG
        usingInitList.debugDumpData();
        usingInitList.debugDumpUserList();
#endif

        testPassed = didConstructionWork("usingInitList", usingInitList, 10);
    }
    else
    {
        std::cout << "testing  using InitList addAllDefinitions() Limits Only  Constructor Multiple IDs Initialization List PASSED\n";
        testPassed = true;
    }

    std::cout << std::endl; // flush output buffer

    return testPassed;
}

static bool limitsConstAddInitListMultiName() noexcept
{
    bool testPassed = true;

    std::cout << "\ntesting addAllDefinitions() Limits Only Constructor Multiple Names in Initialization List \n";
    GenericDictionary<TestAdditions, std::string> usingInitList(TestAdditions::NewAdd_Invalid_enum_Value, TestAdditions::NewAddLast_Enum);
    std::cout << "testing usingInitList.addAllDefinitions(initialization list)\n";
    if (usingInitList.addAllDefinitions({
        {TestAdditions::NewAddValue_1, "New funct 1"},
        {TestAdditions::NewAddValue_2, "New funct 2"},
        {TestAdditions::NewAddValue_5, "New funct 2"},
        {TestAdditions::NewAddValue_4, "New funct 5"},
        {TestAdditions::NewAddValue_5, "New funct 5"},
        {TestAdditions::NewAddValue_6, "New funct 6"},
        {TestAdditions::NewAddValue_7, "New funct 7"},
        {TestAdditions::NewAddValue_8, "New funct 8"},
        {TestAdditions::NewAddValue_10, "New funct 9"},
        {TestAdditions::NewAddValue_10, "New funct 10"},
        {TestAdditions::NewAddValue_11, "New funct 1"},
        {TestAdditions::NewAddValue_12, "New funct 2"},
        {TestAdditions::NewAddValue_13, "New funct 13"},
        {TestAdditions::NewAddValue_14, "New funct 14"},
        {TestAdditions::NewAddValue_15, "New funct 15"},
        {TestAdditions::NewAddValue_16, "New funct 6"}
    }))
    {
        std::cerr << "testing using InitList addAllDefinitions() Limits Only Constructor Multiple Names in Initialization List FAILED\n";
        testPassed = false;
#ifdef DEBUG
        usingInitList.debugDumpData();
        usingInitList.debugDumpUserList();
#endif

        testPassed = didConstructionWork("usingInitList", usingInitList, 10);
    }
    else
    {
        std::cout << "testing  using InitList addAllDefinitions() Limits Only Constructor Multiple Names Initialization List PASSED\n";
        testPassed = true;
    }

    std::cout << std::endl; // flush output buffer

    return testPassed;
}

static bool limitsConstAddInitListMultiIDMultiName() noexcept
{
    bool testPassed = true;

    std::cout << "\ntesting addAllDefinitions()  Limits Only Constructor Multiple IDs Multiple Names in Initialization List \n";
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
        {TestAdditions::NewAddValue_11, "New funct 1"},
        {TestAdditions::NewAddValue_12, "New funct 2"},
        {TestAdditions::NewAddValue_13, "New funct 13"},
        {TestAdditions::NewAddValue_14, "New funct 14"},
        {TestAdditions::NewAddValue_15, "New funct 15"},
        {TestAdditions::NewAddValue_16, "New funct 6"}
    }))
    {
        std::cerr << "testing using InitList addAllDefinitions() Limits Only Constructor Muliple IDs Multiple Names in Initialization List FAILED\n";
        testPassed = false;
#ifdef DEBUG
        usingInitList.debugDumpData();
        usingInitList.debugDumpUserList();
#endif

        testPassed = didConstructionWork("usingInitList", usingInitList, 10);
    }
    else
    {
        std::cout << "testing  using InitList addAllDefinitions()  Limits Only Constructor Multiple IDs Multiple Names Initialization List PASSED\n";
        testPassed = true;
    }

    std::cout << std::endl; // flush output buffer

    return testPassed;
}

typedef bool (*testFunc)();
static testFunc testFunctions[] =
{
    defaultConstructorSelfTests,
    defaultConstructorAddVector,
    defaultConstructorAddArray,
    defaultConstructorAddInitializerList,
    limitsConstructorAddVector,
    limitsConstructorAddArray,
    limitsConstructorAddInitializerList,
// Negative Path Testing
    defaultConstAddVecMultiID,
    defaultConstAddVecMultiName,
    defaultConstAddVecMultiIDMultiName,
    defaultConstAddArrMultiID,
    defaultConstAddArrMultiName,
    defaultConstAddArrMultiIDMultiName,
    defaultConstAddInitListMultiID,
    defaultConstAddInitListMultiName,
    defaultConstAddInitListMultiIDMultiName,
    limitsConstAddVecMultiID,
    limitsConstAddVecMultiName,
    limitsConstAddVecMultiIDMultiName,
    limitsConstAddArrMultiID,
    limitsConstAddArrMultiName,
    limitsConstAddArrMultiIDMultiName,
    limitsConstAddInitListMultiID,
    limitsConstAddInitListMultiName,
    limitsConstAddInitListMultiIDMultiName,
};

bool executeAllFuntionalTests() noexcept
{
    bool allTestsPassed = true;
    std::size_t allTestCount = sizeof(testFunctions) / sizeof(*testFunctions);

    for (std::size_t i = 0; i < allTestCount; ++i)
    {
        if (!testFunctions[i]())
        {
            allTestsPassed = false;
        }
    }

    if (allTestsPassed)
    {
        std::cout << "ALL Functional Tests PASSED\n";
    }
    else
    {
        std::cout << "Some or all Functional Tests FAILED\n"; 
    }
    std::cout << "FUNCTIONAL TEST EXECUTION COMPLETE\n\n";

    std::cout.flush();

    return allTestsPassed;
}

