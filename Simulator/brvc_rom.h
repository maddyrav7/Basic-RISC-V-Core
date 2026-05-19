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
        uint8_t  ReadByte(uint32_t addr);
        uint32_t ReadWord(uint32_t addr);

        uint64_t GetSize();

        // Load is used to (re)initialize.
        void LoadRom(uint32_t base_addr, uint64_t size, const std::vector<uint8_t>& image);
        // Clear removes all addresses (effectively sets everything to 0).
        void Clear();

        void PrintRom() const;

    private:
        std::unordered_map<uint32_t, uint8_t> rom_;
        uint64_t size_;
};

} // namespace brvc

#endif // BRVC_ROM_H