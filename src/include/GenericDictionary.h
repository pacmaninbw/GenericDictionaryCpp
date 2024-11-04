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
#include <unordered_map>

#ifdef GD_PERFORMANCE_TEST
#define GD_UNIT_TEST
#endif // GD_PERFORMANCE_TEST

/*
 * This class provides a basic conversion of enums or integers to strings. The
 * class can be used as is, or as a base for more complex object.
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
 * Changes since the reviews
 * - Multiple constructors and a destructor have been added.
 * - The lists are checked for missing definitions and duplicate definitions
 * - The class is no longer abstract
 * - dicID became DictID and dicName became DictName
 * - The struct used by the constructor now has a template GenricDictionaryDataPair.
 * - The unit test code has been added to this file to ease maintenance.
 * - The code for all the methods and constructors have been moved into template specializations.
 * - There is a constructor that does not need to be wrapped in a try catch block.
 * 
 */

/******************************************************************************
 * Data structures and class Declarations
 *****************************************************************************/
template <typename DictID, typename DictName>
struct GenricDictionaryDataPair
{
    DictID id;
    DictName names;
};

template <typename DictID, typename DictName>
class GenericDictionary
{
public:
    using DictType = GenricDictionaryDataPair<DictID, DictName>;

// Both the MinValue and MaxValue should be invalid values
// Example
// GenericDictionary(enum::NO_VALUE, enum::LAST_VALUE)

    GenericDictionary()
    : MinimumValue{0},
      MaximumValue{0}
    {};

// Safe constructor that will not throw exceptions, but the search table is
// not initialized.
    GenericDictionary(DictID MinValue, DictID MaxValue)
    : MinimumValue{MinValue},
      MaximumValue{MaxValue}
      {};
// The following constructors will throw exceptions if there are problems in the
// list of definitions.
    GenericDictionary(DictID MinValue, DictID MaxValue, std::initializer_list<DictType> definitions);
    GenericDictionary(DictID MinValue, DictID MaxValue, std::vector<DictType> definitions);
    virtual ~GenericDictionary() = default;

    virtual DictID getIds(DictName itemName);
    virtual DictName getNames(DictID id);
    bool addAllDefinitions(std::ranges::input_range auto&& definitions);
    bool addAllDefinitions(DictID MinValue, DictID MaxValue, std::ranges::input_range auto&& definitions);
    bool addAllDefinitions(std::initializer_list<DictType> definitions);
    bool addAllDefinitions(DictID MinValue, DictID MaxValue, std::initializer_list<DictType> definitions);
    void enableExceptions(bool exceptionsEnabled) { throwException = exceptionsEnabled; };

#ifdef GD_UNIT_TEST
    std::vector<DictType> getUserInput() const noexcept { return userInputList; }
    bool selfUnitTest();
#endif

#ifdef DEBUG
    void debugDumpData() const noexcept;
    void debugDumpUserList() noexcept { debugDumpList(userInputList); };
    void debugDumpList(std::vector<DictType> candidate) noexcept;
#endif // DEBUG

private:
    [[nodiscard]] bool commonInternalListBuilder(std::string funcName) noexcept;
    [[nodiscard]] bool alreadyDefined(DictType candidate) noexcept { return hasID(candidate.id) || hasName(candidate.names); };
    [[nodiscard]] bool missingIDSizeTest(std::string funcName) noexcept;
    [[nodiscard]] bool reportDuplicateNameErrors(std::string funcName) noexcept;
    [[nodiscard]] bool hasID(DictID id) noexcept;
    [[nodiscard]] bool hasName(DictName name) noexcept;
    [[nodiscard]] bool limitsNotSet(std::string funcName, std::string searchValue) noexcept;
    [[nodiscard]] bool sanityCheck(std::string funcName, std::string searchValue) noexcept;
    [[nodiscard]] bool searchTableNotInitialized(std::string funcName, std::string searchValue) noexcept;
    [[nodiscard]] bool sortAndTestIds(std::string& emsg) noexcept;
    [[nodiscard]] bool testForIDNoneLinearDefinitions(std::string funcName) noexcept;
    [[nodiscard]] bool addDefinition(DictType newDef) noexcept;

/*
 * Don't change the order of the following 2 member variables since they
 * are set in contructors and the order is important.
 */
    DictID MinimumValue;
    DictID MaximumValue;

    std::unordered_map<DictID, DictName> idSearchTable;
    std::unordered_map<DictName, DictID> nameSearchTable;
    std::vector<DictType> userInputList;
    bool throwException = false;
};

/******************************************************************************
 * Public interface specializations.
 *****************************************************************************/
template <typename DictID, typename DictName>
GenericDictionary<DictID, DictName>::GenericDictionary(DictID MinValue, DictID MaxValue, std::initializer_list<DictType> definitions)
: MinimumValue{MinValue},
MaximumValue{MaxValue}
{
    for (auto const& newDef : definitions)
    {
        userInputList.push_back(newDef);
    }

    if (!commonInternalListBuilder("Constructor"))
    {
        std::logic_error constructorError("GenericDictionary::GenericDictionary(std::initializer_list): Search List Initialization");
        throw constructorError;
    }
}

template <typename DictID, typename DictName>
GenericDictionary<DictID, DictName>::GenericDictionary(DictID MinValue, DictID MaxValue, std::vector<DictType> definitions)
: MinimumValue{MinValue},
MaximumValue{MaxValue},
userInputList{definitions}
{
    if (!commonInternalListBuilder("Constructor"))
    {
        std::logic_error constructorError("GenericDictionary::GenericDictionary(std::vector): Search List Initialization Error");
        throw constructorError;
    }
}

template <typename DictID, typename DictName>
DictID GenericDictionary<DictID, DictName>::getIds(DictName itemName)
{
    if (sanityCheck("getIds", "name value"))
    {
        auto definition = nameSearchTable.find(itemName);
        if (definition != nameSearchTable.end())
        {
            return definition->second;
        }
    }
    else
    {
        if (throwException)
        {
            std::logic_error constructionError("GenericDictionary::addAllDefinitions(): Errors Occured.");
            throw constructionError;
        }

    }

    return static_cast<DictID>(MinimumValue);
};

template <typename DictID, typename DictName>
DictName GenericDictionary<DictID, DictName>::getNames(DictID id)
{
    if (sanityCheck("getNames", "enum value") && (MinimumValue < id && id < MaximumValue))
    {
        auto definition = idSearchTable.find(id);
        if (definition != idSearchTable.end())
        {
            return definition->second;
        }
    }
    else
    {
        if (throwException)
        {
            std::logic_error constructionError("GenericDictionary::addAllDefinitions(): Errors Occured.");
            throw constructionError;
        }

    }

    DictName nameNotFound;
    return nameNotFound;
}

/*
 * This method is used when a default constructor has been used to create the object.
 */
template <typename DictID, typename DictName>
bool GenericDictionary<DictID, DictName>::addAllDefinitions(DictID MinValue, DictID MaxValue, std::ranges::input_range auto&& definitions)
{
    MinimumValue = MinValue;
    MaximumValue = MaxValue;
    return addAllDefinitions(definitions);
}

/*
 * All the other addAllDefinitions() functions reference this function.
 */
template <typename DictID, typename DictName>
bool GenericDictionary<DictID, DictName>::addAllDefinitions(std::ranges::input_range auto&& definitions)
{
    bool noErrors = true;

    if (limitsNotSet("addAllDefinitions",""))
    {
        return false;
    }

// There is no guarantee that definitions are a vector so translate
    for (auto const& newDef : definitions)
    {
        userInputList.push_back(newDef);
    }

    if (noErrors)
    {
        noErrors = commonInternalListBuilder("addAllDefinitions()");
        if (throwException)
        {
            std::logic_error constructionError("GenericDictionary::addAllDefinitions(): Errors Occured.");
            throw constructionError;
        }
    }

    return noErrors;
}

template <typename DictID, typename DictName>
bool GenericDictionary<DictID, DictName>::addAllDefinitions(std::initializer_list<DictType> definitions)
{
    std::vector<DictType> tmpMap;

    for (auto const& newDef : definitions)
    {
        tmpMap.push_back(newDef);
    }

    return addAllDefinitions(tmpMap);
}

template <typename DictID, typename DictName>
bool GenericDictionary<DictID, DictName>::addAllDefinitions(DictID MinValue, DictID MaxValue, std::initializer_list<DictType> definitions)
{
    std::vector<DictType> tmpMap;

    for (auto const& newDef : definitions)
    {
        tmpMap.push_back(newDef);
    }

    return addAllDefinitions(MinValue, MaxValue, tmpMap);
}

#ifdef DEBUG
template <typename DictID, typename DictName>
void GenericDictionary<DictID, DictName>::debugDumpList(std::vector<DictType> toDump) noexcept
{
    for (auto searchItem: toDump)
    {
        std::cerr << "\t\tID int value " << static_cast<std::size_t>(searchItem.id) 
            << " Name value " << searchItem.names << "\n";
    }
}

template <typename DictID, typename DictName>
void GenericDictionary<DictID, DictName>::debugDumpData() const noexcept
{
    std::cerr << "\n\nGenericDictionary::Debug Dump Data\n";
    std::cerr << "\tMinimumValue: " << static_cast<std::size_t>(MinimumValue) << "\n";
    std::cerr << "\tMaximumValue: " << static_cast<std::size_t>(MaximumValue) << "\n";
    std::cerr << "ID Search Table:\n\t{\n";
    for (auto searchItem: idSearchTable)
    {
        std::cerr << "\t\tID int value " << static_cast<std::size_t>(searchItem.first) 
            << " Name value " << searchItem.second << "\n";
    }
    std::cerr << "\t}\n";
    std::cerr << "Name Search Table:\n\t{\n";
    for (auto searchItem: nameSearchTable)
    {
        std::cerr << "\t\tID int value " << static_cast<std::size_t>(searchItem.second) 
            << " Name value " << searchItem.first << "\n";
    }
    std::cerr << "\t}\n";
}
#endif // DEBUG

/******************************************************************************
 * Protected/Private methods
 *****************************************************************************/

template<typename DictID, typename DictName>
[[nodiscard]] bool GenericDictionary<DictID, DictName>::commonInternalListBuilder(std::string funcName) noexcept
{
    bool hasErrors = false;   
    if (missingIDSizeTest(funcName))
    {
        hasErrors = true;
    }

    if (!testForIDNoneLinearDefinitions(funcName))
    {
        hasErrors = true;
    }

    if (reportDuplicateNameErrors(funcName))
    {
        hasErrors = true;
    }

    if (hasErrors)
    {
        return false;
    }
    
    // Errors have been found, there is no need to add the definitions to the maps.
    for (auto newDef: userInputList)
    {
        if (!addDefinition(newDef))
        {
            return false;
        }
    }

    return true;
}

template<typename DictID, typename DictName>
[[nodiscard]] bool GenericDictionary<DictID, DictName>::sanityCheck(std::string funcName, std::string searchValue) noexcept
{
    if (limitsNotSet(funcName, searchValue))
    {
        return false;
    }
// if the limits aren't set there is no need to check searchtable initialization.
    if (searchTableNotInitialized(funcName, searchValue))
    {
        return false;
    }

    return true;
}

template<typename DictID, typename DictName>
[[nodiscard]] bool GenericDictionary<DictID, DictName>::limitsNotSet(std::string funcName, std::string searchValue) noexcept
{
    if (!(static_cast<std::size_t>(MaximumValue) > static_cast<std::size_t>(MinimumValue)))
    {
        std::string emsg("In GenericDictionary::" + funcName + " (" + searchValue +"): ");
        emsg += "The minimum and maximum enum values have not been set.";
        std::cerr << emsg << "\n";
        return true;
    }

    return false;
}

template<typename DictID, typename DictName>
[[nodiscard]] bool GenericDictionary<DictID, DictName>::searchTableNotInitialized(std::string funcName, std::string searchValue) noexcept
{
    if (idSearchTable.size() == 0 || nameSearchTable.size() == 0)
    {
        std::string emsg("In GenericDictionary::" + funcName + " (" + searchValue +"): ");
        emsg += "searchTable has not been initialized.";
        std::cerr << emsg << "\n";
        return true;
    }
    return false;
}

/*
 * Sorts the user input. After sorting the input performs various tests
 * on the validity of the input, finding duplicate IDs or missing IDs. The
 * input must be sorted before the the error checking can be performed.
 */
template <typename DictID, typename DictName>
[[nodiscard]] bool GenericDictionary<DictID, DictName>::sortAndTestIds(std::string& emsg) noexcept
{
    std::sort(userInputList.begin(), userInputList.end(),
        [](DictType defIter1, DictType defIter2) {return  defIter1.id < defIter2.id;});

    bool noErrors = true;

    for (auto defIter2 = userInputList.begin() + 1; defIter2 < userInputList.end(); defIter2++ )
    {
        auto defIter1 = defIter2 - 1;
        std::size_t id1 = static_cast<std::size_t>(defIter1->id);
        std::size_t id2 = static_cast<std::size_t>(defIter2->id);
        if (id1 != (id2 - 1))
        {
            if (id1 == id2)
            {
                emsg += "duplicate enum values: " + std::to_string(id1) + " Name: " + defIter1->names + " - " + std::to_string(id2) +
                    " Name: " + defIter2->names + "\n\t";
            }
            else
            {
                emsg += "missing enum value: " + std::to_string((id2 - 1)) + "\n\t";
            }
            noErrors = false;
        }
    }

    return noErrors;
}

template <typename DictID, typename DictName>
[[nodiscard]] bool GenericDictionary<DictID, DictName>::missingIDSizeTest(std::string funcName) noexcept
{
    std::size_t expectedSize = static_cast<std::size_t>(MaximumValue);
    expectedSize -= 1;
    if (userInputList.size() != expectedSize)
    {
        std::string emsg("In GenericDictionary::" + funcName + " missing definition values");
        emsg += " expected size " + std::to_string(expectedSize) + " actual size " + std::to_string(userInputList.size());
        std::cerr << emsg << "\n";
        return true;
    }

    return false;
}

template <typename DictID, typename DictName>
[[nodiscard]] bool GenericDictionary<DictID, DictName>::hasID(DictID id) noexcept
{
    auto found = idSearchTable.find(id);
    return (found != idSearchTable.end());
}

template <typename DictID, typename DictName>
[[nodiscard]] bool GenericDictionary<DictID, DictName>::hasName(DictName name) noexcept
{
    auto found = nameSearchTable.find(name);
    return (found != nameSearchTable.end());
}

template <typename DictID, typename DictName>
[[nodiscard]] bool GenericDictionary<DictID, DictName>::reportDuplicateNameErrors(std::string funcName) noexcept
{
    std::vector<DictType> duplicates;
    // Find all duplicate names, store the name and the ID to generate an
    // error message after all duplicates are found.
    for (auto defintion: userInputList)
    {
        std::size_t countNames = std::ranges::count(userInputList, defintion.names, &DictType::names);
        if (countNames > 1) 
        {
            duplicates.push_back(defintion);
        }
    }

    if (duplicates.size() == 0)
    {
        return false;
    }

    std::string emsg("In GenericDictionary::" + funcName + ": Duplicate names found: \n\t");
    for (auto duplicate: duplicates)
    {
        emsg += "Name: " + duplicate.names + " Integer Value of ID: " +
            std::to_string(static_cast<std::size_t>(duplicate.id)) + "\n\t";
    }

    std::cerr << emsg << "\n";

    return true;
}

/*
 * Find and report any missing or duplicated enums
 */
template <typename DictID, typename DictName>
[[nodiscard]] bool GenericDictionary<DictID, DictName>::testForIDNoneLinearDefinitions(
    std::string funcName
    ) noexcept
{
    bool noErrors = true; 
    std::string emsg("In GenericDictionary::" + funcName + ": \n\t");

    noErrors = sortAndTestIds(emsg);
    if (!noErrors)
    {
        std::cerr << emsg << "\n";
    }


    return noErrors;
}

template <typename DictID, typename DictName>
[[nodiscard]] bool GenericDictionary<DictID, DictName>::addDefinition(DictType newDef) noexcept
{
    if (!alreadyDefined(newDef))
    {
        idSearchTable.insert({newDef.id, newDef.names});
        nameSearchTable.insert({newDef.names, newDef.id});
        return true;
    }

    return false;
}

/******************************************************************************
 * Unit testing and performance testing of the GenericDictinary class are
 * here to ease the maintenance of the testing and of the class. By default
 * if we are perfomance testing we are also unit testing.
 ******************************************************************************/

#ifdef GD_PERFORMANCE_TEST
#include "UtilityTimer.h"
#endif // GD_PERFORMANCE_TEST

#ifdef GD_UNIT_TEST
#include <iostream>

template <typename DictID, typename DictName>
bool GenericDictionary<DictID, DictName>::selfUnitTest()
{

    return true;
}

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

