#ifndef LOOP_ANALYZER_H
#define LOOP_ANALYZER_H

#include "parser.h"
#include <vector>
#include <map>

// Represents a loop in the code
struct Loop {
    int startIdx;  // Start index in the three-address code
    int endIdx;    // End index in the three-address code
    int nestLevel; // Nesting level (0 = outermost)
    std::string inductionVar; // Loop induction variable
    int lowerBound; // Loop lower bound
    int upperBound; // Loop upper bound
    int step;       // Loop step
    bool isParallelizable; // Whether the loop can be parallelized
};

class LoopAnalyzer {
public:
    LoopAnalyzer(const std::vector<ThreeAddressInst>& code);
    
    // Analyze the code to identify loops and their properties
    void analyze();
    
    // Get the identified loops
    const std::vector<Loop>& getLoops() const;
    
    // Get the parallelizable loops
    std::vector<Loop> getParallelizableLoops() const;
    
    // Get the dependency graph for the code
    const std::map<int, std::vector<int>>& getDependencyGraph() const;
    
private:
    // The three-address code to analyze
    const std::vector<ThreeAddressInst>& code;
    
    // Identified loops
    std::vector<Loop> loops;
    
    // Dependency graph (instruction index -> dependent instruction indices)
    std::map<int, std::vector<int>> dependencyGraph;
    
    // Build the dependency graph
    void buildDependencyGraph();
    
    // Identify loops in the code
    void identifyLoops();
    
    // Analyze loop parallelizability
    void analyzeParallelizability();
};

#endif // LOOP_ANALYZER_H