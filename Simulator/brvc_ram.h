#ifndef BRVC_RAM_H
#define BRVC_RAM_H

#include <cstdint>
#include <unordered_map>
#include <vector>

// BRVC (Basic RISC-V Core) namespace
namespace brvc {

class Ram {
    public:
        explicit Ram(uint64_t size);

        // Non-copyable.
        Ram(const Ram&) = delete;
        Ram& operator=(const Ram&) = delete;

        // Moveable.
        Ram(Ram&&) = default;
        Ram& operator=(Ram&&) = default;

        // Read operations.
        uint8_t  ReadByte(uint32_t addr);
        uint32_t ReadWord(uint32_t addr);

        // Write operations.
        void WriteByte(uint32_t addr, uint8_t value);
        void WriteWord(uint32_t addr, uint32_t value);

        uint64_t GetSize();

        // Load and reset. Load is used to (re)initialize.
        void LoadRam(uint32_t base_addr, uint64_t size, const std::vector<uint8_t>& ram);
        // Clear removes all addresses (effectively sets everything to 0).
        void Clear();

        void PrintRam() const;

    private:
        std::unordered_map<uint32_t, uint8_t> ram_;
        uint64_t size_;
    };

} // namespace brvc

#endif // BRVC_RAM_H