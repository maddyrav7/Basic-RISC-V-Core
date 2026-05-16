#include "brvc_system.h"
#include "brvc_arch.h"

// BRVC (Basic RISC-V Core) namespace
namespace brvc {

System::System(Cpu& cpu, Rom& rom, Ram& ram)
    : cpu_(cpu),
      rom_(rom),
      ram_(ram)
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

} // namespace brvc