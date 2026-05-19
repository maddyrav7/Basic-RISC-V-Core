#ifndef BRVC_ARCH_H
#define BRVC_ARCH_H

#include <cstdint>

// BRVC (Basic RISC-V Core) namespace
namespace brvc::arch {
    static constexpr uint64_t kArchWidthBits = 32;
    static constexpr uint32_t kArchWidthBytes = 4;
    static constexpr uint64_t kAddressSpaceSize = 1ULL << kArchWidthBits;
    static constexpr uint32_t kWordBytes = 4;
    static constexpr uint32_t kByteBits = 8;
    static constexpr uint8_t  kByteBitMask = 0xF;
} // namespace brvc::arch

#endif // BRVC_ARCH_H
