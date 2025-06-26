# CPU-16: A Custom 16-bit Processor Emulator

## Project Overview

CPU-16 is a high-performance, custom-designed 16-bit processor emulator built in C++. This project serves as a robust platform for in-depth exploration of computer architecture, low-level system programming, and the intricacies of CPU design. It's engineered to be a foundational component for developing and testing complex processor logic and custom low-level software.

## Current Features (Version 0.1)

* **16-bit Custom Architecture:** Implements a unique 16-bit CPU design from the ground up.
* **Comprehensive Register Set:** Features 16-bit general-purpose registers (AX, BX, CX, DX), a Stack Pointer (SP), Base Pointer (BP), Instruction Pointer (IP), and a FLAGS register for detailed status and condition codes.
* **Memory Management:** Emulates a 64KB (0x0000 - 0xFFFF) addressable memory space, providing substantial capacity for programs and data.
* **Optimized Instruction Set:** Supports a foundational set of powerful instructions, including:
    * **Data Movement:** Load Immediate (LDI_A_IMMED, etc.), Register-to-Register Move (MOV_A_B, etc.).
    * **Arithmetic Operations:** Add (ADD_A_B, etc.), Subtract (SUB_A_B, etc.).
    * **Control Flow:** Unconditional Jump (JMP_ABS, JMP_REL), Conditional Jumps (JE_ABS, JNE_ABS, etc.), Call, Return.
    * **System Control:** Halt (HLT) for program termination.
* **Built-in Test Program:** Includes a pre-programmed test sequence to demonstrate core CPU functionality like register manipulation, arithmetic, and conditional/unconditional jumps.
* **Deep Inspectability:** Designed for easy internal state monitoring, allowing detailed inspection of registers and memory during execution.

## Roadmap: Planned Core Enhancements

Our vision for CPU-16 is to continuously expand its capabilities and utility. Key enhancements on the immediate roadmap include:

* **Dedicated Two-Pass Assembler:** Development of a robust, standalone C++ assembler to translate human-readable assembly code into the CPU-16's machine code format. This will streamline software development for the processor.
* **Dynamic Program Loading:** Implement a flexible mechanism to load external programs into the emulator's memory at runtime.
* **Instruction Set Expansion:**
    * Introduction of more advanced arithmetic and logical operations (e.g., AND, OR, XOR, NOT, SHIFT, multiply, divide).
    * Comprehensive stack manipulation instructions (PUSH, POP).
    * More flexible memory addressing modes for complex data structures.
    * Fundamental Input/Output (I/O) instructions for external interaction.
* **Advanced Debugging Capabilities:**
    * Implementation of advanced breakpoint management.
    * Precise single-stepping control over instruction execution.
    * Sophisticated memory and register inspection tools.
* **Basic Peripheral Emulation:** Simulate essential I/O devices (e.g., character display, keyboard input) to enable more interactive programs.

## Future Vision: Architectural Evolution

Looking further ahead, CPU-16 is designed for significant architectural evolution. Our long-term goals involve:

* **Advanced Processor Features:** Integration of sophisticated architectural elements for enhanced performance and capability.
* **Performance Optimization Techniques:** Exploration and implementation of CPU performance optimizations, such as pipelining and cache mechanisms.
* **Robust System Interfacing:** Development of a comprehensive interrupt handling system for asynchronous event management.
* **Complex Software Environment:** Laying the groundwork for supporting and executing more intricate software, potentially leading to the development of a custom operating system.

## Getting Started

To compile and run the CPU-16 emulator:

1.  **Clone this repository:**
    ```bash
    git clone [https://github.com/X12-Cloud/CPU-16.git](https://github.com/X12-Cloud/CPU-16.git)
    cd CPU-16
    ```
2.  **Compile the Emulator:**
    Navigate to the `CPU-Emu` directory and use `g++` to compile all source files:
    ```bash
    cd CPU-Emu/
    g++ src/main.cpp src/cpu.cpp src/memory.cpp -o cpu_emu -std=c++17 -Wall -Wextra
    cd .. # Go back to the CPU-16 root directory
    ```
3.  **Run the Emulator:**
    Execute the compiled emulator. It will run its internal, hardcoded test program:
    ```bash
    ./CPU-Emu/cpu_emu
    ```

## Contribution

Contributions are highly valued! If you're passionate about low-level systems, C++ engineering, or processor design, feel free to fork this repository, implement your enhancements, and submit a pull request.

## License

This project is licensed under the MIT License - see the `LICENSE` file for details.
