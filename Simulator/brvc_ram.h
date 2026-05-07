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
        uint8_t  Read8 (uint32_t addr) const;
        uint32_t Read32(uint32_t addr) const;

        // Write operations.
        void Write8 (uint32_t addr, uint8_t value);
        void Write32(uint32_t addr, uint32_t value);

        // Load and reset. Load is used to (re)initialize.
        void LoadRam(uint32_t base_addr, uint32_t size, const std::vector<uint8_t>& ram);
        // Clear sets all of the RAM to 0.
        void Clear (void);

    private:
        void CheckBounds(uint32_t addr) const;

        std::unordered_map<uint32_t, uint8_t> ram_;
    };

} // namespace brvc

#endif // BRVC_RAM_H