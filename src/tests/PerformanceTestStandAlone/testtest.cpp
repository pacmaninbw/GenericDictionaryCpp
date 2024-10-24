#include <array>
#include "../PerformanceTestGenerator/performanceTest.h"

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

int main(void)
{
    if (!performancetests())
    {
        return EXIT_FAILURE;
    }

    std::cout << "testing testMyNewAdditions Constructor\n";
    GenericDictionary<TestAdditions, std::string> testMyNewAdditions(TestAdditions::NewAdd_Invalid_enum_Value, TestAdditions::NewAddLast_Enum);
    std::cout << "testing testMyNewAdditions.addAllDefinitions(newAddtestVec)\n";
    testMyNewAdditions.addAllDefinitions(newAddtestVec);
    std::cout << "testing testMyNewAdditions.getNames(TestAdditions::NewAddValue_16)" << testMyNewAdditions.getNames(TestAdditions::NewAddValue_16) << "\n";

    std::cout << "\n\ntesting usingInitList Constructor\n";
    GenericDictionary<TestAdditions, std::string> usingInitList(TestAdditions::NewAdd_Invalid_enum_Value, TestAdditions::NewAddLast_Enum);
    std::cout << "testing usingInitList.addAllDefinitions(newAddtestVec)\n";
    usingInitList.addAllDefinitions({
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
	);
    std::cout << "testing usingInitList.getNames(TestAdditions::NewAddValue_16)" << usingInitList.getNames(TestAdditions::NewAddValue_16) << "\n";

	std::array<GenricDictionaryDataPair<TestAdditions, std::string>,16> oops;
	for (std::size_t i = 0; i < 16; ++i)
	{
		oops[i] = newAddtestVec[i];
	}

    std::cout << "End testing\n";
    std::cout << "testing testArray Constructor\n";
    GenericDictionary<TestAdditions, std::string> testArray(TestAdditions::NewAdd_Invalid_enum_Value, TestAdditions::NewAddLast_Enum);
    std::cout << "testing testArray.addAllDefinitions(oops)\n";
    testArray.addAllDefinitions(oops);
    std::cout << "testing testArray.getNames(TestAdditions::NewAddValue_16)" << testArray.getNames(TestAdditions::NewAddValue_16) << "\n";


    return EXIT_SUCCESS;
}

