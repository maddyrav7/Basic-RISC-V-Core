#include "brvc_ram.h"

#include <iomanip>
#include <iostream>

#include "brvc_arch.h"
#include "brvc_utils.h"

// BRVC (Basic RISC-V Core) namespace
namespace brvc {

Ram::Ram(uint64_t size) {
    BRVC_ASSERT(size <= arch::kAddressSpaceSize, "Given size (0x%llx) exceeds address space (0x%llx).",
                size, arch::kAddressSpaceSize);
    BRVC_ASSERT_ALIGNED(size, arch::kArchWidthBytes);

    size_ = size;
}

uint8_t Ram::ReadByte(uint32_t addr) {
    BRVC_ASSERT(static_cast<uint64_t>(addr) < size_, "Given address (0x%llx) exceeds address space (0x%llx).",
                static_cast<uint64_t>(addr), size_);

    ram_.try_emplace(addr, uint8_t{0});
    return ram_.at(addr);
}

uint32_t Ram::ReadWord(uint32_t addr) {
    BRVC_ASSERT((static_cast<uint64_t>(addr) + static_cast<uint64_t>(arch::kWordBytes)) <= size_,
                 "Given word address (addr 0x%llx, word size 0x%llx) exceeds address space (0x%llx).",
                 static_cast<uint64_t>(addr), static_cast<uint64_t>(arch::kWordBytes), size_);
    BRVC_ASSERT_ALIGNED(addr, arch::kWordBytes);

    uint32_t word = 0;
    for (uint32_t i = 0; i < arch::kWordBytes; ++i) {
        // Little-endian.
        word |= (static_cast<uint32_t>(ReadByte(addr + i)) << (i * arch::kByteBits));
    }

    return word;
}

void Ram::WriteByte(uint32_t addr, uint8_t value) {
    BRVC_ASSERT(static_cast<uint64_t>(addr) < size_, "Given address (0x%llx) exceeds address space (0x%llx).",
                static_cast<uint64_t>(addr), size_);

    ram_.insert_or_assign(addr, value);
}

void Ram::WriteWord(uint32_t addr, uint32_t value) {
    BRVC_ASSERT((static_cast<uint64_t>(addr) + static_cast<uint64_t>(arch::kWordBytes)) <= size_,
                 "Given word address (addr 0x%llx, word size 0x%llx) exceeds address space (0x%llx).",
                 static_cast<uint64_t>(addr), static_cast<uint64_t>(arch::kWordBytes), size_);
    BRVC_ASSERT_ALIGNED(addr, arch::kWordBytes);

    for (uint32_t i = 0; i < arch::kWordBytes; ++i) {
        // Little-endian.
        WriteByte(addr + i, static_cast<uint8_t>((value >> (i * arch::kByteBits)) & arch::kByteBitMask));
    }
}

uint64_t Ram::GetSize() {
    return size_;
}

void Ram::LoadRam(uint32_t base_addr,
                  uint64_t size,
                  const std::vector<uint8_t>& image) {
    BRVC_ASSERT((static_cast<uint64_t>(base_addr) + size) <= static_cast<uint64_t>(size_),
                 "Given address (0x%llx) and size (0x%llx) exceed address space (0x%llx).",
                 static_cast<uint64_t>(base_addr), size, size_);

    BRVC_ASSERT(image.size() >= size, "Size of given image (0x%zx) too small for given load size (0x%llx).",
                image.size(), size);

    // TODO: This is inefficient and is very slow.
    // Change this to a more efficient (sparse) algorithm later.
    for (uint32_t i = 0; i < size; ++i) {
        ram_.insert_or_assign(base_addr + i, image.at(i));
    }
}

void Ram::Clear() {
    ram_.clear();
}

void Ram::PrintRam() const {
    constexpr int kColumnWidth = 15;

    // Title
    utils::PrintNewLine();
    utils::PrintSeparator();
    std::cout << "RAM Status\n";
    utils::PrintSeparator();

    // Header
    std::cout << std::left
              << std::setw(kColumnWidth) << "Address"
              << std::setw(kColumnWidth) << "Value"
              << '\n';

    // Separator
    utils::PrintSeparator();

    std::cout << std::uppercase << std::hex;

    // Addresses and Values
    for (const auto& [address, value] : ram_) {
        std::cout << std::left
                  << "0x" << std::setw(kColumnWidth - 2) << address
                  << "0x" << std::setw(kColumnWidth - 2) << static_cast<uint32_t>(value)
                  << '\n';
    }

    std::cout << std::dec;
    utils::PrintNewLine();
}

} // namespace brvc