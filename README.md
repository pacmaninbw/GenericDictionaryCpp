# GenericDictionaryCpp
Generic C++23 dictionary class to associate enums or symbolic names with strings.

## C++ Generic Dictionary With Unit Test and Performance Tests  

The GenericDictionary.h contains a generic class for associating enums or integers (numeric constants) 
with strings or more complex mechanisms. It can be a base class for other converters.

## Learning Project  
This project is a learning project, while the major goal is to provide a generic enum to string conversion class, the secondary goal is to keep my C++ skills up to date. What I am learning is:  
 - Improving my CMake skills  
 - Learn CTest  
 - Learn C++23 features  
   - std::expected  
 - Improving my knowledge of C++20 ranges  

# Usage  

## Public Interface  

```
/******************************************************************************
 * For errors in lookup functions
 *****************************************************************************/
enum class DictionaryLookUpError
{
    Id_Not_Found,
    Name_Not_Found
};

/******************************************************************************
 * Data structures and class Declarations
 *****************************************************************************/
template <typename DictID, typename DictName>
class GenericDictionary
{
public:
    struct DictType
    {
        DictID id;
        DictName names
    };
    
    GenericDictionary(std::initializer_list<DictType> definitions);

    template<std::ranges::input_range R>
    requires std::convertible_to<std::ranges::range_reference_t<R>, DictType>
    GenericDictionary(R&& definitions);

    auto lookupID(DictName itemName) const -> std::expected<DictID, DictionaryLookUpError>;
    auto lookupName(DictID id) const -> std::expected<DictName, DictionaryLookUpError>;
}
```

## Example Usage  

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
- CTest

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

# Todo Items  
 - Regression testing.
 
