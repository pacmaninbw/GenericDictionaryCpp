#ifndef GENERICDICTIONARY_H_
#define GENERICDICTIONARY_H_

#include <algorithm>
#include <concepts>
#include <exception>
#include <initializer_list>
#include <optional>
#include <ranges>
#include <stdexcept>
#include <string>
#include <vector>
#include <unordered_map>

/*
 * This class provides a basic conversion of enums or integers to strings. The
 * class can be used as is, or as a base for more complex object.
 * 
 * More complex objects than strings are also supported, however, overrides will
 * be necessary.
 * 
 * This class makes an attempt to find any missing definitions during construction.
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

// The following constructors will throw exceptions if there are problems in the
// list of definitions.
    GenericDictionary(DictID MinValue, DictID MaxValue, std::initializer_list<DictType> definitions);
    GenericDictionary(DictID MinValue, DictID MaxValue, std::ranges::input_range auto&& definitions);
    virtual ~GenericDictionary() = default;

    std::optional<DictID> getIds(DictName itemName);
    std::optional<DictName> getNames(DictID id);

#ifdef GD_UNIT_TEST
    std::vector<DictType> getUserInput() const noexcept { return userInputList; }    bool selfUnitTest();
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
    [[nodiscard]] bool sortAndTestIds() noexcept;
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
    std::string exceptionWhatMsg;
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
        std::logic_error constructorError(exceptionWhatMsg);
        throw constructorError;
    }
}

template <typename DictID, typename DictName>
GenericDictionary<DictID, DictName>::GenericDictionary(DictID MinValue, DictID MaxValue, std::ranges::input_range auto&& definitions)
: MinimumValue{MinValue},
MaximumValue{MaxValue},
userInputList{definitions.begin(), definitions.end()}
{
    if (!commonInternalListBuilder("Constructor"))
    {
        std::logic_error constructorError(exceptionWhatMsg);
        throw constructorError;
    }
}

template <typename DictID, typename DictName>
std::optional<DictID> GenericDictionary<DictID, DictName>::getIds(DictName itemName)
{
    auto definition = nameSearchTable.find(itemName);
    if (definition != nameSearchTable.end())
    {
        return definition->second;
    }

    return std::nullopt;
};

template <typename DictID, typename DictName>
std::optional<DictName> GenericDictionary<DictID, DictName>::getNames(DictID id)
{
    auto definition = idSearchTable.find(id);
    if (definition != idSearchTable.end())
    {
        return definition->second;
    }

    return std::nullopt;
}

#ifdef DEBUG
#include <iostream>
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
 * Private methods
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

/*
 * Sorts the user input. After sorting the input performs various tests
 * on the validity of the input, finding duplicate IDs or missing IDs. The
 * input must be sorted before the the error checking can be performed.
 */
template <typename DictID, typename DictName>
[[nodiscard]] bool GenericDictionary<DictID, DictName>::sortAndTestIds() noexcept
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
                exceptionWhatMsg += "duplicate enum values: " + std::to_string(id1) + " Name: " + defIter1->names + " - " + std::to_string(id2) +
                    " Name: " + defIter2->names + "\n\t";
            }
            else
            {
                exceptionWhatMsg += "missing enum value: " + std::to_string((id2 - 1)) + "\n\t";
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
        exceptionWhatMsg += "In GenericDictionary::" + funcName + " missing definition values";
        exceptionWhatMsg += " expected size " + std::to_string(expectedSize) + " actual size " + std::to_string(userInputList.size());
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

    exceptionWhatMsg += "In GenericDictionary::" + funcName + ": Duplicate names found: \n\t";
    for (auto duplicate: duplicates)
    {
        exceptionWhatMsg += "Name: " + duplicate.names + " Integer Value of ID: " +
            std::to_string(static_cast<std::size_t>(duplicate.id)) + "\n\t";
    }

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
    exceptionWhatMsg += "In GenericDictionary::" + funcName + ": \n\t";

    noErrors = sortAndTestIds();

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

#endif // GENERICDICTIONARY_H_

