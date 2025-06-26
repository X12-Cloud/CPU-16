#ifndef EMULATOR_CPU_HPP
#define EMULATOR_CPU_HPP

#include "types.hpp"
#include "memory.hpp"

class CPU {
public:
    CPU(Memory* memory);
    void Reset();
    void Execute(int cycles);

    void SetFlag(Flag flag);
    void ClearFlag(Flag flag);
    bool IsFlagSet(Flag flag) const;

    Word GetAX() const { return AX; }
    Word GetBX() const { return BX; }
    Word GetCX() const { return CX; }
    Word GetDX() const { return DX; }
    Word GetSP() const { return SP; }
    Word GetBP() const { return BP; }
    Word GetSI() const { return SI; }
    Word GetDI() const { return DI; }
    Address GetIP() const { return IP; }
    Word GetFLAGS() const { return FLAGS; }
    int GetCycles() const { return Cycles; }

private:
    Memory* Mem;

    //Registers
    Word AX, BX, CX, DX;

    Word SP;
    Word BP;
    Word SI;
    Word DI;

    Address IP;

    Word FLAGS;
    int Cycles;
};

#endif // EMULATOR_CPU_HPP
