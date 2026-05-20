#ifndef BRVC_UTILS_H
#define BRVC_UTILS_H

#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>

#define LOCATION_STRING __FILE__ + std::string(":") + std::to_string(__LINE__) + std::string(":") + __func__

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
    } while (false)

#define BRVC_ASSERT_ALIGNED(val, base)                            \
    BRVC_ASSERT((static_cast<uint64_t>((val)) % (base)) == 0,     \
    "Provided value (%llx) is not aligned to base (%llx).",       \
    static_cast<uint64_t>((val)), static_cast<uint64_t>((base)));

namespace brvc::utils {

static constexpr int kSeparatorLength = 30;
static constexpr char kSeparatorChar = '-';

inline void PrintSeparator(char sep = kSeparatorChar, int len = kSeparatorLength) {
    std::cout << std::string(kSeparatorLength, kSeparatorChar) << "\n";
}

inline void PrintNewLine() {
    std::cout << "\n";
}

} // namespace brvc::utils

#endif // BRVC_UTILS_H