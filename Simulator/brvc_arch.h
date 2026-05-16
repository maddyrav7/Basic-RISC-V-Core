#ifndef BRVC_ARCH_H
#define BRVC_ARCH_H

#include <cstdint>
#include <cstdlib>
#include <iostream>

#define BRVC_ASSERT(condition, format, ...)                \
    do {                                                   \
        if (!(condition)) {                                \
            std::fprintf(stderr, "%s:%s:%s: ",             \
                         __FILE__, __LINE__, __func__);    \
            std::fprintf(stderr, (format), ##__VA_ARGS__); \
            std::fprintf(stderr, "\n");                    \
            std::fflush(stderr);                           \
            std::abort();                                  \
        }                                                  \
    } while(false)

#define BRVC_ASSERT_ALIGNED(val, base)                            \
    BRVC_ASSERT(0 == (static_cast<uint64_t>((val)) % (base)),     \
    "Provided value (%llx) is not aligned to base (%llx).",       \
    static_cast<uint64_t>((val)), static_cast<uint64_t>((base)));

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
