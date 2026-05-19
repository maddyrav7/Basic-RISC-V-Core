#ifndef BRVC_TEST_H
#define BRVC_TEST_H

#include <functional>
#include <iostream>
#include <string>
#include <vector>

#include "brvc_utils.h"

#define BRVC_TEST_ASSERT_TRUE(condition) \
    do { \
        if (!(condition)) { \
            throw std::runtime_error(__FILE__ ":" __LINE__ ":" __func__ ": ASSERT_TRUE failed: " #condition); \
        } \
    } while (false)

#define BRVC_TEST_ASSERT_EQ(A, B) \
    do { \
        if ((A) != (B)) { \
            throw std::runtime_error(__FILE__ ":" __LINE__ ":" __func__ ": ASSERT_EQ failed: " #A " != " #B); \
        } \
    } while (false)

namespace brvc::test {

struct BrvcTest {
    std::string name;
    std::function<void()> func;
};

static inline std::vector<BrvcTest>& GetTests() {
    static std::vector<BrvcTest> testList;
    return testList;
}

inline void AddTest(const std::string& name, std::function<void()> func) {
    GetTests().push_back({name, func});
}

inline int RunTests() {
    int numPassed = 0;
    int numFailed = 0;

    utils::PrintSeparator();
    std::cout << "\n";
    for (const auto& test : GetTests()) {
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
    std::cout << "\n" << numPassed << "/" << numPassed + numFailed << " tests passed.\n\n";
    utils::PrintSeparator();

    return numFailed;
}

} // namespace brvc::test

#endif // BRVC_TEST_H