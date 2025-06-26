#ifndef EMULATOR_TYPES_HPP
#define EMULATOR_TYPES_HPP

#include <cstdint>

using Byte = uint8_t;
using Word = uint16_t;
using Address = uint16_t;
using Dword = uint32_t;

enum class OpCode : Byte {
    // Data Movement Instructions
    LDI_A_IMMED = 0x01,
    LDI_B_IMMED = 0x02,
    LDI_C_IMMED = 0x03,
    LDI_D_IMMED = 0x04,

    // Memory Access Instructions
    LDA_ABS = 0x05,
    STA_ABS = 0x06,
    
    // Arithmetic Instructions
    ADD_A_B = 0x10,

    // Control Flow / System Instructions
    JMP_ABS = 0x20,
    JE_ABS = 0x21,
    JNE_ABS = 0x22,
	
    HLT = 0xFF
};

enum class Flag : Byte {
        ZF = (1 << 6)
};

#endif // EMULATOR_TYPES_HPP
