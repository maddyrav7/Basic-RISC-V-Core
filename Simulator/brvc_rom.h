#ifndef BRVC_ROM_H
#define BRVC_ROM_H

#include <cstdint>
#include <unordered_map>
#include <vector>

// BRVC (Basic RISC-V Core) namespace
namespace brvc {

class Rom {
    public:
        explicit Rom(uint64_t size);

        // Non-copyable.
        Rom(const Rom&) = delete;
        Rom& operator=(const Rom&) = delete;

        // Moveable.
        Rom(Rom&&) = default;
        Rom& operator=(Rom&&) = default;

        // Read operations.
        uint8_t  Read8 (uint32_t addr) const;
        uint32_t Read32(uint32_t addr) const;

        // Load is used to (re)initialize.
        void LoadRom(uint32_t base_addr, uint32_t size, const std::vector<uint8_t>& image);
        // Clear sets all of the ROM to 0.
        void Clear (void);

    private:
        void CheckBounds(uint32_t addr) const;

        std::unordered_map<uint32_t, uint8_t> rom_;
};

} // namespace brvc

#endif // BRVC_ROM_H