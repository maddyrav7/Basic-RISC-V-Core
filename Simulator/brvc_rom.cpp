#include "brvc_rom.h"

#include <stdexcept>

#include "brvc_arch.h"

// BRVC (Basic RISC-V Core) namespace
namespace brvc {

Rom::Rom(uint64_t size) {
    if (size > arch::kAddressSpaceSize) {
        throw std::invalid_argument("ROM size exceeds address space.");
    }

    size_ = size;
}

uint8_t Rom::ReadByte(uint32_t addr) {
    if (static_cast<uint64_t>(addr) > size_) {
        throw std::out_of_range("Rom::ReadByte address exceeds address space.");
    }
    rom_.try_emplace(addr, uint8_t{0});
    return rom_.at(addr);
}

uint32_t Rom::ReadWord(uint32_t addr) {
    if ((static_cast<uint64_t>(addr) + static_cast<uint64_t>(arch::kWordBytes)) > size_) {
        throw std::out_of_range("Rom::ReadWord address exceeds address space.");
    }

    uint32_t word = 0;
    for (uint32_t i = 0; i < arch::kWordBytes; ++i) {
        // Little-endian.
        word |= (static_cast<uint32_t>(ReadByte(addr + i)) << (i * arch::kByteBits));
    }
}

void Rom::LoadRom(uint32_t base_addr,
                  uint64_t size,
                  const std::vector<uint8_t>& image) {
    if ((static_cast<uint64_t>(base_addr) + size) > static_cast<uint64_t>(size_)) {
        throw std::out_of_range("Rom::LoadRom address exceeds address space.");
    }

    if (image.size() < size) {
        throw std::invalid_argument("Rom::LoadRom provided image size too small.");
    }

    for (uint32_t i = 0; i < size; ++i) {
        rom_.insert_or_assign(base_addr + i, image.at(i));
    }
}

void Rom::Clear() {
    rom_.clear();
}

} // namespace brvc