#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <iomanip>
#include <cstdint>  // Add this include for uint8_t, uint16_t, uint32_t

// Structure to hold the paper's ISA format
struct PaperISAInstruction {
    uint8_t opType;     // 2 bits (00=NoOp, 01=PROG, 10=EXE, 11=END)
    uint8_t pointer;    // 6 bits (core pointer or operation pointer)
    bool readBit;       // 1 bit
    bool writeBit;      // 1 bit
    uint16_t rowAddr;   // 8 bits
    
    // Rest of the code remains unchanged
    
    // Convert to 24-bit binary representation (as a 32-bit int for convenience)
    uint32_t toBinary() const {
        uint32_t result = 0;
        
        // Upper 8 bits: 2-bit op type + 6-bit pointer
        result |= (opType & 0x3) << 22;
        result |= (pointer & 0x3F) << 16;
        
        // Next 10 bits: read bit + write bit + 8-bit row address
        result |= (readBit ? 1 : 0) << 15;
        result |= (writeBit ? 1 : 0) << 14;
        result |= (rowAddr & 0xFF) << 6;
        
        // Lower 6 bits are reserved (set to 0)
        
        return result;
    }
    
    // Convert to string representation
    std::string toString() const {
        std::stringstream ss;
        
        // Convert to binary and format as 6 hex digits
        ss << std::hex << std::setw(6) << std::setfill('0') << toBinary();
        
        // Add operation type
        ss << " ";
        switch (opType) {
            case 0: ss << "NoOp"; break;
            case 1: ss << "PROG"; break;
            case 2: ss << "EXE"; break;
            case 3: ss << "END"; break;
        }
        
        // Add pointer, read/write bits, and row address
        ss << " ptr=0x" << std::hex << (int)pointer;
        ss << " rd=" << (readBit ? "1" : "0");
        ss << " wr=" << (writeBit ? "1" : "0");
        ss << " row=0x" << std::hex << std::setw(2) << std::setfill('0') << rowAddr;
        
        return ss.str();
    }
};

// Map existing opcodes to the paper's format
PaperISAInstruction convertInstruction(const std::string& opcode, int coreId, int rowAddr, int flags) {
    PaperISAInstruction result;
    
    // Default values
    result.opType = 0;  // NoOp
    result.pointer = coreId & 0x3F;  // Use core ID as pointer (limited to 6 bits)
    result.readBit = false;
    result.writeBit = false;
    result.rowAddr = rowAddr & 0xFF;  // Limit to 8 bits
    
    // Map opcodes to paper's format
    if (opcode == "PROGRAM_LUT") {
        result.opType = 1;  // PROG
        result.pointer = coreId & 0x3F;
    }
    else if (opcode == "COMPUTE") {
        result.opType = 2;  // EXE
        result.pointer = flags & 0x3F;  // Use flags as operation pointer
    }
    else if (opcode == "SYNC") {
        result.opType = 3;  // END
    }
    else if (opcode == "LOAD") {
        result.readBit = true;
    }
    else if (opcode == "STORE") {
        result.writeBit = true;
    }
    else if (opcode == "MOVE") {
        result.readBit = true;
        result.writeBit = true;
    }
    
    return result;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_isa_file> <output_paper_isa_file>" << std::endl;
        return 1;
    }
    
    std::string inputFile = argv[1];
    std::string outputFile = argv[2];
    
    std::ifstream inFile(inputFile);
    if (!inFile) {
        std::cerr << "Error: Could not open input file " << inputFile << std::endl;
        return 1;
    }
    
    std::ofstream outFile(outputFile);
    if (!outFile) {
        std::cerr << "Error: Could not open output file " << outputFile << std::endl;
        return 1;
    }
    
    // Write header
    outFile << "# PIM ISA Instructions in Paper Format (24-bit)" << std::endl;
    outFile << "# Format: [Hex] [OpType] ptr=[Pointer] rd=[ReadBit] wr=[WriteBit] row=[RowAddress]" << std::endl;
    outFile << std::endl;
    
    std::string line;
    while (std::getline(inFile, line)) {
        // Skip comments and empty lines
        if (line.empty() || line[0] == '#') {
            continue;
        }
        
        // Parse the existing ISA format
        std::istringstream iss(line);
        std::string binary, opcode, coreStr, rowStr, flagsStr;
        
        iss >> binary >> opcode;
        
        // Extract core ID, row address, and flags
        int coreId = 0, rowAddr = 0, flags = 0;
        
        if (iss >> coreStr >> rowStr >> flagsStr) {
            // Extract core ID
            size_t pos = coreStr.find("=");
            if (pos != std::string::npos) {
                coreId = std::stoi(coreStr.substr(pos + 1));
            }
            
            // Extract row address
            pos = rowStr.find("=");
            if (pos != std::string::npos) {
                rowAddr = std::stoi(rowStr.substr(pos + 1), nullptr, 16);
            }
            
            // Extract flags
            pos = flagsStr.find("=");
            if (pos != std::string::npos) {
                flags = std::stoi(flagsStr.substr(pos + 1), nullptr, 16);
            }
        }
        
        // Convert to paper's format
        PaperISAInstruction paperInst = convertInstruction(opcode, coreId, rowAddr, flags);
        
        // Write to output file
        outFile << paperInst.toString() << std::endl;
    }
    
    inFile.close();
    outFile.close();
    
    std::cout << "Conversion complete. Output written to " << outputFile << std::endl;
    
    return 0;
}