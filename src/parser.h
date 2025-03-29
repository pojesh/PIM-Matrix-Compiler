#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include <memory>
#include <llvm/IR/Module.h>

// Forward declarations
namespace llvm {
    class Function;
    class Loop;
}

// Represents a three-address instruction
struct ThreeAddressInst {
    enum class OpType {
        LOAD,
        STORE,
        ADD,
        MULTIPLY,
        MOVE
    };
    
    OpType op;
    std::string dest;
    std::string src1;
    std::string src2;  // May be empty for LOAD/STORE
    
    std::string toString() const;
};

class Parser {
public:
    Parser();
    ~Parser();
    
    // Parse C++ file and generate LLVM IR
    bool parseFile(const std::string& filename);
    
    // Get the generated three-address code
    const std::vector<ThreeAddressInst>& getThreeAddressCode() const;
    
    // Get matrix dimensions from the parsed code
    void getMatrixDimensions(int& rows1, int& cols1, int& rows2, int& cols2);
    
private:
    // Convert LLVM IR to three-address code
    void generateThreeAddressCode();
    
    // Process a loop in the LLVM IR
    void processLoop(llvm::Loop* loop);
    
    // LLVM module containing the parsed code
    std::unique_ptr<llvm::Module> module;
    
    // Three-address code representation
    std::vector<ThreeAddressInst> threeAddressCode;
    
    // Matrix dimensions
    int matrixRows1, matrixCols1, matrixRows2, matrixCols2;
};

#endif // PARSER_H