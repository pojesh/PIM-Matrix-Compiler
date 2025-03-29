#include "memory_mapper.h"
#include <iostream>
#include <regex>
#include <cstdint>

MemoryMapper::MemoryMapper(int rows1, int cols1, int rows2, int cols2)
    : matrixRows1(rows1), matrixCols1(cols1), matrixRows2(rows2), matrixCols2(cols2) {
    
    // Set base row addresses for matrices
    matrixABaseRow = 0;
    matrixBBaseRow = matrixRows1 * matrixCols1;
    matrixCBaseRow = matrixBBaseRow + matrixRows2 * matrixCols2;
    
    initializeMapping();
}

void MemoryMapper::initializeMapping() {
    // Map matrix A elements
    for (int i = 0; i < matrixRows1; i++) {
        for (int j = 0; j < matrixCols1; j++) {
            std::string varName = "A_" + std::to_string(i) + "_" + std::to_string(j);
            uint16_t rowAddr = matrixABaseRow + i * matrixCols1 + j;
            variableToRowMap[varName] = rowAddr;
        }
    }
    
    // Map matrix B elements
    for (int i = 0; i < matrixRows2; i++) {
        for (int j = 0; j < matrixCols2; j++) {
            std::string varName = "B_" + std::to_string(i) + "_" + std::to_string(j);
            uint16_t rowAddr = matrixBBaseRow + i * matrixCols2 + j;
            variableToRowMap[varName] = rowAddr;
        }
    }
    
    // Map matrix C elements
    for (int i = 0; i < matrixRows1; i++) {
        for (int j = 0; j < matrixCols2; j++) {
            std::string varName = "C_" + std::to_string(i) + "_" + std::to_string(j);
            uint16_t rowAddr = matrixCBaseRow + i * matrixCols2 + j;
            variableToRowMap[varName] = rowAddr;
        }
    }
}

uint16_t MemoryMapper::mapVariableToRow(const std::string& varName) {
    // Check if the variable is already mapped
    if (variableToRowMap.find(varName) != variableToRowMap.end()) {
        return variableToRowMap[varName];
    }
    
    // Check if it's a matrix element using regex
    std::regex matrixPattern("([A-C])_([0-9]+)_([0-9]+)");
    std::smatch matches;
    
    if (std::regex_match(varName, matches, matrixPattern)) {
        std::string matrixName = matches[1].str();
        int row = std::stoi(matches[2].str());
        int col = std::stoi(matches[3].str());
        
        return getMatrixElementRow(matrixName, row, col);
    }
    
    // For temporary variables, allocate new rows after the matrices
    uint16_t newRow = matrixCBaseRow + matrixRows1 * matrixCols2 + variableToRowMap.size();
    variableToRowMap[varName] = newRow;
    
    return newRow;
}

uint16_t MemoryMapper::getMatrixElementRow(const std::string& matrixName, int row, int col) {
    if (matrixName == "A") {
        return matrixABaseRow + row * matrixCols1 + col;
    } else if (matrixName == "B") {
        return matrixBBaseRow + row * matrixCols2 + col;
    } else if (matrixName == "C") {
        return matrixCBaseRow + row * matrixCols2 + col;
    } else {
        std::cerr << "Unknown matrix name: " << matrixName << std::endl;
        return 0;
    }
}

int MemoryMapper::getTotalRowsNeeded() const {
    return matrixCBaseRow + matrixRows1 * matrixCols2 + variableToRowMap.size();
}