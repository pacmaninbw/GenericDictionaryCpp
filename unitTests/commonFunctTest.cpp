#include <array>
#include "commonFunctTest.h"
#include <string>
#include <vector>

GDTestDataArray copyVecToArray(std::vector<TestDataPair>& testVec)
{
    std::array<TestDataPair, ArrayMax> testArray;
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

