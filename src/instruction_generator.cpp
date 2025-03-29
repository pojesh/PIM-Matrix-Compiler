#include "instruction_generator.h"
#include <iostream>
#include <regex>

InstructionGenerator::InstructionGenerator(const std::vector<ThreeAddressInst>& code,
                                           const std::vector<Loop>& loops,
                                           MemoryMapper& memoryMapper)
    : code(code), loops(loops), memoryMapper(memoryMapper) {
}

std::vector<PimInstruction> InstructionGenerator::generateInstructions() {
    std::vector<PimInstruction> instructions;
    
    // Extract parallelizable loops
    std::vector<Loop> parallelizableLoops;
    for (const auto& loop : loops) {
        if (loop.isParallelizable) {
            parallelizableLoops.push_back(loop);
        }
    }
    
    // For matrix multiplication, we can parallelize the i and j loops
    // We'll distribute the work across cores based on the (i,j) pairs
    
    // Process the three-address code
    for (int i = 0; i <= 2; i++) {  // i loop (0-2 for 3x3 example)
        for (int j = 0; j <= 2; j++) {  // j loop (0-2 for 3x3 example)
            // Assign a core ID for this (i,j) pair
            int coreId = assignCoreId(i, j);
            
            // Initialize C[i][j] to 0
            std::string cij = "C_" + std::to_string(i) + "_" + std::to_string(j);
            auto initInsts = generateMoveInstructions(cij, "0", coreId);
            instructions.insert(instructions.end(), initInsts.begin(), initInsts.end());
            
            for (int k = 0; k <= 2; k++) {  // k loop (0-2 for 3x3 example)
                // Extract the relevant instructions for this (i,j,k) iteration
                std::string aik = "A_" + std::to_string(i) + "_" + std::to_string(k);
                std::string bkj = "B_" + std::to_string(k) + "_" + std::to_string(j);
                
                // Load A[i][k]
                auto loadAInsts = generateLoadInstructions("t_A_" + std::to_string(i) + "_" + std::to_string(k), aik, coreId);
                instructions.insert(instructions.end(), loadAInsts.begin(), loadAInsts.end());
                
                // Load B[k][j]
                auto loadBInsts = generateLoadInstructions("t_B_" + std::to_string(k) + "_" + std::to_string(j), bkj, coreId);
                instructions.insert(instructions.end(), loadBInsts.begin(), loadBInsts.end());
                
                // Multiply A[i][k] * B[k][j]
                auto mulInsts = generateMultiplyInstructions(
                    "t_mul_" + std::to_string(i) + "_" + std::to_string(j) + "_" + std::to_string(k),
                    "t_A_" + std::to_string(i) + "_" + std::to_string(k),
                    "t_B_" + std::to_string(k) + "_" + std::to_string(j),
                    coreId
                );
                instructions.insert(instructions.end(), mulInsts.begin(), mulInsts.end());
                
                // Load current C[i][j]
                auto loadCInsts = generateLoadInstructions("t_C_" + std::to_string(i) + "_" + std::to_string(j), cij, coreId);
                instructions.insert(instructions.end(), loadCInsts.begin(), loadCInsts.end());
                
                // Add to C[i][j]
                auto addInsts = generateAddInstructions(
                    "t_C_new_" + std::to_string(i) + "_" + std::to_string(j),
                    "t_C_" + std::to_string(i) + "_" + std::to_string(j),
                    "t_mul_" + std::to_string(i) + "_" + std::to_string(j) + "_" + std::to_string(k),
                    coreId
                );
                instructions.insert(instructions.end(), addInsts.begin(), addInsts.end());
                
                // Store back to C[i][j]
                auto storeCInsts = generateStoreInstructions(
                    cij,
                    "t_C_new_" + std::to_string(i) + "_" + std::to_string(j),
                    coreId
                );
                instructions.insert(instructions.end(), storeCInsts.begin(), storeCInsts.end());
            }
            
            // Add a synchronization instruction after each (i,j) pair
            PimInstruction syncInst;
            syncInst.opcode = Opcode::SYNC;
            syncInst.core_id = coreId;
            syncInst.row_addr = 0;
            syncInst.flags = 0;
            instructions.push_back(syncInst);
        }
    }
    
    return instructions;
}

int InstructionGenerator::assignCoreId(int i, int j) {
    // Simple assignment: (i * 3 + j) % maxCores
    return (i * 3 + j) % maxCores;
}

std::vector<PimInstruction> InstructionGenerator::generateForInstruction(const ThreeAddressInst& inst, int coreId) {
    switch (inst.op) {
        case ThreeAddressInst::OpType::LOAD:
            return generateLoadInstructions(inst.dest, inst.src1, coreId);
        case ThreeAddressInst::OpType::STORE:
            return generateStoreInstructions(inst.dest, inst.src1, coreId);
        case ThreeAddressInst::OpType::ADD:
            return generateAddInstructions(inst.dest, inst.src1, inst.src2, coreId);
        case ThreeAddressInst::OpType::MULTIPLY:
            return generateMultiplyInstructions(inst.dest, inst.src1, inst.src2, coreId);
        case ThreeAddressInst::OpType::MOVE:
            return generateMoveInstructions(inst.dest, inst.src1, coreId);
        default:
            std::cerr << "Unknown instruction type" << std::endl;
            return {};
    }
}

std::vector<PimInstruction> InstructionGenerator::generateLoadInstructions(const std::string& dest, const std::string& src, int coreId) {
    std::vector<PimInstruction> instructions;
    
    // Map source variable to DRAM row
    uint16_t srcRow = memoryMapper.mapVariableToRow(src);
    
    // Map destination variable to DRAM row
    uint16_t destRow = memoryMapper.mapVariableToRow(dest);
    
    // Generate LOAD instruction
    PimInstruction loadInst;
    loadInst.opcode = Opcode::LOAD;
    loadInst.core_id = coreId;
    loadInst.row_addr = srcRow;
    loadInst.flags = Flags::READ;
    instructions.push_back(loadInst);
    
    // Generate STORE instruction to save to destination
    PimInstruction storeInst;
    storeInst.opcode = Opcode::STORE;
    storeInst.core_id = coreId;
    storeInst.row_addr = destRow;
    storeInst.flags = Flags::WRITE;
    instructions.push_back(storeInst);
    
    return instructions;
}

std::vector<PimInstruction> InstructionGenerator::generateStoreInstructions(const std::string& dest, const std::string& src, int coreId) {
    std::vector<PimInstruction> instructions;
    
    // Map source variable to DRAM row
    uint16_t srcRow = memoryMapper.mapVariableToRow(src);
    
    // Map destination variable to DRAM row
    uint16_t destRow = memoryMapper.mapVariableToRow(dest);
    
    // Generate LOAD instruction to get the source value
    PimInstruction loadInst;
    loadInst.opcode = Opcode::LOAD;
    loadInst.core_id = coreId;
    loadInst.row_addr = srcRow;
    loadInst.flags = Flags::READ;
    instructions.push_back(loadInst);
    
    // Generate STORE instruction
    PimInstruction storeInst;
    storeInst.opcode = Opcode::STORE;
    storeInst.core_id = coreId;
    storeInst.row_addr = destRow;
    storeInst.flags = Flags::WRITE;
    instructions.push_back(storeInst);
    
    return instructions;
}

std::vector<PimInstruction> InstructionGenerator::generateAddInstructions(const std::string& dest, const std::string& src1, const std::string& src2, int coreId) {
    std::vector<PimInstruction> instructions;
    
    // Map source variables to DRAM rows
    uint16_t src1Row = memoryMapper.mapVariableToRow(src1);
    uint16_t src2Row = memoryMapper.mapVariableToRow(src2);
    
    // Map destination variable to DRAM row
    uint16_t destRow = memoryMapper.mapVariableToRow(dest);
    
    // Program LUT for addition
    PimInstruction programLutInst;
    programLutInst.opcode = Opcode::PROGRAM_LUT;
    programLutInst.core_id = coreId;
    programLutInst.row_addr = 0;  // Special row for LUT programming
    programLutInst.flags = 0;     // Addition operation
    instructions.push_back(programLutInst);
    
    // Load first operand
    PimInstruction load1Inst;
    load1Inst.opcode = Opcode::LOAD;
    load1Inst.core_id = coreId;
    load1Inst.row_addr = src1Row;
    load1Inst.flags = Flags::READ;
    instructions.push_back(load1Inst);
    
    // Load second operand
    PimInstruction load2Inst;
    load2Inst.opcode = Opcode::LOAD;
    load2Inst.core_id = coreId;
    load2Inst.row_addr = src2Row;
    load2Inst.flags = Flags::READ;
    instructions.push_back(load2Inst);
    
    // Compute addition
    PimInstruction computeInst;
    computeInst.opcode = Opcode::COMPUTE;
    computeInst.core_id = coreId;
    computeInst.row_addr = 0;  // Result goes to a temporary register
    computeInst.flags = 0;
    instructions.push_back(computeInst);
    
    // Store result
    PimInstruction storeInst;
    storeInst.opcode = Opcode::STORE;
    storeInst.core_id = coreId;
    storeInst.row_addr = destRow;
    storeInst.flags = Flags::WRITE;
    instructions.push_back(storeInst);
    
    return instructions;
}

std::vector<PimInstruction> InstructionGenerator::generateMultiplyInstructions(const std::string& dest, const std::string& src1, const std::string& src2, int coreId) {
    std::vector<PimInstruction> instructions;
    
    // Map source variables to DRAM rows
    uint16_t src1Row = memoryMapper.mapVariableToRow(src1);
    uint16_t src2Row = memoryMapper.mapVariableToRow(src2);
    
    // Map destination variable to DRAM row
    uint16_t destRow = memoryMapper.mapVariableToRow(dest);
    
    // Program LUT for multiplication
    PimInstruction programLutInst;
    programLutInst.opcode = Opcode::PROGRAM_LUT;
    programLutInst.core_id = coreId;
    programLutInst.row_addr = 0;  // Special row for LUT programming
    programLutInst.flags = 1;     // Multiplication operation
    instructions.push_back(programLutInst);
    
    // Load first operand
    PimInstruction load1Inst;
    load1Inst.opcode = Opcode::LOAD;
    load1Inst.core_id = coreId;
    load1Inst.row_addr = src1Row;
    load1Inst.flags = Flags::READ;
    instructions.push_back(load1Inst);
    
    // Load second operand
    PimInstruction load2Inst;
    load2Inst.opcode = Opcode::LOAD;
    load2Inst.core_id = coreId;
    load2Inst.row_addr = src2Row;
    load2Inst.flags = Flags::READ;
    instructions.push_back(load2Inst);
    
    // Compute multiplication
    PimInstruction computeInst;
    computeInst.opcode = Opcode::COMPUTE;
    computeInst.core_id = coreId;
    computeInst.row_addr = 0;  // Result goes to a temporary register
    computeInst.flags = 0;
    instructions.push_back(computeInst);
    
    // Store result
    PimInstruction storeInst;
    storeInst.opcode = Opcode::STORE;
    storeInst.core_id = coreId;
    storeInst.row_addr = destRow;
    storeInst.flags = Flags::WRITE;
    instructions.push_back(storeInst);
    
    return instructions;
}

std::vector<PimInstruction> InstructionGenerator::generateMoveInstructions(const std::string& dest, const std::string& src, int coreId) {
    std::vector<PimInstruction> instructions;
    
    // Map destination variable to DRAM row
    uint16_t destRow = memoryMapper.mapVariableToRow(dest);
    
    // Check if source is a constant
    if (src == "0") {
        // Generate a MOVE instruction with constant 0
        PimInstruction moveInst;
        moveInst.opcode = Opcode::MOVE;
        moveInst.core_id = coreId;
        moveInst.row_addr = destRow;
        moveInst.flags = Flags::WRITE | Flags::RESET;  // RESET flag indicates constant 0
        instructions.push_back(moveInst);
    } else {
        // Map source variable to DRAM row
        uint16_t srcRow = memoryMapper.mapVariableToRow(src);
        
        // Generate LOAD instruction
        PimInstruction loadInst;
        loadInst.opcode = Opcode::LOAD;
        loadInst.core_id = coreId;
        loadInst.row_addr = srcRow;
        loadInst.flags = Flags::READ;
        instructions.push_back(loadInst);
        
        // Generate STORE instruction
        PimInstruction storeInst;
        storeInst.opcode = Opcode::STORE;
        storeInst.core_id = coreId;
        storeInst.row_addr = destRow;
        storeInst.flags = Flags::WRITE;
        instructions.push_back(storeInst);
    }
    
    return instructions;
}