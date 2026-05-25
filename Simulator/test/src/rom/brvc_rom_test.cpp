#include "brvc_rom_test.h"

#include <limits>
#include <unordered_map>

#include "brvc_test.h"
#include "brvc_arch.h"
#include "brvc_rom.h"

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
        {static_cast<uint32_t>(0x00000000UL), static_cast<uint8_t>(0x11)},
        {static_cast<uint32_t>(0x00001111UL), static_cast<uint8_t>(0x22)},
        {static_cast<uint32_t>(0x00002222UL), static_cast<uint8_t>(0x33)},
        {static_cast<uint32_t>(0x00003333UL), static_cast<uint8_t>(0x44)},
        {static_cast<uint32_t>(0x00004444UL), static_cast<uint8_t>(0x55)},
        {static_cast<uint32_t>(0x00005555UL), static_cast<uint8_t>(0x66)},
        {static_cast<uint32_t>(0x00006666UL), static_cast<uint8_t>(0x77)},
        {static_cast<uint32_t>(0x00007777UL), static_cast<uint8_t>(0x88)},
        {static_cast<uint32_t>(0x0000ABCDUL), static_cast<uint8_t>(0xBE)},
        {static_cast<uint32_t>(0x0000FFFFUL), static_cast<uint8_t>(0x00)}
    };

    rom.LoadRom(image);

    for (const auto& [address, value] : image) {
        BRVC_TEST_ASSERT_EQ(rom.ReadByte(address), value);
    }
    rom.PrintRom();
}

void LoadFullRomReadsBackCorrectBytes() {
    brvc::Rom rom(arch::kRomSizeBytes);

    std::unordered_map<uint32_t, uint8_t> image;

    for (uint32_t address = 0; address < arch::kRomSizeBytes; ++address) {
        image.insert_or_assign(address, static_cast<uint8_t>(address % (1 << arch::kByteBits)));
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

    AddTestSuite(suite);
}

} // namespace brvc::test