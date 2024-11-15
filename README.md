# GenericDictionaryCpp
Generic C++ dictionary class to associate enums or symbolic names with strings.

## C++ Generic Dictionary With Unit Test and Performance Tests  

The src/include/GenericDictionary.h contains a generic class for associating enums or integers (numeric constants) 
with strings or more complex mechanisms. It can be a base class for other converters.

The src/tests/TestDictionary.cpp file contains the unit testing for the GenericDictionary 
class as well as classes that inherit from the GenericDictionary base class.

The ColumnDictionary files and the TableDictionary files are from 
another project that uses the GenericDictionary class defined in
GenericDictionary.h.

# Usage


Strings can be assigned to EnumValue_1 through EnumValue_N.

## Expected Input Type for a List  
The follow struct is used to map enums to a name  

```
struct GenricDictionaryDataPair<ENUMNAME, NameType>  // NameType will generally be std::string.   
```

## Constructors:  

```
GenericDictionary<ENUMNAME, NameType>(std::vector<GenricDictionaryDataPair<ENUMNAME, NameType>>)  
   // Initializes the internal data structures for searches  
   // Checks the input data for any duplicates or missing definitions
   // will throw exceptions in the case of duplicates or missing definitions  
GenericDictionary<ENUMNAME, NameType>({<GenricDictionaryDataPair<ENUMNAME, NameType>>, ...})  
   // Initializes the internal data structures for searches  
   // Checks the input data for any duplicates or missing definitions
   // will throw exceptions in the case of duplicates or missing definitions  
```
     
## Public Methods  

```
// Translate enums to names and names to enums
    ENUMNAME getIds(NameType itemName);
    NameType getNames(ENUMNAME id);
    
 
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

