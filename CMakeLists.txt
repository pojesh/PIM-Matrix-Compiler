cmake_minimum_required(VERSION 3.10)
project(CompilerDA3)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find LLVM
find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

# Include LLVM headers
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

# Add include directory
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Add source files
set(SOURCES
    src/main.cpp
    src/parser.cpp
    src/loop_analyzer.cpp
    src/memory_mapper.cpp
    src/instruction_generator.cpp
)

# Create executable
add_executable(pim_compiler ${SOURCES})

# Link against LLVM libraries
llvm_map_components_to_libnames(llvm_libs support core irreader analysis)
target_link_libraries(pim_compiler ${llvm_libs})

# Add example directory
add_subdirectory(examples)