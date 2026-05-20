#include "brvc_test.h"

#include <iostream>
#include <string>

namespace brvc::test {

namespace {

static inline std::vector<BrvcTestSuite>& GetTestSuites() {
    static std::vector<BrvcTestSuite> testSuites;
    return testSuites;
}

} // namespace
    
BrvcTestSuite::BrvcTestSuite(const std::string& name)
    : name_(name) {}

void BrvcTestSuite::AddTest(const std::string& name, std::function<void()> func) {
    tests_.push_back({name, func});
}

int BrvcTestSuite::RunSuite() {
    int numPassed = 0;
    int numFailed = 0;
    int numTests = 0;

    utils::PrintSeparator();
    std::cout << "TEST SUITE: " << name_ <<  "\n\n";
    for (const auto& test : GetTests()) {
        ++numTests;
        std::cout << "[ RUNNING ] " << test.name << "\n";
        try {
            test.func();
            ++numPassed;
            std::cout << "[ PASSED  ] " << test.name << "\n";
        }
        catch (const std::exception& e) {
            ++numFailed;
            std::cout << "[ FAILED ] " << test.name << ": " << e.what() << "\n";
        }
        catch (...) {
            ++numFailed;
            std::cout << "[ FAILED ] " << test.name << ": unknown error\n";
        }
    }

    utils::PrintSeparator();
    std::cout << "TEST SUITE " << name_ << " RESULTS: "
              << numPassed << " PASSED, " << numFailed << " FAILED, " << numTests << " TOTAL.\n";
    utils::PrintSeparator();

    results_ = std::tuple(numPassed, numFailed, numTests);

    return numFailed;
}

const std::string& BrvcTestSuite::GetName() const {
    return name_;
}

const std::vector<BrvcTestCase>& BrvcTestSuite::GetTests() const {
    return tests_;
}

void AddTestSuite(const BrvcTestSuite& suite) {
    GetTestSuites().push_back(suite);
}

int RunTestSuites() {
    int numPassedSuites = 0;
    int numFailedSuites = 0;
    int numPassedTests = 0;
    int numTotalTests = 0;

    for (auto& suite : GetTestSuites()) {
        utils::PrintNewLine();
        // Results are retrieved later in this function.
        if (suite.RunSuite() == 0) {
            ++numPassedSuites;
        }
        else {
            ++numFailedSuites;
        }
    }

    utils::PrintSeparator('=');
    std::cout << "TESTING SUMMARY\n";
    utils::PrintSeparator('=');
    utils::PrintNewLine();

    for (auto& suite : GetTestSuites()) {
        int numPassed = 0;
        int numFailed = 0;
        int numTests = 0;
        std::tie(numPassed, numFailed, numTests) = suite.GetResults();
        std::cout << suite.GetName() << ": "
                  << numPassed << " PASSED, " << numFailed << " FAILED, " << numTests << " TOTAL.\n";

        numPassedTests += numPassed;
        numTotalTests += numTests;
    }

    utils::PrintNewLine();
    utils::PrintSeparator('=');
    std::cout << "FINAL SUMMARY: "
              << numPassedSuites << " SUITES PASSED, " << numFailedSuites << " SUITES FAILED, "
              << " OUT OF " << numPassedSuites + numFailedSuites << " TOTAL SUITES ("
              << numPassedTests << "/" << numTotalTests << " tests passed).\n";
    utils::PrintSeparator('=');
    utils::PrintNewLine();
}

} // namespace brvc::test