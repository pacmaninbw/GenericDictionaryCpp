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

enum class TestFunctionalityEnumDict
{
	NewAdd_Invalid_enum_Value,
	FunctionalTest_1,
	FunctionalTest_2,
	FunctionalTest_3,
	FunctionalTest_4,
	FunctionalTest_5,
	FunctionalTest_6,
	FunctionalTest_7,
	FunctionalTest_8,
	FunctionalTest_9,
	FunctionalTest_10,
	FunctionalTest_11,
	FunctionalTest_12,
	FunctionalTest_13,
	FunctionalTest_14,
	FunctionalTest_15,
	FunctionalTest_16,
	NewAddLast_Enum
};

/*
 * Positive Path Test Data
 */
static std::vector<GenricDictionaryDataPair<TestFunctionalityEnumDict, std::string>> newAddtestVec = 
{
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
};

/*
 * Negative Path Test Data
 */
static std::vector<GenricDictionaryDataPair<TestFunctionalityEnumDict, std::string>> testVecMultiNameMultiID = 
{
	{TestFunctionalityEnumDict::FunctionalTest_1, "Functional Test Str 1"},
	{TestFunctionalityEnumDict::FunctionalTest_2, "Functional Test Str 2"},
	{TestFunctionalityEnumDict::FunctionalTest_5, "Functional Test Str 2"},
	{TestFunctionalityEnumDict::FunctionalTest_4, "Functional Test Str 5"},
	{TestFunctionalityEnumDict::FunctionalTest_5, "Functional Test Str 5"},
	{TestFunctionalityEnumDict::FunctionalTest_6, "Functional Test Str 6"},
	{TestFunctionalityEnumDict::FunctionalTest_7, "Functional Test Str 7"},
	{TestFunctionalityEnumDict::FunctionalTest_8, "Functional Test Str 8"},
	{TestFunctionalityEnumDict::FunctionalTest_10, "Functional Test Str 9"},
	{TestFunctionalityEnumDict::FunctionalTest_10, "Functional Test Str 10"},
	{TestFunctionalityEnumDict::FunctionalTest_11, "Functional Test Str 1"},
	{TestFunctionalityEnumDict::FunctionalTest_12, "Functional Test Str 2"},
	{TestFunctionalityEnumDict::FunctionalTest_13, "Functional Test Str 13"},
	{TestFunctionalityEnumDict::FunctionalTest_14, "Functional Test Str 14"},
	{TestFunctionalityEnumDict::FunctionalTest_15, "Functional Test Str 15"},
	{TestFunctionalityEnumDict::FunctionalTest_16, "Functional Test Str 6"}
};

static std::vector<GenricDictionaryDataPair<TestFunctionalityEnumDict, std::string>> testVecMultiName = 
{
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
	{TestFunctionalityEnumDict::FunctionalTest_11, "Functional Test Str 1"},
	{TestFunctionalityEnumDict::FunctionalTest_12, "Functional Test Str 2"},
	{TestFunctionalityEnumDict::FunctionalTest_13, "Functional Test Str 13"},
	{TestFunctionalityEnumDict::FunctionalTest_14, "Functional Test Str 14"},
	{TestFunctionalityEnumDict::FunctionalTest_15, "Functional Test Str 15"},
	{TestFunctionalityEnumDict::FunctionalTest_16, "Functional Test Str 6"}
};

static std::vector<GenricDictionaryDataPair<TestFunctionalityEnumDict, std::string>> testVecMultiID = 
{
	{TestFunctionalityEnumDict::FunctionalTest_1, "Functional Test Str 1"},
	{TestFunctionalityEnumDict::FunctionalTest_2, "Functional Test Str 2"},
	{TestFunctionalityEnumDict::FunctionalTest_3, "Functional Test Str 3"},
	{TestFunctionalityEnumDict::FunctionalTest_4, "Functional Test Str 4"},
	{TestFunctionalityEnumDict::FunctionalTest_5, "Functional Test Str 5"},
	{TestFunctionalityEnumDict::FunctionalTest_6, "Functional Test Str 6"},
	{TestFunctionalityEnumDict::FunctionalTest_7, "Functional Test Str 7"},
	{TestFunctionalityEnumDict::FunctionalTest_8, "Functional Test Str 8"},
	{TestFunctionalityEnumDict::FunctionalTest_9, "Functional Test Str 9"},
	{TestFunctionalityEnumDict::FunctionalTest_1, "Functional Test Str 10"},
	{TestFunctionalityEnumDict::FunctionalTest_2, "Functional Test Str 11"},
	{TestFunctionalityEnumDict::FunctionalTest_12, "Functional Test Str 12"},
	{TestFunctionalityEnumDict::FunctionalTest_13, "Functional Test Str 13"},
	{TestFunctionalityEnumDict::FunctionalTest_14, "Functional Test Str 14"},
	{TestFunctionalityEnumDict::FunctionalTest_5, "Functional Test Str 15"},
	{TestFunctionalityEnumDict::FunctionalTest_16, "Functional Test Str 16"}
};

static bool testLookUpID(
    TestFunctionalityEnumDict searchID,
    std::string expectedName,
    GenericDictionary<TestFunctionalityEnumDict, std::string>& dictionary,
    std::string testName)
{
    std::size_t idIntVal = static_cast<std::size_t>(searchID);
    std::string strVal = expectedName;

    std::clog << "\ttesting " << testName << ".lookupName(" << idIntVal << "), expected output is " << strVal << "\n";
    auto checkName = dictionary.lookupName(searchID);
    if (checkName.has_value() && *checkName == strVal)
    {
        std::clog << "\t" << testName << ".getNames(" << idIntVal << ") PASSED\n";
    }
    else
    {
        if (checkName.has_value())
        {
            std::cerr << "\t" << testName << ".lookupName(" << idIntVal << ") FAILED\n";
            std::cerr << "\tExpected " << strVal << " Actual " << *checkName << "\n";
        }
        else
        {
            std::cerr << "\t" << testName << ".lookupName(" << idIntVal << ") FAILED\n";
            std::cerr << "\tID Not Found\n";
        }
        return false;
    }

    return true;
}

static bool testLookUpName(
    std::size_t idIntVal,
    std::string strVal,
    GenericDictionary<TestFunctionalityEnumDict, std::string>& dictionary,
    std::string testName)
{
    auto checkID = dictionary.lookupID(strVal);
    if (checkID.has_value() && static_cast<std::size_t>(*checkID) == idIntVal)
    {
        std::clog << "\t" << testName << ".lookupID(" << strVal << ") PASSED\n";
    }
    else
    {
        if (checkID.has_value())
        {
            std::cerr << "\t" << testName << ".lookupID(" << strVal << ") FAILED\n";
            std::cerr << "\tExpected " << std::to_string(idIntVal) << " Actual " << 
                std::to_string(static_cast<std::size_t>(*checkID)) << "\n";
        }
        else
        {
            std::cerr << "\t" << testName << ".lookupID(" << strVal << ") Name Not Found FAILED\n";
        }
        return false;
    }

    return true;
}

static bool didConstructionWork(
    std::string testName,
    GenericDictionary<TestFunctionalityEnumDict, std::string>& dictionary,
    std::size_t itemToTest
) noexcept
{
    bool testPassed = true;
    std::vector<GenricDictionaryDataPair<TestFunctionalityEnumDict, std::string>> userInput = dictionary.getUserInput();
    std::size_t idIntVal = static_cast<std::size_t>(userInput[itemToTest].id);
    std::string strVal = userInput[itemToTest].names;

    testPassed = testLookUpID(userInput[itemToTest].id, strVal, dictionary, testName);
// Test no matter what, but don't change a failure to a pass.
    if (testPassed)
    {
        testPassed = testLookUpName(idIntVal, strVal, dictionary, testName);
    }
    else
    {
        testLookUpName(idIntVal, strVal, dictionary, testName);
    }

    return testPassed;
}

static bool ConstructorInitializerListSuccess() noexcept
{
    bool testPassed = true;
    std::string addTitle("usingInitList"
        "(TestFunctionalityEnumDict::NewAdd_Invalid_enum_Value, TestFunctionalityEnumDict::NewAddLast_Enum, INITLIST)");

    try
    {
        std::clog << "\ntesting usingInitList Constructor using initialization list\n";
        GenericDictionary<TestFunctionalityEnumDict, std::string>
        usingInitList(TestFunctionalityEnumDict::NewAdd_Invalid_enum_Value, TestFunctionalityEnumDict::NewAddLast_Enum,{
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
            {TestFunctionalityEnumDict::FunctionalTest_16, "Functional Test Str 16"}}
        );
        testPassed = didConstructionWork("usingInitList", usingInitList, 10);
        if (testPassed)
        {
            std::clog << addTitle << " PASSED\n";
        }
        else
        {
            std::cerr << addTitle << " FAILED\n";
            testPassed = false;
#ifdef DEBUG
            usingInitList.debugDumpData();
            usingInitList.debugDumpUserList();
#endif
        }
    }
    catch (const std::logic_error &le)
    {
        std::cerr << addTitle  << " logic_error: " << le.what() << "\n\n";
        testPassed = false;
    }
    catch(const std::exception& e)
    {
        std::cerr << addTitle << " UNKNOWN EXCEPTION: " << e.what() << "\n\n";
        testPassed = false;
    }
    

    std::clog << "\n";

    return testPassed;
}

static bool expectSuccessArray(std::string dictionaryName, std::string tname, std::string rangeName,
    std::vector<GenricDictionaryDataPair<TestFunctionalityEnumDict, std::string>> testVec) noexcept
{
	std::array<GenricDictionaryDataPair<TestFunctionalityEnumDict, std::string>,16> testArray;
    std::size_t i = 0;
	for (auto tdata: testVec)
	{
		testArray[i] = tdata;
        ++i;
	}

    bool testPassed = true;
    std::string addTitle(dictionaryName +
        "(TestFunctionalityEnumDict::NewAdd_Invalid_enum_Value, TestFunctionalityEnumDict::NewAddLast_Enum, "
         + rangeName + ")");

    try
    {
        std::clog << "testing " << dictionaryName << " Constructor - " << tname << "\n";
        GenericDictionary<TestFunctionalityEnumDict, std::string> testDictionary(TestFunctionalityEnumDict::NewAdd_Invalid_enum_Value, TestFunctionalityEnumDict::NewAddLast_Enum, testArray);

        std::clog << "testing " << addTitle << "\n";
        testPassed = didConstructionWork(dictionaryName, testDictionary, 1);
        if (testPassed)
        {
            std::clog << "testing " << addTitle << " PASSED\n\n";
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
    }
    catch (const std::logic_error &le)
    {
        std::cerr << addTitle  << " logic_error: " << le.what() << "\n\n";
        testPassed = false;
    }
    catch(const std::exception& e)
    {
        std::cerr << addTitle << " UNKNOWN EXCEPTION: " << e.what() << "\n\n";
        testPassed = false;
    }
    
    return testPassed;
}

static bool expectSuccessVector(std::string dictionaryName, std::string tname, std::string rangeName,
    std::vector<GenricDictionaryDataPair<TestFunctionalityEnumDict, std::string>> testVec) noexcept
{
    bool testPassed = true;
    std::string addTitle(dictionaryName +
        "(TestFunctionalityEnumDict::NewAdd_Invalid_enum_Value, TestFunctionalityEnumDict::NewAddLast_Enum, "
         + rangeName + ")");

    try
    {
        std::clog << "testing " << dictionaryName << " Constructor - " << tname << "\n";
        GenericDictionary<TestFunctionalityEnumDict, std::string>
        testDictionary(TestFunctionalityEnumDict::NewAdd_Invalid_enum_Value, TestFunctionalityEnumDict::NewAddLast_Enum, testVec);

        std::clog << "testing " << addTitle << "\n";
        testPassed = didConstructionWork(dictionaryName, testDictionary, 1);
        if (testPassed)
        {
            std::clog << "testing " << addTitle << " PASSED\n\n";
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
    }
    catch (const std::logic_error &le)
    {
        std::cerr << addTitle  << " logic_error: " << le.what() << "\n\n";
        testPassed = false;
    }
    catch(const std::exception& e)
    {
        std::cerr << addTitle << " UNKNOWN EXCEPTION: " << e.what() << "\n\n";
        testPassed = false;
    }
    
    return testPassed;
}

static bool expectFailureRange(std::string dictionaryName, std::string tname, std::string rangeName, std::ranges::input_range auto &&testRange) noexcept
{
    bool testPassed = true;
    std::string addTitle(dictionaryName +
        "(TestFunctionalityEnumDict::NewAdd_Invalid_enum_Value, TestFunctionalityEnumDict::NewAddLast_Enum, "
         + rangeName + ")");

    std::clog << "testing " << dictionaryName << " Constructor - " << tname << "\n";
    try
    {
        std::clog << "testing " << addTitle << "\n"; // flush output
        GenericDictionary<TestFunctionalityEnumDict, std::string> testDictionary(TestFunctionalityEnumDict::NewAdd_Invalid_enum_Value, TestFunctionalityEnumDict::NewAddLast_Enum, testRange);
#ifdef DEBUG
        testDictionary.debugDumpData();
        testDictionary.debugDumpUserList();
#endif
        std::cerr << "testing " << addTitle << " FAILED\n";
        testPassed = false;
        didConstructionWork(dictionaryName, testDictionary, 1);
    }
    catch (const std::logic_error &le)
    {
        std::clog << "GenericDictionary constructor threw expected std::logic_error: \n\t" << le.what() << "\n";
        std::clog << "testing " << addTitle << " PASSED\n\n";
        std::clog.flush();
        return true;
    }
    catch(const std::exception& e)
    {
        std::cerr << addTitle << " UNKNOWN EXCEPTION: " << e.what() << "\n\n";
        std::clog.flush();
        return false;
    }
    
    std::clog.flush();

    return testPassed;
}

static bool expectFailArray(std::string dictionaryName, std::string tname, std::string rangeName,
    std::vector<GenricDictionaryDataPair<TestFunctionalityEnumDict, std::string>> testVec) noexcept
{
	std::array<GenricDictionaryDataPair<TestFunctionalityEnumDict, std::string>,16> testArray;
    std::size_t i = 0;
	for (auto tdata: testVec)
	{
		testArray[i] = tdata;
        ++i;
	}

    bool testPassed = true;
    std::string addTitle(dictionaryName +
        "(TestFunctionalityEnumDict::NewAdd_Invalid_enum_Value, TestFunctionalityEnumDict::NewAddLast_Enum, "
         + rangeName + ")");

    std::clog << "testing " << dictionaryName << " Constructor - " << tname << "\n";
    try
    {
        std::clog << "testing " << addTitle << "\n"; // flush output
        GenericDictionary<TestFunctionalityEnumDict, std::string> testDictionary(
            TestFunctionalityEnumDict::NewAdd_Invalid_enum_Value, TestFunctionalityEnumDict::NewAddLast_Enum, testArray);
#ifdef DEBUG
        testDictionary.debugDumpData();
        testDictionary.debugDumpUserList();
#endif
        std::cerr << "testing " << addTitle << " FAILED\n";
        testPassed = false;
        didConstructionWork(dictionaryName, testDictionary, 1);
    }
    catch (const std::logic_error &le)
    {
        std::clog << "GenericDictionary constructor threw expected std::logic_error: \n\t" << le.what() << "\n";
        std::clog << "testing " << addTitle << " PASSED\n\n";
        std::clog.flush();
        return true;
    }
    catch(const std::exception& e)
    {
        std::cerr << addTitle << " UNKNOWN EXCEPTION: " << e.what() << "\n\n";
        std::clog.flush();
        return false;
    }
    
    std::clog.flush();

    return testPassed;
}

static bool expectFailVector(std::string dictionaryName, std::string tname, std::string rangeName,
    std::vector<GenricDictionaryDataPair<TestFunctionalityEnumDict, std::string>> testVec) noexcept
{
    bool testPassed = true;
    std::string addTitle(dictionaryName +
        "(TestFunctionalityEnumDict::NewAdd_Invalid_enum_Value, TestFunctionalityEnumDict::NewAddLast_Enum, "
         + rangeName + ")");

    std::clog << "testing " << dictionaryName << " Constructor - " << tname << "\n";
    try
    {
        std::clog << "testing " << addTitle << "\n"; // flush output
        GenericDictionary<TestFunctionalityEnumDict, std::string> testDictionary(
            TestFunctionalityEnumDict::NewAdd_Invalid_enum_Value, TestFunctionalityEnumDict::NewAddLast_Enum, testVec);
#ifdef DEBUG
        testDictionary.debugDumpData();
        testDictionary.debugDumpUserList();
#endif
        std::cerr << "testing " << addTitle << " FAILED\n";
        testPassed = false;
        didConstructionWork(dictionaryName, testDictionary, 1);
    }
    catch (const std::logic_error &le)
    {
        std::clog << "GenericDictionary constructor threw expected std::logic_error: \n\t" << le.what() << "\n";
        std::clog << "testing " << addTitle << " PASSED\n\n";
        std::clog.flush();
        return true;
    }
    catch(const std::exception& e)
    {
        std::cerr << addTitle << " UNKNOWN EXCEPTION: " << e.what() << "\n\n";
        std::clog.flush();
        return false;
    }
    
    std::clog.flush();

    return testPassed;
}


static bool ConstuctorArrMultiIDMultiName() noexcept
{
    return (expectFailArray("arrayMultiIDMultiNames", "Duplicate IDs Duplicate Names in Array", "testArrMultiNameMultiID", testVecMultiNameMultiID));
}

static bool ConstuctorVecMultiIDMultiName() noexcept
{
    return (expectFailVector("vectorMultiIDMultiNames", "Duplicate IDs Duplicate Names in Vector", "testArrMultiNameMultiID", testVecMultiNameMultiID));
}

static bool ConstructorArraySuccess() noexcept
{
    return expectSuccessArray("testArray", "Definitions by array", "newAddArray", newAddtestVec);
}

static bool ConstructorVectorSuccess() noexcept
{
    return expectSuccessVector("testVec", "Definitions by vector", "newAddtestVec", newAddtestVec);
}

typedef bool (*testFunc)();
static testFunc testFunctions[] =
{
    ConstructorInitializerListSuccess,
    ConstructorVectorSuccess,
    ConstructorArraySuccess,
// Negative Path Testing
    ConstuctorVecMultiIDMultiName,
    ConstuctorArrMultiIDMultiName,
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
        std::clog << "ALL Functional Tests PASSED\n";
    }
    else
    {
        std::clog << "Some or all Functional Tests FAILED\n"; 
    }
    std::clog << "FUNCTIONAL TEST EXECUTION COMPLETE\n\n";

    std::clog.flush();

    return allTestsPassed;
}

