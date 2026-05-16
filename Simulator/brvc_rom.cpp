#include "brvc_rom.h"
#include "brvc_arch.h"

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

void Rom::LoadRom(uint32_t base_addr,
                  uint64_t size,
                  const std::vector<uint8_t>& image) {
    BRVC_ASSERT((static_cast<uint64_t>(base_addr) + size) <= static_cast<uint64_t>(size_),
                 "Given address (%llx) and size (%llx) exceed address space (%llx).",
                 static_cast<uint64_t>(base_addr), size, size_);

    BRVC_ASSERT(image.size() >= size, "Size of given image (%llx) too small for given load size (%llx).",
                image.size(), size);

    // TODO: This is inefficient and will become very slow as the ROM size increases.
    // Change this to a more efficient (sparse) algorithm later.
    for (uint32_t i = 0; i < size; ++i) {
        rom_.insert_or_assign(base_addr + i, image.at(i));
    }
}

void Rom::Clear() {
    rom_.clear();
}

} // namespace brvc