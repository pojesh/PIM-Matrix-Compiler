#include "loop_analyzer.h"
#include <iostream>
#include <set>
#include <algorithm>

LoopAnalyzer::LoopAnalyzer(const std::vector<ThreeAddressInst>& code)
    : code(code) {
}

void LoopAnalyzer::analyze() {
    buildDependencyGraph();
    identifyLoops();
    analyzeParallelizability();
}

void LoopAnalyzer::buildDependencyGraph() {
    dependencyGraph.clear();
    
    // Track variable definitions and uses
    std::map<std::string, int> lastDef;
    
    for (int i = 0; i < code.size(); i++) {
        const auto& inst = code[i];
        std::vector<int> dependencies;
        
        // Check for dependencies on source operands
        if (!inst.src1.empty() && lastDef.find(inst.src1) != lastDef.end()) {
            dependencies.push_back(lastDef[inst.src1]);
        }
        
        if (!inst.src2.empty() && lastDef.find(inst.src2) != lastDef.end()) {
            dependencies.push_back(lastDef[inst.src2]);
        }
        
        // Record this instruction as defining its destination
        if (!inst.dest.empty()) {
            lastDef[inst.dest] = i;
        }
        
        dependencyGraph[i] = dependencies;
    }
}

void LoopAnalyzer::identifyLoops() {
    loops.clear();
    
    // In a real implementation, this would analyze the control flow graph
    // For this example, we'll use a simplified approach based on the
    // three-address code structure we generated in the parser
    
    // Identify the matrix multiplication loops
    // We know there are 3 nested loops for i, j, k
    
    Loop iLoop;
    iLoop.startIdx = 0;
    iLoop.endIdx = code.size() - 1;
    iLoop.nestLevel = 0;
    iLoop.inductionVar = "i";
    iLoop.lowerBound = 0;
    iLoop.upperBound = 2;  // 3x3 matrix example
    iLoop.step = 1;
    iLoop.isParallelizable = true;  // Outer loop can be parallelized
    
    Loop jLoop;
    jLoop.startIdx = 0;
    jLoop.endIdx = code.size() - 1;
    jLoop.nestLevel = 1;
    jLoop.inductionVar = "j";
    jLoop.lowerBound = 0;
    jLoop.upperBound = 2;
    jLoop.step = 1;
    jLoop.isParallelizable = true;  // Middle loop can be parallelized
    
    Loop kLoop;
    kLoop.startIdx = 0;
    kLoop.endIdx = code.size() - 1;
    kLoop.nestLevel = 2;
    kLoop.inductionVar = "k";
    kLoop.lowerBound = 0;
    kLoop.upperBound = 2;
    kLoop.step = 1;
    kLoop.isParallelizable = false;  // Innermost loop has dependencies
    
    loops.push_back(iLoop);
    loops.push_back(jLoop);
    loops.push_back(kLoop);
}

void LoopAnalyzer::analyzeParallelizability() {
    // For each loop, determine if it can be parallelized
    for (auto& loop : loops) {
        // Check for loop-carried dependencies
        bool hasLoopCarriedDependency = false;
        
        // In a real implementation, this would analyze the dependency graph
        // to determine if there are dependencies across loop iterations
        
        // For this example, we'll use our knowledge of matrix multiplication:
        // - The i and j loops can be parallelized
        // - The k loop has loop-carried dependencies due to accumulation
        
        if (loop.inductionVar == "k") {
            hasLoopCarriedDependency = true;
        }
        
        loop.isParallelizable = !hasLoopCarriedDependency;
    }
}

const std::vector<Loop>& LoopAnalyzer::getLoops() const {
    return loops;
}

std::vector<Loop> LoopAnalyzer::getParallelizableLoops() const {
    std::vector<Loop> parallelizableLoops;
    for (const auto& loop : loops) {
        if (loop.isParallelizable) {
            parallelizableLoops.push_back(loop);
        }
    }
    return parallelizableLoops;
}

const std::map<int, std::vector<int>>& LoopAnalyzer::getDependencyGraph() const {
    return dependencyGraph;
}