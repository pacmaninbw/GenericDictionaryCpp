#ifndef COMMONFUNCTIONALITYTEST_H_
#define COMMONFUNCTIONALITYTEST_H_

#define GD_UNIT_TEST
#include <array>
#include "GenericDictionary.h"
#include "GD_Testing.h"
#include <iostream>
#include <string>
#include <vector>

enum class TestFunctionalityEnumDict
{
	FunctionalTest_0,
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
	FunctionalTest_16
};

struct TestPair
{
	TestFunctionalityEnumDict id;
	std::string names;
};
/*
 * Positive Path Test Data
 */
std::vector<TestPair> testPostivePathVec = 
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
};

#if 0
std::array<TestPair, 17> testPostivePathVec = 
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
};
#endif

/*
 * Negative Path Test Data
 */
std::vector<TestPair> testVecMultiIDMultiName = 
{
	{TestFunctionalityEnumDict::FunctionalTest_0, "Functional Test Str 0"},
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

std::vector<TestPair> testVecMultiName = 
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
	{TestFunctionalityEnumDict::FunctionalTest_11, "Functional Test Str 1"},
	{TestFunctionalityEnumDict::FunctionalTest_12, "Functional Test Str 2"},
	{TestFunctionalityEnumDict::FunctionalTest_13, "Functional Test Str 13"},
	{TestFunctionalityEnumDict::FunctionalTest_14, "Functional Test Str 14"},
	{TestFunctionalityEnumDict::FunctionalTest_15, "Functional Test Str 15"},
	{TestFunctionalityEnumDict::FunctionalTest_16, "Functional Test Str 6"}
};

std::vector<TestPair> testVecMultiID = 
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
	{TestFunctionalityEnumDict::FunctionalTest_1, "Functional Test Str 10"},
	{TestFunctionalityEnumDict::FunctionalTest_2, "Functional Test Str 11"},
	{TestFunctionalityEnumDict::FunctionalTest_12, "Functional Test Str 12"},
	{TestFunctionalityEnumDict::FunctionalTest_13, "Functional Test Str 13"},
	{TestFunctionalityEnumDict::FunctionalTest_14, "Functional Test Str 14"},
	{TestFunctionalityEnumDict::FunctionalTest_5, "Functional Test Str 15"},
	{TestFunctionalityEnumDict::FunctionalTest_16, "Functional Test Str 16"}
};

constexpr std::size_t ArrayMax = 17;
std::array<TestPair, ArrayMax>
copyVecToArray(std::vector<TestPair>& testVec)
{
    std::array<TestPair, ArrayMax> testArray;
    std::size_t i = 0;
	for (auto tdata: testVec)
	{
        if (i >= ArrayMax)
        {
            break;
        }
		testArray[i] = tdata;
        ++i;
	}

    return testArray;
}

#endif // COMMONFUNCTIONALITYTEST_H_