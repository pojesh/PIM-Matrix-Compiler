#ifndef INSTRUCTION_GENERATOR_H
#define INSTRUCTION_GENERATOR_H

#include "parser.h"
#include "loop_analyzer.h"
#include "memory_mapper.h"
#include "../include/pim_isa.h"
#include <vector>

class InstructionGenerator {
public:
    InstructionGenerator(const std::vector<ThreeAddressInst>& code,
                         const std::vector<Loop>& loops,
                         MemoryMapper& memoryMapper);
    
    // Generate PIM ISA instructions
    std::vector<PimInstruction> generateInstructions();
    
private:
    // Input code and analysis
    const std::vector<ThreeAddressInst>& code;
    const std::vector<Loop>& loops;
    MemoryMapper& memoryMapper;
    
    // Maximum number of cores available
    const int maxCores = 8;
    
    // Generate instructions for a single three-address instruction
    std::vector<PimInstruction> generateForInstruction(const ThreeAddressInst& inst, int coreId);
    
    // Generate instructions for loading data
    std::vector<PimInstruction> generateLoadInstructions(const std::string& dest, const std::string& src, int coreId);
    
    // Generate instructions for storing data
    std::vector<PimInstruction> generateStoreInstructions(const std::string& dest, const std::string& src, int coreId);
    
    // Generate instructions for addition
    std::vector<PimInstruction> generateAddInstructions(const std::string& dest, const std::string& src1, const std::string& src2, int coreId);
    
    // Generate instructions for multiplication
    std::vector<PimInstruction> generateMultiplyInstructions(const std::string& dest, const std::string& src1, const std::string& src2, int coreId);
    
    // Generate instructions for moving data
    std::vector<PimInstruction> generateMoveInstructions(const std::string& dest, const std::string& src, int coreId);
    
    // Assign a core ID for a loop iteration
    int assignCoreId(int i, int j);
};

#endif // INSTRUCTION_GENERATOR_H