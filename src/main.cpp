#include "parser.h"
#include "loop_analyzer.h"
#include "memory_mapper.h"
#include "instruction_generator.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

void printInstructions(const std::vector<PimInstruction>& instructions, std::ostream& out) {
    out << "# PIM ISA Instructions for Matrix Multiplication" << std::endl;
    out << "# Format: [Binary] [Opcode] core=[Core ID] row=[Row Address] flags=[Flags]" << std::endl;
    out << std::endl;
    
    for (size_t i = 0; i < instructions.size(); i++) {
        const auto& inst = instructions[i];
        out << std::setw(8) << std::setfill('0') << std::hex << inst.toBinary() << " ";
        out << std::setw(0) << std::setfill(' ') << std::dec << inst.toString() << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
        return 1;
    }
    
    std::string inputFile = argv[1];
    std::string outputFile = argv[2];
    
    // Step 1: Parse the input file
    Parser parser;
    if (!parser.parseFile(inputFile)) {
        std::cerr << "Failed to parse input file: " << inputFile << std::endl;
        return 1;
    }
    
    // Get the three-address code
    const auto& threeAddressCode = parser.getThreeAddressCode();
    
    // Print the three-address code
    std::cout << "Three-Address Code:" << std::endl;
    for (const auto& inst : threeAddressCode) {
        std::cout << inst.toString() << std::endl;
    }
    std::cout << std::endl;
    
    // Step 2: Analyze loops for parallelization
    LoopAnalyzer loopAnalyzer(threeAddressCode);
    loopAnalyzer.analyze();
    
    // Get the identified loops
    const auto& loops = loopAnalyzer.getLoops();
    
    // Print the loops
    std::cout << "Identified Loops:" << std::endl;
    for (const auto& loop : loops) {
        std::cout << "Loop " << loop.inductionVar << ": ";
        std::cout << "Nest Level = " << loop.nestLevel << ", ";
        std::cout << "Range = [" << loop.lowerBound << ", " << loop.upperBound << "], ";
        std::cout << "Parallelizable = " << (loop.isParallelizable ? "Yes" : "No") << std::endl;
    }
    std::cout << std::endl;
    
    // Step 3: Set up memory mapping
    int rows1, cols1, rows2, cols2;
    parser.getMatrixDimensions(rows1, cols1, rows2, cols2);
    
    // For the example, we'll use 3x3 matrices
    if (rows1 == 0) rows1 = 3;
    if (cols1 == 0) cols1 = 3;
    if (rows2 == 0) rows2 = 3;
    if (cols2 == 0) cols2 = 3;
    
    MemoryMapper memoryMapper(rows1, cols1, rows2, cols2);
    
    // Step 4: Generate PIM ISA instructions
    InstructionGenerator instructionGenerator(threeAddressCode, loops, memoryMapper);
    auto instructions = instructionGenerator.generateInstructions();
    
    // Print the instructions
    std::cout << "Generated " << instructions.size() << " PIM ISA instructions." << std::endl;
    
    // Write the instructions to the output file
    std::ofstream outFile(outputFile);
    if (!outFile) {
        std::cerr << "Failed to open output file: " << outputFile << std::endl;
        return 1;
    }
    
    printInstructions(instructions, outFile);
    outFile.close();
    
    std::cout << "Instructions written to " << outputFile << std::endl;
    
    return 0;
}