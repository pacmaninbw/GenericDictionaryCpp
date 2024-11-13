#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include "../tests/UtilityTimer.h"
#include "PerformanceTestGenerator.h"

PerformanceTestGenerator::PerformanceTestGenerator(TestParameters testParameters)
 : testValues{testParameters.testValues},
    progName{testParameters.progName},
    version{testParameters.version},
    useCout{testParameters.useCout},
    generationType{testParameters.generationType},
    inputRadix{testParameters.inputRadix}
{
    if (!testParameters.useCout)
    {
        stdCoutBuffBackup = std::cout.rdbuf();
        outPutFileName = testParameters.outPutFile;
        outPutFile.open(outPutFileName);
        std::cout.rdbuf(outPutFile.rdbuf());
    }
}

PerformanceTestGenerator::~PerformanceTestGenerator()
{
    if (!useCout)
    {
        std::cout.rdbuf(stdCoutBuffBackup);
        outPutFile.close();
    }
}

bool PerformanceTestGenerator::generateAllPerformaneTests() noexcept
{
    std::cout << "#ifndef GD_PERFORMANCETEST_H_\n";
    std::cout << "#define GD_PERFORMANCETEST_H_\n\n";
    std::cout << "// Warning, this file is generated by a test generator " << progName << " " << version << "\n";
    std::cout << "// This file contains " << testValues.size() << " performance tests\n";
    std::cout << "// ";
    for (auto testEnumCount: testValues)
    {
        std::cout << " test " << testEnumCount << " enum values";
    }
    std::cout << "\n// The command line to reproduce this file is \n";
    std::cout << "//     " << reconstructCommandLine();
    std::cout << "\n\n";
    std::cout << "#define GD_PERFORMANCE_TEST\n";
    std::cout << "#include \"GenericDictionary.h\"\n";
    std::cout << "#include \"GD_Testing.h\"\n";
    std::cout << "#include <string>\n";
    std::cout << "#include <vector>\n\n\n";

    std::cout << std::flush;
    if (!std::cout.flush())
    {
        return false;
    }

    if (!genPerformanceTest())
    {
        return false;
    }

    std::cout << "#endif // GD_PERFORMANCETEST_H_\n\n";

    std::cout << std::flush;
    if (!std::cout.flush())
    {
        return false;
    }

    return true;
}

bool PerformanceTestGenerator::generateEnumValues(std::size_t testSize) const noexcept
{
    for (std::size_t lcount = MinEnumVal; lcount <= testSize; ++lcount)
    {
        std::cout << "\t" << enumTemplate << lcount << ",\n";
    }

    std::cout << std::flush;
    if (!std::cout.flush())
    {
        return false;
    }

    return true;
}

bool PerformanceTestGenerator::generateEnum(std::size_t testSize) const noexcept
{
    std::cout << "enum class " << enumName << testSize << "\n";
    std::cout << "{\n\t" << firstEnum <<",\n";

    if (!generateEnumValues(testSize))
    {
        return false;
    }

    std::cout << "\t" << lastEnum << "\n};\n";
    std::cout << std::flush;
    if (!std::cout.flush())
    {
        return false;
    }

    return true;
}

/*
 * Generate the command line to reproduce the output being generated.
 * The command line is generated no matter how the user input the data.
 * The command line generated is accurate, but, it may not be the exact
 * command line input, simple flags such as -f, -c and -s are translated
 * to the more meaningful -- flag equivalents such as --output-file for -f,
 * --test-count for -c and --test-size for -s.
 */
std::string PerformanceTestGenerator::reconstructCommandLine() noexcept
{
    std::stringstream cmdLineBuff;

    cmdLineBuff << progName << ' ';

    if (!useCout)
    {
        cmdLineBuff << "--output-file " << outPutFileName << ' ';
    }

    cmdLineBuff << "--test-count " + std::to_string(testValues.size()) + ' ';

    cmdLineBuff << "--radix-" << std::to_string(inputRadix) + ' ';

    commandLineTestSizes(cmdLineBuff);

    cmdLineBuff << commandLineTestType();

    return cmdLineBuff.str();
}

void PerformanceTestGenerator::commandLineTestSizes(std::stringstream &cmdLineBuff) noexcept
{
    for (auto testSize: testValues)
    {
        cmdLineBuff << "--test-size ";
        if (inputRadix == 10)
        {
            cmdLineBuff << std::to_string(testSize);
        }
        else
        {
            cmdLineBuff << std::hex << testSize;
        }
        cmdLineBuff << ' ';
    }
}

std::string PerformanceTestGenerator::commandLineTestType() noexcept
{
    switch (generationType)
    {
        default:
            return "--both-tests";
        case TestGenerationType::InitializationList_input :
            return "--init-list-test";
        case TestGenerationType::Vector_input :
            return "--vector-test";
    }
}

void PerformanceTestGenerator::dataPairLineOut(std::size_t lineC, std::string tabPlusOpen, bool lastLine) const noexcept
{
    std::cout << tabPlusOpen << lineC << ", \"" << testStrTemplate << lineC << "\"}";
    
    if (!lastLine)
    {
        std::cout << ",";
    }

    std::cout << "\n";
}

bool PerformanceTestGenerator::genTestDataPairs(std::size_t testSize, std::size_t tabCount = 1) const noexcept
{
    std::string tSize(std::to_string(testSize));
    std::string enumValue(enumName + std::to_string(testSize) + "::" + enumTemplate);
    auto tabPlusOpen = std::string(tabCount, '\t') + '{' + enumValue;

    std::size_t lcount = MinEnumVal;
    for (; lcount < testSize ; ++lcount)
    {
        dataPairLineOut(lcount, tabPlusOpen, false);
    }
    dataPairLineOut(lcount, tabPlusOpen, true);

    std::cout << std::flush;
    if (!std::cout.flush())
    {
        return false;
    }

    return true;
}

bool PerformanceTestGenerator::genTestDataPairsTable(std::size_t testSize) const noexcept
{
    std::cout << "\nstatic std::vector<TestPairs<" << enumName + std::to_string(testSize) <<
        ">> " << testDataName << std::to_string(testSize) << " =\n{\n";
    if (!genTestDataPairs(testSize))
    {
        return false;
    }
    std::cout << "};\n\n";

    std::cout << std::flush;
    if (!std::cout.flush())
    {
        return false;
    }

    return true;
}

std::string PerformanceTestGenerator::genTestFunc(std::size_t testSize, bool useVector) const noexcept
{
    std::string enumBase(enumName + std::to_string(testSize));
    std::string testName("performanceTest" + std::to_string(testSize) + (useVector? "Vector" : "ListInit"));

    std::cout << "static bool " << testName << "()\n{\n" <<
        "\tbool testPassed = true;\n\tUtilityTimer testTimer;\n\n\tstd::string testName(\"" <<
        testName <<"\");\n\n\ttry {\n" <<
        "\t\tstd::clog << \"Testing GenericDictionary with enum of size " << testSize << "\\n\";" <<
        "\n\t\ttestTimer.startTimer();" <<
        "\n\t\tGenericDictionary <" << enumBase  << ", std::string> underTest (";

    enumBase += "::";

    if (useVector)
    {
        std::cout << " " << testDataName << std::to_string(testSize);
    }
    else
    {
        std::cout << "\n\t\t\t{\n";
        if (!genTestDataPairs(testSize, 4))
        {
            return "";
        }
        std::cout << "\t\t\t}\n\t\t";
    }

    std::cout << ");\n\t\ttestTimer.stopTimerAndReport(\"Performance Test Constructor \" + testName + \" \");\n\n\t\t" <<
        "testPassed = performanceExecution<" << enumName + std::to_string(testSize)  <<
        ">(underTest, testData" << testSize << ", testName);\n"
        "\n\t}\n"
        "\tcatch (const std::logic_error &le)\n\t{\n"
        "\t\tstd::cerr << \"TestGenericDictionary::testContructorPositivePath() logic_error: \" << le.what() << \"\\n\\n\";\n"
        "\t\ttestPassed = false;\n\t}\n"
        "\tcatch(const std::exception& e)\n\t{\n"
        "\t\tstd::cerr << \"TestGenericDictionary::testContructorPositivePath() UNKNOWN EXCEPTION: \" << e.what() << \"\\n\";\n"        
        "\t\ttestPassed = false;\n\t}\n";
    std::cout << "\tstd::clog << \"GenericDictionary Constructor " << testName <<
        " \" << (testPassed? \"PASSED\\n\\n\": \"FAILED\\n\\n\");\n\n"
        "\treturn testPassed;\n}\n\n";

    std::cout << std::flush;
    if (!std::cout.flush())
    {
        return "";
    }

    return testName;
}

bool PerformanceTestGenerator::generateAllTestDataAndTest(std::size_t testSize) noexcept
{
    std::string currentTest;

    std::cout <<
        "// Generated GenericDictionary Performance Test Values for an enum class of "
        << testSize << " enum values\n\n";

    if (!generateEnum(testSize)) return false;

    std::cout << "\n";
    if (!genTestDataPairsTable(testSize)) return false;

    std::cout << "\n";
    if (generationType != TestGenerationType::Vector_input)
    {
        if ((currentTest = genTestFunc(testSize, false)).length() > 0)
        {
            testNames.push_back(currentTest);
        }
        else
        {
            return false;
        }
    }

// since we are testing using the previously generated test data, just a simple test
    if (generationType != TestGenerationType::InitializationList_input)
    {
        std::cout << "\n";
        if ((currentTest = genTestFunc(testSize, true)).length() > 0)
        {
            testNames.push_back(currentTest);
        }
        else
        {
            return false;
        }
    }

    return true;
}

bool PerformanceTestGenerator::genPerformanceTest() noexcept
{
    for (auto testSize: testValues)
    {
        if (!generateAllTestDataAndTest(testSize))
        {
            return false;
        }
    }

    std::cout << "bool performancetests()\n{\n\tbool allTestsPassed = true;\n\n";
    for (auto test: testNames)
    {
        std::cout << "\tif (allTestsPassed)\n\t{\n\t\tallTestsPassed = " << test << "();\n\t}\n";
    }

    std::cout << "\n\treturn allTestsPassed;\n}\n\n";
    std::cout << std::flush;
    if (!std::cout.flush())
    {
        return false;
    }

    return true;
}
