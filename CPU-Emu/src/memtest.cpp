#include "types.hpp"
#include "memory.hpp"
#include <iostream>
#include <vector>
#include <iomanip>

int main() {
	std::cout << "Starting 16-bit CPU emulator..." << std::endl;

	Memory mem;

    // --- Test: Byte Read/Write ---
    Address testAddressByte = 0x1000;
    Byte testValueByte = 0xA5;

    mem.WriteByte(testAddressByte, testValueByte);
    Byte readValueByte = mem.ReadByte(testAddressByte);

    std::cout << "\n--- Test: Byte Read/Write ---" << std::endl;
    std::cout << "  Wrote 0x" << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(testValueByte)
              << " to 0x" << std::hex << std::setw(4) << std::setfill('0') << testAddressByte << std::endl;
    std::cout << "  Read  0x" << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(readValueByte)
              << " from 0x" << std::hex << std::setw(4) << std::setfill('0') << testAddressByte << std::endl;
    if (testValueByte == readValueByte) { std::cout << "  PASSED!\n"; } else { std::cout << "  FAILED!\n"; }

    // --- Test: Word Read/Write ---
    Address testAddressWord = 0x2000;
    Word testValueWord = 0x1234;

    mem.WriteWord(testAddressWord, testValueWord);
    Word readValueWord = mem.ReadWord(testAddressWord);

    std::cout << "\n--- Test: Word Read/Write ---" << std::endl;
    std::cout << "  Wrote 0x" << std::hex << std::setw(4) << std::setfill('0') << testValueWord
              << " to 0x" << std::hex << std::setw(4) << std::setfill('0') << testAddressWord << std::endl;
    std::cout << "  Read  0x" << std::hex << std::setw(4) << std::setfill('0') << readValueWord
              << " from 0x" << std::hex << std::setw(4) << std::setfill('0') << testAddressWord << std::endl;
    if (testValueWord == readValueWord) { std::cout << "  PASSED!\n"; } else { std::cout << "  FAILED!\n"; }

    // --- Test: Word Endianness ---
    Byte lsb_expected = 0x34;
    Byte msb_expected = 0x12;
    Byte lsb_read = mem.ReadByte(testAddressWord);
    Byte msb_read = mem.ReadByte(testAddressWord + 1);

    std::cout << "\n--- Test: Word Endianness ---" << std::endl;
    std::cout << "  0x" << std::hex << std::setw(4) << std::setfill('0') << testValueWord << " (0x1234)" << std::endl;
    std::cout << "    Byte at 0x" << std::hex << std::setw(4) << std::setfill('0') << testAddressWord << ": 0x"
              << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(lsb_read) << " (Expected LSB: 0x" << static_cast<int>(lsb_expected) << ")" << std::endl;
    std::cout << "    Byte at 0x" << std::hex << std::setw(4) << std::setfill('0') << testAddressWord + 1 << ": 0x"
              << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(msb_read) << " (Expected MSB: 0x" << static_cast<int>(msb_expected) << ")" << std::endl;
    if (lsb_read == lsb_expected && msb_read == msb_expected) { std::cout << "  PASSED (Little-Endian)!\n"; } else { std::cout << "  FAILED!\n"; }

    // --- Test: Memory Reset ---
    std::cout << "\n--- Test: Memory Reset ---" << std::endl;
    mem.WriteByte(0x0000, 0xFF);
    std::cout << "  Byte at 0x0000 before reset: 0x" << std::hex << static_cast<int>(mem.ReadByte(0x0000)) << std::endl;
    mem.Reset();
    std::cout << "  Byte at 0x0000 after reset:  0x" << std::hex << static_cast<int>(mem.ReadByte(0x0000)) << std::endl;
    if (mem.ReadByte(0x0000) == 0x00) { std::cout << "  PASSED!\n"; } else { std::cout << "  FAILED!\n"; }


	return 0;
}
