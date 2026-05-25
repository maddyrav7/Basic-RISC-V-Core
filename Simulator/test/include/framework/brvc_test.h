#ifndef BRVC_TEST_H
#define BRVC_TEST_H

#include <functional>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#include "brvc_utils.h"

namespace brvc::test {

struct BrvcTestCase {
    std::string name;
    std::function<void()> func;
};

class BrvcTestSuite {
    public:
        explicit BrvcTestSuite(const std::string& name);

        void AddTest(const std::string& name, std::function<void()> func);
        int  RunSuite();

        const std::string& GetName() const;
        const std::vector<BrvcTestCase>& GetTests() const;
        const std::tuple<int, int, int>& GetResults() const;

    private:
        std::string name_;
        std::vector<BrvcTestCase> tests_;
        std::tuple<int, int, int> results_;
};

void AddTestSuite(const BrvcTestSuite& suite);
int  RunTests();

} // namespace brvc::test

#define BRVC_TEST_ASSERT_TRUE(condition)                                                     \
    do {                                                                                     \
        if (!(condition)) {                                                                  \
            throw std::runtime_error(LOCATION_STRING + ": ASSERT_TRUE failed: " #condition); \
        }                                                                                    \
    } while (false)

#define BRVC_TEST_ASSERT_EQ(A, B)                                                            \
    do {                                                                                     \
        if ((A) != (B)) {                                                                    \
            throw std::runtime_error(LOCATION_STRING + ": ASSERT_EQ failed: " #A " != " #B); \
        }                                                                                    \
    } while (false)

#define BRVC_ADD_TEST(suite, test_name) suite.AddTest(#test_name, test_name)

#endif // BRVC_TEST_H