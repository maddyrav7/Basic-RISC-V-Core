## 2026-05-06

This is the official start of the project. To start, I defined the base specifications of the CPU (see the CPU_Specification document for reference). The first part of designing this CPU is creating a high-level functional simulator that abstracts away and simulates the behaviour of the CPU (see the Simulator_Notes document for more details). To summarize, I am creating a very simple 32-bit single cycle RISC-V CPU, without pipelining. For the time being, instruction memory and data memory are separated into ROM and RAM, respectively. \
Today, I defined header files for the RAM, ROM, CPU, and entire system, in the C++ simulator.

## 2026-05-14

Today I went back to complete the implementations of the ROM and RAM modules. Part of this involved creating a new header file, brvc_arch.h, with the arch namespace. This contains architecture-level constants. The ROM/RAM read and write methods were also renamed to Read/WriteByte and Read/WriteWord, mostly in case the architecture widths and sizing change if/when I eventually transition to a 64-bit CPU with RV64I. This might not be necessary in the long run, and using explicit sizes in the function names might actually be better, but that's a decision for later. It's becoming very clear that designing for flexibility and modularity in the early stages is very important, so that I can make changes and adjust the project scope as I continue. Failing to plan this out now, and failing to structure the project flexibly, might result in me needing to rewrite the entire simulator if I expand to 64-bits, add pipelining, add caching, etc. This is part of the reason why it took me around 3 hours to define the ROM and RAM modules, despite their simplicity; most of that involved high-level design and project organization for simplifying future work.

## 2026-05-16

- Created the GitHub repo for the project.
- Decided on a git commit format: conventional commits.
- Added an assertion utility called BRVC_ASSERT, which basically performs an assertion and outputs custom logging information if the assert fails. This will be very useful later on when I need to debug.
- Created the implementation for the brvc_cpu module.
- Modified ROM and RAM to check for word alignment before reading/writing words. Technically, the CPU shouldn't be issuing reads/writes on non-aligned addresses, but this just serves as a sanity check.
- Created the implementation for the brvc_system module.

Much of the code I wrote today is relatively self-explanatory; not many details to go over that aren't obvious from the code. Same as last time, most of the work went into properly organizing the project and its code to make future work easier. Over the next couple weeks though, I will transition into implementing individual instructions and writing tests. Once that work gets started, there will be more time spent on implementation over organization. Next task is creating mechanisms to dump out the system state at any point in time (mainly for debugging and verification). One thing, I might want to make a separate utils file to put the custom macros and other utilities inside. I haven't done that for the time being for convenience, but I might later.

## 2026-05-18

- Moved assert and alignment macros to a new brvc_utils.h file.
- Added print functions for ROM, RAM, CPU (registers), and the System modules to print out each module's state at any point in time.
- Revised system constructors to actually construct ROM, RAM, and CPU rather than take references to existing objects.
- Created a simple test framework, in brvc_test.h, that can be used to create tests, run them, and output their status. This framework is basically complete, and I just need to add different assertion types as needed to fully mark this as complete.
- I have not yet gotten around to running even a single line of code that I have written so far. I don't even know if it builds. The next task is to implement a test suite for the ROM module and run the tests to verify that ROM is working as intended.

## 2026-05-19

- Made some miscellaneous utils changes and bug fixes.
- Moved ROM and RAM sizes to arch header.
- Changed LoadRom to use an unordered_map instead of a vector. This was important because using a vector removes the sparse nature of an unordered_map. So if I want the loading process, and the subsequent state of ROM, to remain as sparse as necessary, I need to use an unordered_map.
- Added a test suite class for organizing sets of tests into suites.
- Created a brvc_test.cpp source file for better organization of the testing framework.
- The construction of test assertion error strings was incorrect (buggy), fixed that.
- Created a few ROM tests to start. Will create more in the future.
- Next step is actually to add and configure the build system, so that I can start testing things like running my ROM tests.

## 2026-05-25

- Moved each module into its own directory, and split source and header files into separate directories. This was done to support future expansion of each module. For example, if I later add a DRAM controller with specific access policies, a simple RAM module like I have today won't be enough. The module would likely grow to be much larger in size and complexity. To keep the systems modular, and keep individual modules as separate as possible (e.g. ROM doesn't need access to RAM files and vice versa), I made these changes to move each module into its own directory.
- Added the CMake build system.
- Note that each module in this case is built as its own library, which seems strange right now but is meant to support the pattern I mentioned above, where each of these individual libraries might grow significantly in size.
- Fixed bugs that caused build issues, like with some of the utility macros.
- Fixed the print outputs of various modules.
- Integrated the existing ROM test, which now produces the following output when run:

```
------------------------------
TEST SUITE: ROM

[ RUNNING ] ConstructCorrectSize
[ PASSED  ] ConstructCorrectSize
[ RUNNING ] DefaultReadByteZero
[ PASSED  ] DefaultReadByteZero
[ RUNNING ] LoadPartialRomReadsBackCorrectBytes

------------------------------
ROM Status
------------------------------
Address        Value
------------------------------
0x00000000     0x11
0x00001111     0x22
0x00002222     0x33
0x00003333     0x44
0x00004444     0x55
0x00005555     0x66
0x00006666     0x77
0x00007777     0x88
0x0000ABCD     0xBE
0x0000FFFF     0x00

[ PASSED  ] LoadPartialRomReadsBackCorrectBytes
[ RUNNING ] LoadFullRomReadsBackCorrectBytes
[ PASSED  ] LoadFullRomReadsBackCorrectBytes
------------------------------
TEST SUITE ROM RESULTS: 4 PASSED, 0 FAILED, 4 TOTAL.
------------------------------
==============================
TESTING SUMMARY
==============================

ROM: 4 PASSED, 0 FAILED, 4 TOTAL.

==============================
FINAL SUMMARY: 1 SUITES PASSED, 0 SUITES FAILED,  OUT OF 1 TOTAL SUITES (4/4 tests passed).
==============================
```

One thing I'm realizing, is that if I want to eventually transition this system to a 64-bit CPU, it might make sense for me to make that change sooner (i.e. now) rather than later. Especially with the amount of setup work involved with the simulator, it might be relatively difficult to transition to a 64-bit architecture after significant work has been done on the simulator. For this reason, I'm considering putting my other tasks on hold to spend some time transitioning the simulator to a 64-bit one right now. One more thing is that before I get around to writing the decoding logic, I need to finish the test suite for ROM, and create one for RAM (which is more complicated). For this reason, I've put the task on writing decoding logic on hold.