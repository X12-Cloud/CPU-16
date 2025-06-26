#include "types.hpp"
#include "memory.hpp"
#include "cpu.hpp"
#include <iostream>
#include <iomanip>

// Helper to print CPU state for debugging
void printCpuState(const CPU& cpu, const std::string& title) {
    std::cout << "\n--- " << title << " ---" << std::endl;
    std::cout << "  AX: 0x" << std::hex << std::setw(4) << std::setfill('0') << cpu.GetAX() << std::endl;
    std::cout << "  BX: 0x" << std::hex << std::setw(4) << std::setfill('0') << cpu.GetBX() << std::endl;
    std::cout << "  CX: 0x" << std::hex << std::setw(4) << std::setfill('0') << cpu.GetCX() << std::endl;
    std::cout << "  DX: 0x" << std::hex << std::setw(4) << std::setfill('0') << cpu.GetDX() << std::endl;
    std::cout << "  IP: 0x" << std::hex << std::setw(4) << std::setfill('0') << cpu.GetIP() << std::endl;
    std::cout << "  FLAGS: 0x" << std::hex << std::setw(4) << std::setfill('0') << cpu.GetFLAGS();
    std::cout << " (ZF: " << (cpu.IsFlagSet(Flag::ZF) ? "1" : "0") << ")" << std::endl;
    std::cout << "  Cycles remaining: " << std::dec << cpu.GetCycles() << std::endl;
}

int main() {
    std::cout << "Starting 16-bit CPU emulator (Jump & Flag Test)..." << std::endl;

    Memory mem;
    CPU cpu(&mem);
    cpu.Reset();

    printCpuState(cpu, "CPU Initial State After Reset");

    // --- Memory Initial State ---
    const Address DATA_ADDR_1 = 0x1000;
    const Address DATA_ADDR_2 = 0x1002;
    mem.WriteWord(DATA_ADDR_1, 0xAA55);
    mem.WriteWord(DATA_ADDR_2, 0xBB66);

    std::cout << "\n--- Memory Initial State ---" << std::endl;
    std::cout << "  Memory at 0x" << std::hex << std::setw(4) << std::setfill('0') << DATA_ADDR_1
              << ": 0x" << std::setw(4) << std::setfill('0') << mem.ReadWord(DATA_ADDR_1) << std::endl;
    std::cout << "  Memory at 0x" << std::hex << std::setw(4) << std::setfill('0') << DATA_ADDR_2
              << ": 0x" << std::setw(4) << std::setfill('0') << mem.ReadWord(DATA_ADDR_2) << std::endl;

    std::cout << "\n--- Program Loading ---" << std::endl;

    Address current_addr = 0x0000;

    mem.WriteByte(current_addr++, static_cast<Byte>(OpCode::LDI_A_IMMED)); mem.WriteWord(current_addr, 0x000A);
    std::cout << "  [0x" << std::hex << std::setw(4) << std::setfill('0') << (current_addr - 1) << "] LDI_A_IMMED 0x000A" << std::endl; current_addr += 2; // IP = 0x0003

    mem.WriteByte(current_addr++, static_cast<Byte>(OpCode::LDI_B_IMMED)); mem.WriteWord(current_addr, 0x0005);
    std::cout << "  [0x" << std::hex << std::setw(4) << std::setfill('0') << (current_addr - 1) << "] LDI_B_IMMED 0x0005" << std::endl; current_addr += 2; // IP = 0x0006

    mem.WriteByte(current_addr++, static_cast<Byte>(OpCode::ADD_A_B));
    std::cout << "  [0x" << std::hex << std::setw(4) << std::setfill('0') << (current_addr - 1) << "] ADD_A_B (AX=0x000F, ZF clear)" << std::endl; // IP = 0x0007

    const Address JNE_SKIP_ADDR = 0x0020;
    mem.WriteByte(current_addr++, static_cast<Byte>(OpCode::JNE_ABS)); mem.WriteWord(current_addr, JNE_SKIP_ADDR);
    std::cout << "  [0x" << std::hex << std::setw(4) << std::setfill('0') << (current_addr - 1) << "] JNE_ABS 0x" << std::hex << std::setw(4) << std::setfill('0') << JNE_SKIP_ADDR << " (ZF clear, SHOULD JUMP)" << std::endl;
    current_addr += 2;

    mem.WriteByte(current_addr++, static_cast<Byte>(OpCode::LDI_A_IMMED)); mem.WriteWord(current_addr, 0xDEAD);
    std::cout << "  [0x" << std::hex << std::setw(4) << std::setfill('0') << (current_addr - 1) << "] LDI_A_IMMED 0xDEAD (SHOULD BE SKIPPED)" << std::endl;
    current_addr += 2;

    const Address JUMP_TO_ZERO_TEST = 0x0010;
    mem.WriteByte(current_addr++, static_cast<Byte>(OpCode::JMP_ABS)); mem.WriteWord(current_addr, JUMP_TO_ZERO_TEST);
    std::cout << "  [0x" << std::hex << std::setw(4) << std::setfill('0') << (current_addr - 1) << "] JMP_ABS 0x" << std::hex << std::setw(4) << std::setfill('0') << JUMP_TO_ZERO_TEST << " (unconditional jump)" << std::endl;
    current_addr += 2;

    mem.WriteByte(current_addr++, static_cast<Byte>(OpCode::LDI_A_IMMED)); mem.WriteWord(current_addr, 0xBEEF);
    std::cout << "  [0x" << std::hex << std::setw(4) << std::setfill('0') << (current_addr - 1) << "] LDI_A_IMMED 0xBEEF (SHOULD BE SKIPPED by JMP)" << std::endl;
    current_addr += 2;


    current_addr = JUMP_TO_ZERO_TEST;

    mem.WriteByte(current_addr++, static_cast<Byte>(OpCode::LDI_A_IMMED)); mem.WriteWord(current_addr, 0x000F);
    std::cout << "  [0x" << std::hex << std::setw(4) << std::setfill('0') << (current_addr - 1) << "] LDI_A_IMMED 0x000F" << std::endl; current_addr += 2; // IP = 0x0013

    mem.WriteByte(current_addr++, static_cast<Byte>(OpCode::LDI_B_IMMED)); mem.WriteWord(current_addr, 0xFFF1);
    std::cout << "  [0x" << std::hex << std::setw(4) << std::setfill('0') << (current_addr - 1) << "] LDI_B_IMMED 0xFFF1" << std::endl; current_addr += 2; // IP = 0x0016

    mem.WriteByte(current_addr++, static_cast<Byte>(OpCode::ADD_A_B));
    std::cout << "  [0x" << std::hex << std::setw(4) << std::setfill('0') << (current_addr - 1) << "] ADD_A_B (AX=0x0000, ZF set)" << std::endl; // IP = 0x0017

    const Address JUMP_TAKEN_ADDR = 0x0020;
    mem.WriteByte(current_addr++, static_cast<Byte>(OpCode::JE_ABS)); mem.WriteWord(current_addr, JUMP_TAKEN_ADDR);
    std::cout << "  [0x" << std::hex << std::setw(4) << std::setfill('0') << (current_addr - 1) << "] JE_ABS 0x" << std::hex << std::setw(4) << std::setfill('0') << JUMP_TAKEN_ADDR << " (ZF set, SHOULD JUMP)" << std::endl;
    current_addr += 2;

    mem.WriteByte(current_addr++, static_cast<Byte>(OpCode::HLT));
    std::cout << "  [0x" << std::hex << std::setw(4) << std::setfill('0') << (current_addr - 1) << "] HLT (SHOULD BE SKIPPED by JE)" << std::endl; // IP = 0x001B

    current_addr = JUMP_TAKEN_ADDR; // Reset current_addr to this label

    mem.WriteByte(current_addr++, static_cast<Byte>(OpCode::LDI_A_IMMED)); mem.WriteWord(current_addr, 0xC0DE);
    std::cout << "  [0x" << std::hex << std::setw(4) << std::setfill('0') << (current_addr - 1) << "] LDI_A_IMMED 0xC0DE (Jump Target)" << std::endl; current_addr += 2; // IP = 0x0023

    mem.WriteByte(current_addr++, static_cast<Byte>(OpCode::HLT));
    std::cout << "  [0x" << std::hex << std::setw(4) << std::setfill('0') << (current_addr - 1) << "] HLT (Final Halt)" << std::endl; // IP = 0x0024


    // --- CPU Execution ---
    std::cout << "\n--- CPU Execution ---" << std::endl;
    cpu.Execute(50);


    // --- Post-Execution CPU State ---
    printCpuState(cpu, "Post-Execution CPU State");

    // --- Memory Post-Execution State ---
    std::cout << "\n--- Memory Post-Execution State ---" << std::endl;
    std::cout << "  Memory at 0x" << std::hex << std::setw(4) << std::setfill('0') << DATA_ADDR_1
              << ": 0x" << std::setw(4) << std::setfill('0') << mem.ReadWord(DATA_ADDR_1) << std::endl;
    std::cout << "  Memory at 0x" << std::hex << std::setw(4) << std::setfill('0') << DATA_ADDR_2
              << ": 0x" << std::setw(4) << std::setfill('0') << mem.ReadWord(DATA_ADDR_2) << std::endl;


    return 0;
}
