# GenericDictionaryCpp
Generic C++ dictionary class to associate enums with strings.

## C++ Generic Dictionary With Unit Test and Performance Tests  

The src/include/GenericDictionary.h contains a generic class for associating enums or integers (numeric constants) 
with strings or more complex mechanisms. It can be a base class for other converters.

The src/tests/TestDictionary.cpp file contains the unit testing for the GenericDictionary 
class as well as classes that inherit from the GenericDictionary base class.

The ColumnDictionary files and the TableDictionary files are from 
another project that uses the GenericDictionary class defined in
GenericDictionary.h.

# Usage

The GenericDictionary expects enums of a particular format:

```
enum class ENUMNAME
{
	Invalid_enum_Value,
	EnumValue_1,
    ...
	EnumValue_N,
	Last_Enum
};
```

Strings can be assigned to EnumValue_1 through EnumValue_N.

## Expected Input Type for a List  
The follow struct is used to map enums to a name  

```
struct GenricDictionaryDataPair<ENUMNAME, NameType>  // NameType will generally be std::string.   
```

## Constructors:  

```
GenericDictionary<ENUMNAME, NameType>() // The default constructor, creates an empty instance of the class.  
GenericDictionary<ENUMNAME, NameType>(ENUM::Invalid_enum_Value, ENUM::Last_Enum) // Sets the upper and lower limits of the range of enums used  
GenericDictionary<ENUMNAME, NameType>(ENUM::Invalid_enum_Value, ENUM::Last_Enum, std::vector<GenricDictionaryDataPair<ENUMNAME, NameType>>)  
   // Sets the upper and lower limits of the range of enums used  
   // Initializes the internal data structures for searches  
   // Checks the input data for any duplicates or missing definitions
   // will throw exceptions in the case of duplicates or missing definitions  
GenericDictionary<ENUMNAME, NameType>(ENUM::Invalid_enum_Value, ENUM::Last_Enum, Initializer List  {<GenricDictionaryDataPair<ENUMNAME, NameType>>, ...})  
   // Sets the upper and lower limits of the range of enums used  
   // Initializes the internal data structures for searches  
   // Checks the input data for any duplicates or missing definitions
   // will throw exceptions in the case of duplicates or missing definitions  
```
     
## Public Methods  

```
// Translate enums to names and names to enums
    virtual ENUMNAME getIds(NameType itemName);
    virtual NameType getNames(ENUMNAME id);
    
// Complete the data for the instance of the class
    bool addAllDefinitions(std::ranges::input_range auto&& definitions);  
    bool addAllDefinitions(std::initializer_list<DictType> definitions);  
// The following method set the upper and lower limits of the range of enums used  
// Initializes the internal data structures for searches  
// Checks the input data for any duplicates or missing definitions
// may throw exceptions in the case of duplicates or missing definitions  
    bool addAllDefinitions(dictID MinValue, dictID MaxValue, std::ranges::input_range auto&& definitions);  
    bool addAllDefinitions(dictID MinValue, dictID MaxValue, std::initializer_list<DictType> definitions);  
```

The DictionaryBase class should be portable to all systems and all C++20 compilers.

# Development Environments  
- C++ 20
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

The [performance test generator code was also reviewed](https://codereview.stackexchange.com/questions/293933/c20-performance-test-code-generator) on the Stack Exchange Code Review site. The code reviewed by that review can be found in found in this [branch on GitHub](https://github.com/pacmaninbw/DictionaryBaseCPP/tree/PerformanceTestGeneratorCodeReview).

The master branch contains corrections from both code review.

A new repository was created, the original version of the GenericDictionary was an abstract class, the current version can be used as is or can be used as a base class. The original version is in the [DictionaryBaseCPP repository](https://github.com/pacmaninbw/DictionaryBaseCPP).    

Multiple constructors have been added, including a default constructor.  
# Todo Items  
 - Add performance tests that test different containers in the GenericDictionary (std::vector versus std::map)
 - Integrate the generated performance tests into the unit testing.
 - Make sure all paths through the code are tested.

