#include "GenericDictionary.h"
#include <string>
#include <vector>

enum class ExampleEnum
{
	ExampleDemo_0,
	ExampleDemo_1,
	ExampleDemo_2
};

using ExampleData = GenericDictionary<ExampleEnum, std::string>::DictType;

std::vector<ExampleData> ExampleInput = 
{
	{ExampleEnum::ExampleDemo_0, "Functional Test Str 0"},
	{ExampleEnum::ExampleDemo_1, "Functional Test Str 1"},
	{ExampleEnum::ExampleDemo_2, "Functional Test Str 2"}
};

int main()
{
    GenericDictionary<ExampleEnum, std::string> dictionary(ExampleInput);


	auto checkID = dictionary.lookupID("Functional Test Str 0");
	ExampleEnum exID = checkID.has_value()? *checkID : static_cast<ExampleEnum>(-1);

    auto checkName = dictionary.lookupName(exID);
    std::string exstr = checkName.has_value()? *checkName : "Not Found";

    
    return EXIT_SUCCESS;
}