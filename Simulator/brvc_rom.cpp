#include "brvc_rom.h"

#include <iomanip>
#include <iostream>

#include "brvc_arch.h"
#include "brvc_utils.h"

// BRVC (Basic RISC-V Core) namespace
namespace brvc {

Rom::Rom(uint64_t size) {
    BRVC_ASSERT(size <= arch::kAddressSpaceSize, "Given size (%llx) exceeds address space (%llx).",
                size, arch::kAddressSpaceSize);
    BRVC_ASSERT_ALIGNED(size, arch::kArchWidthBytes);

    size_ = size;
}

uint8_t Rom::ReadByte(uint32_t addr) {
    BRVC_ASSERT(static_cast<uint64_t>(addr) < size_, "Given address (%llx) exceeds address space (%llx).",
                static_cast<uint64_t>(addr), size_);

    rom_.try_emplace(addr, uint8_t{0});
    return rom_.at(addr);
}

uint32_t Rom::ReadWord(uint32_t addr) {
    BRVC_ASSERT((static_cast<uint64_t>(addr) + static_cast<uint64_t>(arch::kWordBytes)) <= size_,
                 "Given word address (addr %llx, word size %llx) exceeds address space (%llx).",
                 static_cast<uint64_t>(addr), static_cast<uint64_t>(arch::kWordBytes), size_);
    BRVC_ASSERT_ALIGNED(addr, arch::kWordBytes);

    uint32_t word = 0;
    for (uint32_t i = 0; i < arch::kWordBytes; ++i) {
        // Little-endian.
        word |= (static_cast<uint32_t>(ReadByte(addr + i)) << (i * arch::kByteBits));
    }
}

uint64_t Rom::GetSize() {
    return size_;
}

void Rom::LoadRom(const std::unordered_map<uint32_t, uint8_t>& image) {
    for (const auto& [address, value] : image) {
        BRVC_ASSERT(static_cast<uint64_t>(address) < size_,
                    "Address given in image (%llx) exceeds address space (%llx).",
                    static_cast<uint64_t>(address), size_);
        rom_.insert_or_assign(address, value);
    }
}

void Rom::Clear() {
    rom_.clear();
}

void Rom::PrintRom() const {
    constexpr int kColumnWidth = 15;

    // Header
    std::cout << std::left
              << std::setw(kColumnWidth) << "Address"
              << std::setw(kColumnWidth) << "Value"
              << '\n';

    utils::PrintSeparator();

    std::cout << std::uppercase << std::hex << std::showbase;

    // Addresses and Values
    for (const auto& [address, value] : rom_) {
        std::cout << std::left
                  << std::setw(kColumnWidth) << address
                  << std::setw(kColumnWidth) << value
                  << '\n';
    }
}

} // namespace brvc