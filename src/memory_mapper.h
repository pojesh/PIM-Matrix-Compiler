#ifndef MEMORY_MAPPER_H
#define MEMORY_MAPPER_H

#include <string>
#include <map>
#include <cstdint>  // Add this include for uint16_t

class MemoryMapper {
public:
    MemoryMapper(int rows1, int cols1, int rows2, int cols2);
    
    // Map a variable to a DRAM row address
    uint16_t mapVariableToRow(const std::string& varName);
    
    // Get the row address for a matrix element
    uint16_t getMatrixElementRow(const std::string& matrixName, int row, int col);
    
    // Get the total number of rows needed
    int getTotalRowsNeeded() const;
    
private:
    // Matrix dimensions
    int matrixRows1, matrixCols1, matrixRows2, matrixCols2;
    
    // Base row addresses for matrices
    uint16_t matrixABaseRow;
    uint16_t matrixBBaseRow;
    uint16_t matrixCBaseRow;
    
    // Map of variable names to row addresses
    std::map<std::string, uint16_t> variableToRowMap;
    
    // Initialize the mapping
    void initializeMapping();
};

#endif // MEMORY_MAPPER_H