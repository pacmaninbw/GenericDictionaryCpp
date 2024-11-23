#include <array>
#include "commonFunctTest.h"
#include <string>
#include <vector>

std::array<GenricDictionaryDataPair<TestFunctionalityEnumDict, std::string>, ArrayMax>
copyVecToArray(std::vector<GenricDictionaryDataPair<TestFunctionalityEnumDict, std::string>>& testVec)
{
    std::array<GenricDictionaryDataPair<TestFunctionalityEnumDict, std::string>, ArrayMax> testArray;
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

