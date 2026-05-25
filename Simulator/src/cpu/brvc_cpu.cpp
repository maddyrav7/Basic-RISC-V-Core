#include "brvc_cpu.h"

#include <iomanip>
#include <iostream>

#include "brvc_arch.h"
#include "brvc_utils.h"

// BRVC (Basic RISC-V Core) namespace
namespace brvc {

Cpu::Cpu(Rom& rom, Ram& ram)
    : rom_(rom),
      ram_(ram),
      raw_instruction_(0),
      decoded_instruction_{0},
      registers_{},
      pc_(0)
      {}

void Cpu::Step() {
    raw_instruction_ = Fetch();
    decoded_instruction_ = Decode(raw_instruction_);
    Execute(decoded_instruction_);
}

uint32_t Cpu::ReadRegister(size_t index) const {
    BRVC_ASSERT(index < kNumRegisters, "Given index (%zu) too high for number of registers (%zu).",
                index, kNumRegisters);

    return registers_.at(index);
}

void Cpu::WriteRegister(size_t index, uint32_t value) {
    BRVC_ASSERT(index < kNumRegisters, "Given index (%zu) too high for number of registers (%zu).",
                index, kNumRegisters);

    // r0 is tied to 0.
    if (index == 0) {
        return;
    }

    registers_[index] = value;
}

uint32_t Cpu::GetProgramCounter() const {
    return pc_;
}

void Cpu::SetProgramCounter(uint32_t value) {
    // PC needs to be aligned.
    BRVC_ASSERT_ALIGNED(value, arch::kArchWidthBytes);

    pc_ = value;
}

void Cpu::Reset() {
    raw_instruction_ = 0;
    decoded_instruction_ = {0};
    registers_.fill(0);
    pc_ = 0;
}

uint32_t Cpu::Fetch() {
    return rom_.ReadWord(pc_);
}

Cpu::DecodedInstruction Cpu::Decode(uint32_t raw) {
    // TODO: This is a placeholder implementation. This needs to be rewritten with decoding logic for each instruction
    // type.
    Cpu::DecodedInstruction instruction{};
    instruction.raw = raw;
    return instruction;
}

void Cpu::Execute(const DecodedInstruction& instruction) {
    // TODO: This is a placeholder implementation. This needs to be rewritten with the correct execution logic for each
    // instruction type and instruction.
    (void)instruction;
    // TODO: Rollover is allowed here for the time being. Determine whether it should be, and adjust accordingly.
    pc_ += arch::kArchWidthBytes;
}

void Cpu::PrintRegisters() const {
    constexpr int kColumnWidth = 15;

    // Title
    utils::PrintNewLine();
    utils::PrintSeparator();
    std::cout << "CPU Registers Status\n";
    utils::PrintSeparator();

    // Header
    std::cout << std::left
              << std::setw(kColumnWidth) << "Register"
              << std::setw(kColumnWidth) << "Value"
              << '\n';

    // Separator
    utils::PrintSeparator();

    // Registers and Values
    for (size_t reg = 0; reg < kNumRegisters; reg++) {
        // Register names
        std::cout << std::left << std::dec
                  << "x" << std::setw(kColumnWidth - 1) << reg;

        // Register values
        std::cout << std::uppercase << std::hex
                  << std::left
                  << "0x" << std::setw(kColumnWidth - 2) << registers_.at(reg);
    }
    
    std::cout << std::dec;
    utils::PrintNewLine();
}

} // namespace brvc