#ifndef EMULATOR_MEMORY_HPP
#define EMULATOR_MEMORY_HPP

#include "types.hpp"
#include <vector>

class Memory {
public:
	static constexpr Dword MAX_MEM_SIZE = 1024 * 64;

	Memory() {
		Data.resize(MAX_MEM_SIZE, 0);
	}

	Byte ReadByte(Address address) const {
		if (address < MAX_MEM_SIZE) {
			return Data[address];
		}

		return 0;
	}

	void WriteByte(Address address, Byte value) {
		if (address < MAX_MEM_SIZE) {
			Data[address] = value;
		}
	}

	Word ReadWord(Address address) const {
            	if (static_cast<Dword>(address + 1) < MAX_MEM_SIZE) {
			return (static_cast<Word>(Data[address + 1]) << 8) | Data[address];
        	}
        	return 0;
    	}

	void WriteWord(Address address, Word value) {
		if (static_cast<Dword>(address + 1) < MAX_MEM_SIZE) {
			Data[address] = static_cast<Byte>(value & 0xFF);
        		Data[address + 1] = static_cast<Byte>((value >> 8) & 0xFF);
		}
	}
	
	void Reset() {
		std::fill(Data.begin(), Data.end(), 0);
	}

private:
	std::vector<Byte> Data;
};

#endif // EMULATOR_MEMORY_HPP

