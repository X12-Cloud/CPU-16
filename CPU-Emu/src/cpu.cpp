#include "cpu.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>

CPU::CPU(Memory* memory) : Mem(memory) {
    AX = BX = CX = DX = 0;
    SP = BP = SI = DI = 0;
    IP = 0;
    FLAGS = 0;
    Cycles = 0;
    
    Reset();
}

void CPU::Reset() {
    AX = BX = CX = DX = 0;
    SP = BP = SI = DI = 0;

    IP = 0x0000;

    FLAGS = 0;

    Cycles = 0;
}

void CPU::Execute(int cycles) {
    Cycles = cycles;

    while (Cycles > 0) {
        Byte opcode = Mem->ReadByte(IP);

        IP++;

        Cycles--;

        switch (static_cast<OpCode>(opcode)) {
            // --- Data Movement Instructions ---
            case OpCode::LDI_A_IMMED: {
                Word value = Mem->ReadWord(IP);
                AX = value;
                IP += 2;
                Cycles -= 2;
                break;
            }

            case OpCode::LDI_B_IMMED: {
                Word value = Mem->ReadWord(IP);
                BX = value;
                IP += 2;
                Cycles -= 2;
                break;
            }

            case OpCode::LDI_C_IMMED: {
                Word value = Mem->ReadWord(IP);
                CX = value;
                IP += 2;
                Cycles -= 2;
                break;
            }

            case OpCode::LDI_D_IMMED: {
                Word value = Mem->ReadWord(IP);
                DX = value;
                IP += 2;
                Cycles -= 2;
                break;
            }
	    
	    // --- Memory Access Instructions ---
            case OpCode::LDA_ABS: {
                Address addr = Mem->ReadWord(IP);
                AX = Mem->ReadWord(addr);
                IP += 2;
                Cycles -= 3;
                break;
            }

            case OpCode::STA_ABS: {
                Address addr = Mem->ReadWord(IP);
                Mem->WriteWord(addr, AX);
                IP += 2;
                Cycles -= 3;
                break;
            }

            // --- Arithmetic Instructions ---
            case OpCode::ADD_A_B: {
                AX = AX + BX;

                if (AX == 0x0000) {
                    SetFlag(Flag::ZF);
                } else {
                    ClearFlag(Flag::ZF);
                }

                Cycles -= 1;
                break;
            }

	        // --- Control Flow Instructions ---
            case OpCode::JMP_ABS: {
                Address jump_addr = Mem->ReadWord(IP);
                IP = jump_addr;
                Cycles -= 2;
                break;
            }

            case OpCode::JE_ABS: {
                Address jump_addr = Mem->ReadWord(IP);
                Cycles -= 2;
                if (IsFlagSet(Flag::ZF)) {
                    IP = jump_addr;
                } else {
                    IP += 2;
                }
                break;
            }

            case OpCode::JNE_ABS: {
                Address jump_addr = Mem->ReadWord(IP);
                Cycles -= 2;
                if (!IsFlagSet(Flag::ZF)) {
                    IP = jump_addr;
                } else {
                    IP += 2;
                }
                break;
            }

            case OpCode::HLT: {
                std::cout << "CPU Halted at address 0x" << std::hex << std::setw(4) << std::setfill('0') << (IP - 1) << std::endl;
                Cycles = 0; 
                break;
            }

            default: {
                std::cerr << "ERROR: Unknown Opcode 0x" << std::hex << static_cast<int>(opcode)
                          << " at address 0x" << std::hex << std::setw(4) << std::setfill('0') << (IP - 1) << std::endl;
                Cycles = 0;
                break;
            }
        }
    }
}

void CPU::SetFlag(Flag flag) {
        FLAGS |= static_cast<Word>(flag);
}

void CPU::ClearFlag(Flag flag) {
        FLAGS &= ~static_cast<Word>(flag);
}

bool CPU::IsFlagSet(Flag flag) const {
        return (FLAGS & static_cast<Word>(flag)) != 0;
}
