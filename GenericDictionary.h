#ifndef GENERICDICTIONARY_H_
#define GENERICDICTIONARY_H_

// Allow debug in either gcc or MSVS
#ifdef _DEBUG
#define GD_DEBUG
#else
#ifndef NDEBUG
#define GD_DEBUG
#endif
#endif

#include <algorithm>
#include <exception>
#include <expected>
#include <initializer_list>
#include <ranges>
#include <stdexcept>
#include <string>
#include <vector>
#include <unordered_map>

/*
 * This class provides a basic conversion of enums or integers to strings.  
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
 * 
 */

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
    GenericDictionary(std::initializer_list<DictType> definitions);
    GenericDictionary(std::ranges::input_range auto&& definitions);
    virtual ~GenericDictionary() = default;
    auto lookupID(DictName itemName) const -> std::expected<DictID, DictionaryLookUpError>;
    auto lookupName(DictID id) const -> std::expected<DictName, DictionaryLookUpError>;

#ifdef GD_UNIT_TEST
    std::vector<DictType> getUserInput() const noexcept { return userInputList; }
#endif

private:
    [[nodiscard]] bool commonInternalListBuilder(std::string funcName) noexcept;
    [[nodiscard]] bool alreadyDefined(DictType candidate) noexcept { return hasID(candidate.id) || hasName(candidate.names); };
    [[nodiscard]] bool reportDuplicateNameErrors(std::string funcName) noexcept;
    [[nodiscard]] bool hasID(DictID id) noexcept;
    [[nodiscard]] bool hasName(DictName name) noexcept;
    [[nodiscard]] bool sortAndTestIds() noexcept;
    [[nodiscard]] bool testForIDNoneLinearDefinitions(std::string funcName) noexcept;
    [[nodiscard]] bool addDefinition(DictType newDef) noexcept;

    std::unordered_map<DictID, DictName> idSearchTable;
    std::unordered_map<DictName, DictID> nameSearchTable;
    std::vector<DictType> userInputList;
    std::string exceptionWhatMsg;
};

/******************************************************************************
 * Public interface.
 *****************************************************************************/
template <typename DictID, typename DictName>
GenericDictionary<DictID, DictName>::GenericDictionary(std::initializer_list<DictType> definitions)
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
GenericDictionary<DictID, DictName>::GenericDictionary(std::ranges::input_range auto&& definitions)
: userInputList{definitions.begin(), definitions.end()}
{
    if (!commonInternalListBuilder("Constructor"))
    {
        std::logic_error constructorError(exceptionWhatMsg);
        throw constructorError;
    }
}

template <typename DictID, typename DictName>
auto GenericDictionary<DictID, DictName>::lookupID(DictName itemName) const
    -> std::expected<DictID, DictionaryLookUpError>
{
    auto definition = nameSearchTable.find(itemName);
    if (definition != nameSearchTable.end())
    {
        return definition->second;
    }

    return std::unexpected{DictionaryLookUpError::Name_Not_Found};
};

template <typename DictID, typename DictName>
auto GenericDictionary<DictID, DictName>::lookupName(DictID id) const
    -> std::expected<DictName, DictionaryLookUpError>
{
    auto definition = idSearchTable.find(id);
    if (definition != idSearchTable.end())
    {
        return definition->second;
    }

    return std::unexpected{DictionaryLookUpError::Id_Not_Found};
}

/******************************************************************************
 * Private methods
 *****************************************************************************/

template<typename DictID, typename DictName>
[[nodiscard]] bool GenericDictionary<DictID, DictName>::commonInternalListBuilder(std::string funcName) noexcept
{
    bool hasErrors = false;
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
                exceptionWhatMsg += "duplicate enum values: " + std::to_string(id1) + 
                    " Name: " + defIter1->names + " - " + std::to_string(id2) +
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

