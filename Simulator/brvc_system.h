#ifndef BRVC_SYSTEM_H
#define BRVC_SYSTEM_H

#include <cstdint>
#include <vector>

#include "brvc_cpu.h"
#include "brvc_ram.h"
#include "brvc_rom.h"

// BRVC (Basic RISC-V Core) namespace
namespace brvc {

class System {
    public:
        static constexpr uint64_t kRomSizeBytes = 64ULL * 1024; // 64 KB
        static constexpr uint64_t kRamSizeBytes = 4ULL * 1024 * 1024 * 1024; // 4 GB

        explicit System();
        explicit System(uint64_t romSize, uint64_t ramSize);

        // Non-copyable.
        System(const System&) = delete;
        System& operator=(const System&) = delete;

        // Moveable.
        System(System&&) = default;
        System& operator=(System&&) = default;

        void Step();
        void Run();

        Cpu& GetCpu();
        Rom& GetRom();
        Ram& GetRam();

        void Reset();

        void PrintState();

    private:
        Cpu cpu_;
        Rom rom_;
        Ram ram_;

};

} // namespace bvrc

#endif // BRVC_SYSTEM_H