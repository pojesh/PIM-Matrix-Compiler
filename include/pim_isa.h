#ifndef PIM_ISA_H
#define PIM_ISA_H

#include <cstdint>
#include <string>

// Opcodes as defined in the paper
enum class Opcode : uint8_t {
    NOP         = 0x0,
    LOAD        = 0x1,  // Load data from DRAM row
    STORE       = 0x2,  // Store data to DRAM row
    PROGRAM_LUT = 0x3,  // Program a LUT for computation
    COMPUTE     = 0x4,  // Execute computation using programmed LUT
    MOVE        = 0x5,  // Move data between cores
    SYNC        = 0xF   // Synchronization instruction
};

// Instruction format based on Section IV-D
struct PimInstruction {
    Opcode opcode;       // 4-bit opcode
    uint8_t core_id;     // Core pointer/ID (4-bit)
    uint16_t row_addr;   // Memory row address (16-bit)
    uint8_t flags;       // Additional control flags (8-bit)
    
    // Convert instruction to binary representation
    uint32_t toBinary() const {
        uint32_t binary = 0;
        binary |= (static_cast<uint32_t>(opcode) & 0xF);
        binary |= ((static_cast<uint32_t>(core_id) & 0xF) << 4);
        binary |= ((static_cast<uint32_t>(row_addr) & 0xFFFF) << 8);
        binary |= ((static_cast<uint32_t>(flags) & 0xFF) << 24);
        return binary;
    }
    
    // Convert instruction to human-readable format
    std::string toString() const {
        std::string result;
        switch(opcode) {
            case Opcode::NOP: result = "NOP"; break;
            case Opcode::LOAD: result = "LOAD"; break;
            case Opcode::STORE: result = "STORE"; break;
            case Opcode::PROGRAM_LUT: result = "PROGRAM_LUT"; break;
            case Opcode::COMPUTE: result = "COMPUTE"; break;
            case Opcode::MOVE: result = "MOVE"; break;
            case Opcode::SYNC: result = "SYNC"; break;
            default: result = "UNKNOWN"; break;
        }
        
        result += " core=" + std::to_string(core_id);
        result += " row=" + std::to_string(row_addr);
        result += " flags=0x" + std::to_string(flags);
        
        return result;
    }
};

// Flag definitions
namespace Flags {
    constexpr uint8_t READ = 0x01;
    constexpr uint8_t WRITE = 0x02;
    constexpr uint8_t ACCUMULATE = 0x04;
    constexpr uint8_t PARALLEL = 0x08;
    constexpr uint8_t RESET = 0x10;
}

#endif // PIM_ISA_H