#include "brvc_system.h"

#include <iostream>

#include "brvc_arch.h"
#include "brvc_utils.h"

// BRVC (Basic RISC-V Core) namespace
namespace brvc {

System::System()
    : rom_(arch::kRomSizeBytes),
      ram_(arch::kRamSizeBytes),
      cpu_(rom_, ram_)
      {}

System::System(uint64_t romSize, uint64_t ramSize)
    : rom_(romSize),
      ram_(ramSize),
      cpu_(rom_, ram_)
      {}

void System::Step() {
    cpu_.Step();
}

void System::Run() {
    // TODO: This is likely wrong. Adjust this later once it becomes more clear how this should be handled.
    while (true) {
        Step();
    }
}

Cpu& System::GetCpu() {
    return cpu_;
}

Rom& System::GetRom() {
    return rom_;
}

Ram& System::GetRam() {
    return ram_;
}

void System::Reset() {
    cpu_.Reset();
    rom_.Clear();
    ram_.Clear();
}

void System::PrintState() {
    utils::PrintSeparator();
    std::cout << "System State\n";
    utils::PrintSeparator();

    std::cout << "\nRegisters\n\n";
    cpu_.PrintRegisters();

    utils::PrintSeparator();

    std::cout << "\nROM\n\n";
    rom_.PrintRom();

    utils::PrintSeparator();

    std::cout << "\nRAM\n\n";
    ram_.PrintRam();

    utils::PrintSeparator();
    utils::PrintNewLine();
}

} // namespace brvc