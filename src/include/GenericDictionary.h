#ifndef GENERICDICTIONARY_H_
#define GENERICDICTIONARY_H_

#include <algorithm>
#include <concepts>
#include <exception>
#include <initializer_list>
#include <iostream>
#include <ranges>
#include <stdexcept>
#include <string>
#include <vector>

/*
 * This class provides a basic conversion of enums or integers to strings. The
 * class can be used as is, or as defIter1 base for defIter1 more complex object.
 * 
 * More complex objects than strings are also supported, however, overrides will
 * be necessary.
 * 
 * This class makes an attempt to find any missing definitions during construction.
 * 
 * Enums or integers should have an illegal value as 0. If not, then override the
 * getIds method.
 * 
 * The code has been modified based on the Code Reviews
 * https://codereview.stackexchange.com/questions/293782/generic-c-class-to-associate-enum-values-with-strings-for-translation
 * and
 * https://codereview.stackexchange.com/questions/293933/c20-performance-test-code-generator
 * Changes since the review
 * - A multiple constructor and destructor have been added.
 * - The constructor checks for missing definitions
 * - The class is no longer abstract
 * - dicID became dictID and dicName became dictName
 * - A performance test generator has been added:
 *   - The performance test generator will accept user input during runtime
 *   - The performance test generator will accept a command line
 *   - The code generated by the performance test generator includes a comment with the command line to regenerate the file.
 * - The struct used by the constructor now has a template GenricDictionaryDataPair.
 * - The unit test code has been added to this file to ease maintenance.
 * - The code for all the methods and constructors have been moved into template specializations.
 * - There is a constructor that does not need to be wrapped in a try catch block.
 * 
 */
template <typename dictID, typename dictName>
struct GenricDictionaryDataPair
{
    dictID id;
    dictName names;
};

template <typename dictID, typename dictName>
class GenericDictionary
{
public:
    using DictType = GenricDictionaryDataPair<dictID, dictName>;

// Both the MinValue and MaxValue should be invalid values
// Example
// GenericDictionary(enum::NO_VALUE, enum::LAST_VALUE)

// Safe constructor that will not throw exceptions, but the search table is
// not initialized.
    GenericDictionary(dictID MinValue, dictID MaxValue)
    : MinimumValue{MinValue},
      MaximumValue{MaxValue}
      {};
// The following constructors will throw exceptions if there are problems in the
// list of definitions.
    GenericDictionary(dictID MinValue, dictID MaxValue, std::initializer_list<DictType> definitions);
    GenericDictionary(dictID MinValue, dictID MaxValue, std::vector<DictType> definitions);
    virtual ~GenericDictionary() = default;

    virtual dictID getIds(dictName itemName);
    virtual dictName getNames(dictID id);
    bool addAllDefinitions(std::ranges::input_range auto&& definitions);
    bool addAllDefinitions(std::initializer_list<DictType> definitions);

protected:
    bool alreadyDefined(DictType candidate) noexcept;
    bool commonInternalListBuilder(std::string funcName);
    bool missingIDSizeTest(std::string funcName);
    bool hasDuplicateIds();
    bool hasDuplicateNames();
    bool hasID(dictID id) noexcept;
    bool hasName(dictName name) noexcept;
    void searchTableNotInitialized(std::string funcName, std::string searchValue);
    bool testForNoneLinearDefinitions(std::string funcName);
    [[nodiscard]] bool addDefinition(dictID id, dictName name) noexcept;

/*
 * Don't change the order of the following member variables since they
 * are set in contructors and the order is important.
 * 
 * The MinimumValue and MaximumValue can only be set in constructors.
 */
    dictID MinimumValue;
    dictID MaximumValue;
/*
 * This is currently implemented using std::vector to avoid multiple
 * allocations on the heap using std::map.
 */
    std::vector<DictType> searchTable;

/*
 * Member variables not initialized in constructor argument lists
 */
    bool inConstructor;
};

/*
 * Public interface specializations.
 */
template <typename dictID, typename dictName>
GenericDictionary<dictID, dictName>::GenericDictionary(dictID MinValue, dictID MaxValue, std::initializer_list<DictType> definitions)
: MinimumValue{MinValue},
MaximumValue{MaxValue},
searchTable{definitions}
{
    inConstructor = true;
    commonInternalListBuilder("Constructor");
    inConstructor = false;
}

template <typename dictID, typename dictName>
GenericDictionary<dictID, dictName>::GenericDictionary(dictID MinValue, dictID MaxValue, std::vector<DictType> definitions)
: MinimumValue{MinValue},
MaximumValue{MaxValue},
searchTable{definitions}
{
    inConstructor = true;
    commonInternalListBuilder("Constructor");
    inConstructor = false;
}

template <typename dictID, typename dictName>
dictID GenericDictionary<dictID, dictName>::getIds(dictName itemName)
{
    searchTableNotInitialized("getIds", "name value");
    auto definition = std::find_if(searchTable.begin(), searchTable.end(),
        [&itemName](DictType &dicItem) {return (dicItem.names == itemName);});

    if (definition != searchTable.end())
    {
        return definition->id;
    }

    return static_cast<dictID>(MinimumValue);
};

template <typename dictID, typename dictName>
dictName GenericDictionary<dictID, dictName>::getNames(dictID id)
{
    searchTableNotInitialized("getNames", "enum value");
    if (MinimumValue > id && id < MaximumValue)
    {
        auto definition = std::ranges::find(searchTable, id, &DictType::id);
        if (definition != searchTable.end())
        {
            return definition->names;
        }
    }

    dictName nameNotFound;
    return nameNotFound;
}

template <typename dictID, typename dictName>
bool GenericDictionary<dictID, dictName>::addAllDefinitions(std::ranges::input_range auto&& definitions)
{
    bool noErrors = true;

    for (auto const& newDef : definitions)
    {
        if (!addDefinition(newDef.id, newDef.names))
        {
            noErrors = false;
        }
    }

    if (noErrors)
    {
        inConstructor = false;
        noErrors = commonInternalListBuilder("addAllDefinitions()");
    }

    return noErrors;
}

template <typename dictID, typename dictName>
bool GenericDictionary<dictID, dictName>::addAllDefinitions(std::initializer_list<DictType> definitions)
{
    std::vector<DictType> tmpMap;

    for (auto const& newDef : definitions)
    {
        tmpMap.push_back(newDef);
    }

    return addAllDefinitions(tmpMap);
}
/*
 * Protected/Private methods
 */
template<typename dictID, typename dictName>
void GenericDictionary<dictID, dictName>::searchTableNotInitialized(std::string funcName, std::string searchValue)
{
    if (searchTable.size() == 0)
    {
        std::string emsg("In GenericDictionary::" + funcName + " (" + searchValue +"): ");
        emsg += "searchTable has not been initialized or sorted";
        std::logic_error notInitialized(emsg);
        throw notInitialized;
   }
}

template<typename dictID, typename dictName>
bool GenericDictionary<dictID, dictName>::commonInternalListBuilder(std::string funcName)
{
    if (missingIDSizeTest(funcName))
    {
        return false;
    }
    
    // To improve performance when searhing by id sort by id.
    // This sort is only necessary if the underlying structure remains
    // a std::vector. If it is std::map() the sort is not necessary.
    std::sort(searchTable.begin(), searchTable.end(),
        [](DictType defIter1, DictType defIter2) {return  defIter1.id < defIter2.id;});

    // Check for any missing or duplicate definitions now that the data is sorted.
    return testForNoneLinearDefinitions(funcName);
}

template <typename dictID, typename dictName>
bool GenericDictionary<dictID, dictName>::missingIDSizeTest(std::string funcName)
{
    std::size_t expectedSize = static_cast<std::size_t>(MaximumValue);
    expectedSize -= 1;
    if (searchTable.size() != expectedSize)
    {
        std::string emsg("In GenericDictionary::" + funcName + " missing definition values");
        if (inConstructor)
        {
            std::logic_error missingDefinitions(emsg);
            throw missingDefinitions;
        }
        else
        {
            std::cerr << emsg << "\n";
            return true;
        }
    }

    return false;
}

template <typename dictID, typename dictName>
bool GenericDictionary<dictID, dictName>::hasID(dictID id) noexcept
{
    std::size_t countID = std::ranges::count(searchTable, id, &DictType::id);
    return (countID > 0);
}

template <typename dictID, typename dictName>
bool GenericDictionary<dictID, dictName>::hasName(dictName name) noexcept
{
    std::size_t countID = std::ranges::count(searchTable, name, &DictType::names);
    return (countID > 0);
}

template <typename dictID, typename dictName>
bool GenericDictionary<dictID, dictName>::alreadyDefined(DictType candidate) noexcept
{
    return hasID(candidate.id) || hasName(candidate.names);
}

template <typename dictID, typename dictName>
bool GenericDictionary<dictID, dictName>::hasDuplicateIds()
{
    for (auto defintion: searchTable)
    {
        std::size_t countID = std::ranges::count(searchTable, defintion->id, &DictType::id);
        if (countID > 1)
        {
            return true;
        }
    }

    return false;
}

template <typename dictID, typename dictName>
bool GenericDictionary<dictID, dictName>::hasDuplicateNames()
{
    for (auto defintion: searchTable)
    {
        std::size_t countNames = std::ranges::count(searchTable, defintion->names, &DictType::names);
        if (countNames > 1)
        {
            return true;
        }
    }

    return false;
}

/*
 * Assumption, the input for this function has been sorted by ID.
 */
template <typename dictID, typename dictName>
bool GenericDictionary<dictID, dictName>::testForNoneLinearDefinitions(std::string funcName)
{
    for (auto defIter2 = searchTable.begin() + 1; defIter2 < searchTable.end(); defIter2++ )
    {
        auto defIter1 = defIter2 - 1;
        std::size_t id1 = static_cast<std::size_t>(defIter1->id);
        std::size_t id2 = static_cast<std::size_t>(defIter2->id);
        if (id1 != (id2 - 1))
        {
            std::string emsg("In GenericDictionary::" + funcName + ": ");
            emsg += (id1 == id2)? "duplicate definition values: " : 
                "missing definition value: ";
            emsg += std::to_string((id2 - 1));

            if (inConstructor)
            {
                std::logic_error orderError(emsg);
                throw orderError;
            }
            else
            {
                std::cerr << emsg << "\n";
                return false;
            }
        }
    }

    return true;
}

template <typename dictID, typename dictName>
[[nodiscard]] bool GenericDictionary<dictID, dictName>::addDefinition(dictID id, dictName name) noexcept
{
    DictType newDef(id, name);
    if (!alreadyDefined(newDef))
    {
        searchTable.push_back(newDef);
        return true;
    }

    return false;
}

/*
 * Unit testing and performance testing of the GenericDictinary class are
 * here to ease the maintenance of the testing and of the class. By default
 * if we are perfomance testing we are also unit testing.
 */

#ifdef GD_PERFORMANCE_TEST
#include "UtilityTimer.h"
#define GD_UNIT_TEST
#endif // GD_PERFORMANCE_TEST

#ifdef GD_UNIT_TEST
#include <iostream>

template <typename enumDictType>
static bool testIdToName(
	GenericDictionary<enumDictType, std::string>& underTest,
	enumDictType testID,
	std::string expectedOutput,
	std::string errorMessage
)
{
    std::string testGetName = underTest.getNames(testID);
    if (testGetName.compare(expectedOutput) != 0)
    {
        std::cerr
            << "\t" << errorMessage << " Input Value " <<
            static_cast<std::size_t>(testID)
            << " Expected Output " << expectedOutput << " " 
            << " Actual Ouput " << testGetName << "\n";
            ;
        return false;
    }

    return true;
}

template <typename enumDictType>
static bool testNameToID(
	GenericDictionary<enumDictType, std::string>& underTest,
	std::string testName,
	enumDictType expectedOutput,
	std::string errorMessage
	)
{
    enumDictType testGetID = underTest.getIds(testName);
    if (testGetID != expectedOutput)
    {
        std::cerr <<
            "\t " << errorMessage << " get ID from Name FAILED: "
            << "Input Name: " << testName
            << " Expected Output: " << static_cast<std::size_t>(expectedOutput)
            << " Actual Output: " << static_cast<std::size_t>(testGetID)
            << "\n";
        return false;
    }

    return true;
}

template <typename  enumDictType> using TestPairs = GenricDictionaryDataPair<enumDictType, std::string>;

template <typename enumDictType>
static bool testIDtoNameLoop(
    GenericDictionary <enumDictType, std::string>& underTest,
    std::vector<GenricDictionaryDataPair<enumDictType, std::string>>& TestData,
    std::string errorMessage
)
{
    bool allTestsPassed = true;

    for (auto test: TestData)
    {
        enumDictType testId = test.id;
        std::string expectedOutPut = test.names;
        std::string testGetName = underTest.getNames(testId);
        if (testGetName.compare(expectedOutPut) != 0)
        {
            std::cerr
                << "\t" << errorMessage << " Input Value " <<
                static_cast<std::size_t>(testId)
                << " Expected Output " << expectedOutPut << " " 
                << " Actual Ouput " << testGetName << "\n";
                ;
            allTestsPassed = false;
            break;
        }
    }

    return allTestsPassed;
}

template <typename enumDictType>
static bool testNametoIDLoop(
    GenericDictionary <enumDictType, std::string>& underTest,
    std::vector<GenricDictionaryDataPair<enumDictType, std::string>>& TestData,
    std::string errorMessage
)
{
    bool allTestsPassed = true;

    for (auto test: TestData)
    {
        std::string testName = test.names;
        enumDictType expectedOutput = test.id;
        enumDictType testGetID = underTest.getIds(testName);
        if (testGetID != expectedOutput)
        {
            std::cerr <<
                "\t " << errorMessage << " get ID from Name FAILED: "
                << "Input Name: " << testName
                << " Expected Output: " << static_cast<std::size_t>(expectedOutput)
                << " Actual Output: " << static_cast<std::size_t>(testGetID)
                << "\n";
            allTestsPassed = false;
            break;
        }
    }

    return allTestsPassed;
}

#ifdef GD_PERFORMANCE_TEST
/*
 * This function tests the performance of the searches for selected, the first
 * the last and 3 middle values.
 */
template <typename enumDictType>
static bool testMinMaxMiddleValues(
    GenericDictionary <enumDictType, std::string>& underTest,
    std::vector<TestPairs<enumDictType>>& testData,
    std::string testName
)
{
    bool allTestsPassed = true;
    UtilityTimer testTimer;

    std::vector<std::size_t> indexes;
    indexes.push_back(static_cast<std::size_t>(testData.size() - 1));
    if (testData.size() > 10)
    {
        indexes.push_back(static_cast<std::size_t>((testData.size() * 0.75) - 1));
        indexes.push_back(static_cast<std::size_t>((testData.size() * 0.5) - 1));
        indexes.push_back(static_cast<std::size_t>((testData.size() * 0.25) -1));
    }
    indexes.push_back(0);

    for (auto tIndex: indexes)
    {
        auto tDp = testData[tIndex];
        std::string testReport = "Performance Test find string from [" + std::to_string(tIndex) + "] ID " + testName + " ";
        testTimer.startTimer();
        allTestsPassed = testIdToName<enumDictType>(underTest, tDp.id, tDp.names, testName + " testIDToName()");
        testTimer.stopTimerAndReport(testReport);
        if (!allTestsPassed)
        {
            return false;
        }
    }

    for (auto tIndex: indexes)
    {
        auto tDp = testData[tIndex];
        std::string testReport = "Performance Test find ID from [" + std::to_string(tIndex) + "] Name " + testName + " ";
        testTimer.startTimer();
        allTestsPassed = testNameToID<enumDictType>(underTest, tDp.names, tDp.id, testName + " testNameToID()");
        testTimer.stopTimerAndReport(testReport);

        if (!allTestsPassed)
        {
            return false;
        }
    }

    return allTestsPassed;
}

template <typename enumDictType>
static bool performanceExecution(
    GenericDictionary <enumDictType, std::string>& underTest,
    std::vector<TestPairs<enumDictType>>& testData,
    std::string testName
)
{
    bool allTestsPassed = true;
    UtilityTimer testTimer;

    testMinMaxMiddleValues<enumDictType>(underTest, testData, testName);
    if (!allTestsPassed)
    {
        return false;
    }

    testTimer.startTimer();
    testIDtoNameLoop<enumDictType>(underTest, testData, testName + " testIDtoNameLoop()");
    testTimer.stopTimerAndReport("Performance Loop Test find string from ID " + testName + " ");
    if (!allTestsPassed)
    {
        return false;
    }

    testTimer.startTimer();
    testNametoIDLoop<enumDictType>(underTest, testData, testName + " testNametoIDLoop()");
    testTimer.stopTimerAndReport("Performance Loop Test find ID from Name " + testName + " ");
    if (!allTestsPassed)
    {
        return false;
    }

    return allTestsPassed;
}
#endif

#endif // GD_UNIT_TEST

#endif // GENERICDICTIONARY_H_

