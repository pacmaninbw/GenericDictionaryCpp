#ifndef TESTCOLUMNDICTIONARY_H
#define TESTCOLUMNDICTIONARY_H

/*
 * Testing the ColumnDictionary class, which just uses the base class.
 *
 * The ColumnDictionary class was selected for testing because it is being
 * used in another project.
 */

#include "../include/GenericDictionary.h"
#include "columnidenum.h"
#include <string>
#include <vector>

class TestColumnDictionary
{
public:
    TestColumnDictionary();
    ~TestColumnDictionary() = default;
    bool executeTests() noexcept;
    bool executeStandAloneTests() noexcept;
    bool executeCommonGDTests() noexcept;

private:
    bool commonGDIdToName(GenericDictionary<ColumnIds, std::string> &underTest, ColumnIds input, std::string expectedOutput) noexcept;
    bool commonGDNameToID(GenericDictionary<ColumnIds, std::string> &underTest, std::string input, ColumnIds expectedOutput) noexcept;
    bool standAloneIdToName(ColumnIds input, std::string expectedOutput) noexcept;
    bool standAloneNameToID(std::string input, ColumnIds expectedOutput) noexcept;
    std::vector<GenricDictionaryDataPair<ColumnIds, std::string>> positiveColumnTestData;
};

#endif // TESTCOLUMNDICTIONARY_H