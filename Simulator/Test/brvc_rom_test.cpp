#include "brvc_rom_test.h"

#include <limits>
#include <unordered_map>

#include "brvc_test.h"
#include "../brvc_arch.h"
#include "../brvc_rom.h"

namespace brvc::test {

namespace {

void ConstructCorrectSize() {
    brvc::Rom rom(arch::kRomSizeBytes);

    BRVC_TEST_ASSERT_EQ(rom.GetSize(), arch::kRomSizeBytes);
}

void DefaultReadByteZero() {
    brvc::Rom rom(arch::kRomSizeBytes);

    // First
    BRVC_TEST_ASSERT_EQ(rom.ReadByte(0x0000), 0x00000000);
    // Middle
    BRVC_TEST_ASSERT_EQ(rom.ReadByte(arch::kRomSizeBytes / 2), 0x00000000);
    // Last
    BRVC_TEST_ASSERT_EQ(rom.ReadByte(arch::kRomSizeBytes - 1), 0x00000000);
}

void LoadPartialRomReadsBackCorrectBytes() {
    brvc::Rom rom(arch::kRomSizeBytes);

    std::unordered_map<uint32_t, uint8_t> image = {
        {0x0000, 0x11111111},
        {0x1111, 0x22222222},
        {0x2222, 0x33333333},
        {0x3333, 0x44444444},
        {0x4444, 0x55555555},
        {0x5555, 0x66666666},
        {0x6666, 0x77777777},
        {0x7777, 0x88888888},
        {0xabcd, 0xbeadbed0},
        {0xffff, 0x00000000}
    };

    rom.LoadRom(image);

    for (const auto& [address, value] : image) {
        BRVC_TEST_ASSERT_EQ(rom.ReadByte(address), value);
    }
}

void LoadFullRomReadsBackCorrectBytes() {
    brvc::Rom rom(arch::kRomSizeBytes);

    std::unordered_map<uint32_t, uint8_t> image;

    for (uint32_t address = 0; address < arch::kRomSizeBytes; ++address) {
        image.insert_or_assign(address, address);
    }

    rom.LoadRom(image);

    for (const auto& [address, value] : image) {
        BRVC_TEST_ASSERT_EQ(rom.ReadByte(address), value);
    }
}

} // namespace

void AddRomTestSuite() {
    BrvcTestSuite suite("ROM");

    BRVC_ADD_TEST(suite, ConstructCorrectSize);
    BRVC_ADD_TEST(suite, DefaultReadByteZero);
    BRVC_ADD_TEST(suite, LoadPartialRomReadsBackCorrectBytes);
    BRVC_ADD_TEST(suite, LoadFullRomReadsBackCorrectBytes);
}

} // namespace brvc::test