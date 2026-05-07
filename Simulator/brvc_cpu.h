#ifndef BRVC_CPU_H
#define BRVC_CPU_H

#include <array>
#include <cstddef>
#include <cstdint>

#include "brvc_rom.h"
#include "brvc_ram.h"

// BRVC (Basic RISC-V Core) namespace
namespace brvc {

class Cpu {
    public:
        static constexpr size_t kNumRegisters = 32;

        explicit Cpu(Rom& rom, Ram& ram);

        // Non-copyable.
        Cpu(const Cpu&) = delete;
        Cpu& operator=(const Cpu&) = delete;

        // Moveable.
        Cpu(Cpu&&) = default;
        Cpu& operator=(Cpu&&) = default;

        void Step();

        uint32_t ReadRegister(size_t index) const;
        void     WriteRegister(size_t index, uint32_t value);

        uint32_t GetProgramCounter() const;
        void     SetProgramCounter(uint32_t value);

        void Reset();

    private:
        struct DecodedInstruction {
            // Decoded instruction formats.
            // Placeholder for the time being.
            // TODO: Replace this later.
            uint32_t raw;
        };

        uint32_t           Fetch();
        DecodedInstruction Decode(uint32_t raw);
        void               Execute(const DecodedInstruction& instruction);

        // Reference to ROM and RAM.
        Rom& rom_;
        Ram& ram_;

        uint32_t raw_instruction_ = 0;
        DecodedInstruction decoded_instruction_;
        std::array<uint32_t, kNumRegisters> registers_;
        uint32_t pc_;
};

} // namespace brvc

#endif // BRVC_CPU_H