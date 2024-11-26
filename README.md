# GenericDictionaryCpp
Generic C++ dictionary class to associate enums or symbolic names with strings.

## C++ Generic Dictionary With Unit Test and Performance Tests  

The GenericDictionary.h contains a generic class for associating enums or integers (numeric constants) 
with strings or more complex mechanisms. It can be a base class for other converters.

## Learning Project  
This project is a learning project, while the major goal is to provide a generic enum to string conversion class, the secondary goal is to keep my C++ skills up to date. What I am learning is:  
 - Improving my CMake skills  
 - Learn CTest  
 - Learn C++23 features  
   - std::expected  
 - Improve my knowledge of C++20 ranges  

# Example Usage  

The dictionary can be initialized with a range or an initialization list.

```
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

```

The DictionaryBase class should be portable to all systems and all C++23 compilers.

# Development Environments  
- C++ 23
- CMake

## Linux Development  
- gcc 12
- Ubuntu 22.04
- Visual Studio Code (vscode)

## Windows Development  
- Windows 10
- Visual Studion 2022

## Building The Tests  
cmake -B build  
cmake --build build -j

# Status  
This code was reviewed on the [Stack Exchange Code Review site](https://codereview.stackexchange.com/questions/293782/generic-c-class-to-associate-enum-values-with-strings-for-translation). The code reviewed in that review can be found in the `PreCodeReview` branch. Development is continuing in the `master` branch.  

The GenericDictionary class was reviewed a second time on the [Stack Exchange Code Review site](https://codereview.stackexchange.com/questions/294285/second-try-at-c-20-generic-dictionary-for-enums-and-strings). The branch that contains the code that was review is [PreThirdCodeReview](https://github.com/pacmaninbw/GenericDictionaryCpp/tree/PreThirdCodeReview). Any changes based on that code review will be included in the `master` branch`.

The [performance test generator code was also reviewed](https://codereview.stackexchange.com/questions/293933/c20-performance-test-code-generator) on the Stack Exchange Code Review site. The code reviewed by that review can be found in found in this [branch on GitHub](https://github.com/pacmaninbw/DictionaryBaseCPP/tree/PerformanceTestGeneratorCodeReview).

The master branch contains corrections from both code review.

A new repository was created, the original version of the GenericDictionary was an abstract class, the current version can be used as is or can be used as a base class. The original version is in the [DictionaryBaseCPP repository](https://github.com/pacmaninbw/DictionaryBaseCPP).    

Multiple constructors have been added, including a default constructor.  
# Todo Items  
 - Automate testing.
   - Generate test output to a file
   - Compare the test output to previous results.
 - Completely rework unit testing using CTest.
 - Get the `requires` for the range based constructor working properly.
 
