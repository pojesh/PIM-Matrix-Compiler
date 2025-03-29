#include "parser.h"
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Analysis/LoopInfo.h>
#include <llvm/Transforms/Utils.h>
#include <iostream>

std::string ThreeAddressInst::toString() const {
    std::string result;
    switch (op) {
        case OpType::LOAD: result = dest + " = LOAD " + src1; break;
        case OpType::STORE: result = "STORE " + src1 + " to " + dest; break;
        case OpType::ADD: result = dest + " = " + src1 + " + " + src2; break;
        case OpType::MULTIPLY: result = dest + " = " + src1 + " * " + src2; break;
        case OpType::MOVE: result = dest + " = " + src1; break;
    }
    return result;
}

Parser::Parser() : matrixRows1(0), matrixCols1(0), matrixRows2(0), matrixCols2(0) {
}

Parser::~Parser() {
}

bool Parser::parseFile(const std::string& filename) {
    llvm::LLVMContext context;
    llvm::SMDiagnostic err;
    
    // Parse the input file to get LLVM IR
    module = llvm::parseIRFile(filename, err, context);
    
    if (!module) {
        std::cerr << "Error parsing IR file: " << filename << std::endl;
        err.print(filename.c_str(), llvm::errs());
        return false;
    }
    
    // Extract matrix dimensions from global variables or function parameters
    // This is a simplified approach - in a real implementation, you would
    // analyze the code to determine the dimensions
    matrixRows1 = matrixCols1 = matrixRows2 = matrixCols2 = 100;  // Default size
    
    // Generate three-address code from the LLVM IR
    generateThreeAddressCode();
    
    return true;
}

void Parser::generateThreeAddressCode() {
    // Clear any existing code
    threeAddressCode.clear();
    
    // Find the main function or the matrix multiplication function
    llvm::Function* mainFunc = module->getFunction("main");
    if (!mainFunc) {
        std::cerr << "Could not find main function in the module" << std::endl;
        return;
    }
    
    // Create a loop info pass to identify loops
    llvm::legacy::FunctionPassManager FPM(module.get());
    llvm::LoopInfo* LI = new llvm::LoopInfo();
    
    // Analyze the function to find loops
    for (auto& BB : *mainFunc) {
        for (auto& I : BB) {
            if (auto* load = llvm::dyn_cast<llvm::LoadInst>(&I)) {
                // Process load instruction
                ThreeAddressInst tai;
                tai.op = ThreeAddressInst::OpType::LOAD;
                tai.dest = "t" + std::to_string(threeAddressCode.size());
                tai.src1 = load->getPointerOperand()->getName().str();
                threeAddressCode.push_back(tai);
            }
            else if (auto* store = llvm::dyn_cast<llvm::StoreInst>(&I)) {
                // Process store instruction
                ThreeAddressInst tai;
                tai.op = ThreeAddressInst::OpType::STORE;
                tai.dest = store->getPointerOperand()->getName().str();
                tai.src1 = "t" + std::to_string(threeAddressCode.size() - 1);
                threeAddressCode.push_back(tai);
            }
            else if (auto* binOp = llvm::dyn_cast<llvm::BinaryOperator>(&I)) {
                // Process binary operations (add, multiply)
                ThreeAddressInst tai;
                tai.dest = "t" + std::to_string(threeAddressCode.size());
                
                // Get operand names
                if (auto* op1 = llvm::dyn_cast<llvm::LoadInst>(binOp->getOperand(0))) {
                    tai.src1 = op1->getPointerOperand()->getName().str();
                } else {
                    tai.src1 = "t" + std::to_string(threeAddressCode.size() - 2);
                }
                
                if (auto* op2 = llvm::dyn_cast<llvm::LoadInst>(binOp->getOperand(1))) {
                    tai.src2 = op2->getPointerOperand()->getName().str();
                } else {
                    tai.src2 = "t" + std::to_string(threeAddressCode.size() - 1);
                }
                
                // Determine operation type
                if (binOp->getOpcode() == llvm::Instruction::Add) {
                    tai.op = ThreeAddressInst::OpType::ADD;
                } else if (binOp->getOpcode() == llvm::Instruction::Mul) {
                    tai.op = ThreeAddressInst::OpType::MULTIPLY;
                }
                
                threeAddressCode.push_back(tai);
            }
        }
    }
    
    // For demonstration purposes, let's add some matrix multiplication code
    // In a real implementation, this would be derived from the LLVM IR analysis
    
    // Simplified matrix multiplication in three-address code
    // for (i = 0; i < N; i++)
    //   for (j = 0; j < N; j++)
    //     for (k = 0; k < N; k++)
    //       C[i][j] += A[i][k] * B[k][j]
    
    for (int i = 0; i < 3; i++) {  // Just generate a small example
        for (int j = 0; j < 3; j++) {
            // Initialize C[i][j] to 0
            ThreeAddressInst init;
            init.op = ThreeAddressInst::OpType::MOVE;
            init.dest = "C_" + std::to_string(i) + "_" + std::to_string(j);
            init.src1 = "0";
            threeAddressCode.push_back(init);
            
            for (int k = 0; k < 3; k++) {
                // Load A[i][k]
                ThreeAddressInst loadA;
                loadA.op = ThreeAddressInst::OpType::LOAD;
                loadA.dest = "t_A_" + std::to_string(i) + "_" + std::to_string(k);
                loadA.src1 = "A_" + std::to_string(i) + "_" + std::to_string(k);
                threeAddressCode.push_back(loadA);
                
                // Load B[k][j]
                ThreeAddressInst loadB;
                loadB.op = ThreeAddressInst::OpType::LOAD;
                loadB.dest = "t_B_" + std::to_string(k) + "_" + std::to_string(j);
                loadB.src1 = "B_" + std::to_string(k) + "_" + std::to_string(j);
                threeAddressCode.push_back(loadB);
                
                // Multiply A[i][k] * B[k][j]
                ThreeAddressInst mul;
                mul.op = ThreeAddressInst::OpType::MULTIPLY;
                mul.dest = "t_mul_" + std::to_string(i) + "_" + std::to_string(j) + "_" + std::to_string(k);
                mul.src1 = "t_A_" + std::to_string(i) + "_" + std::to_string(k);
                mul.src2 = "t_B_" + std::to_string(k) + "_" + std::to_string(j);
                threeAddressCode.push_back(mul);
                
                // Load current C[i][j]
                ThreeAddressInst loadC;
                loadC.op = ThreeAddressInst::OpType::LOAD;
                loadC.dest = "t_C_" + std::to_string(i) + "_" + std::to_string(j);
                loadC.src1 = "C_" + std::to_string(i) + "_" + std::to_string(j);
                threeAddressCode.push_back(loadC);
                
                // Add to C[i][j]
                ThreeAddressInst add;
                add.op = ThreeAddressInst::OpType::ADD;
                add.dest = "t_C_new_" + std::to_string(i) + "_" + std::to_string(j);
                add.src1 = "t_C_" + std::to_string(i) + "_" + std::to_string(j);
                add.src2 = "t_mul_" + std::to_string(i) + "_" + std::to_string(j) + "_" + std::to_string(k);
                threeAddressCode.push_back(add);
                
                // Store back to C[i][j]
                ThreeAddressInst storeC;
                storeC.op = ThreeAddressInst::OpType::STORE;
                storeC.dest = "C_" + std::to_string(i) + "_" + std::to_string(j);
                storeC.src1 = "t_C_new_" + std::to_string(i) + "_" + std::to_string(j);
                threeAddressCode.push_back(storeC);
            }
        }
    }
}

const std::vector<ThreeAddressInst>& Parser::getThreeAddressCode() const {
    return threeAddressCode;
}

void Parser::getMatrixDimensions(int& rows1, int& cols1, int& rows2, int& cols2) {
    rows1 = matrixRows1;
    cols1 = matrixCols1;
    rows2 = matrixRows2;
    cols2 = matrixCols2;
}