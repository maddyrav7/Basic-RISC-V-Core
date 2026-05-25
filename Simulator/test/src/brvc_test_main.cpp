#include "brvc_test.h"

#include "brvc_rom_test.h"

int main() {

    // Add test suites.
    brvc::test::AddRomTestSuite();

    // Run test suites.
    return brvc::test::RunTests();
}