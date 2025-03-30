# PIM-Matrix-Compiler

A specialized compiler that translates C++ matrix multiplication code into custom ISA instructions for DRAM-based Processing-in-Memory (PIM) architecture. This project implements a complete toolchain that analyzes matrix operations, identifies parallelizable loops, maps data to DRAM rows, and generates optimized instructions for LUT-based PIM execution.

This compiler generates a ThreeAddressCode (TAC) representation of the input matrix multiplication code, which is then used to generate the 32bit ISA instructions for the PIM architecture. Further the 32bit ISA instructions are converted to 24bit ISA instructions as discussed in attached research paper.
Alternatively the 24bit ISA instructions can be generated directly from the TAC representation with slight modifications in the implementation.

## 📂 Directory Structure

```
PIM-Matrix-Compiler/
├── src/                      # Source code for the compiler
│   ├── main.cpp              # Main driver program
│   ├── parser.cpp            # LLVM-based C++ parser
│   ├── parser.h
│   ├── loop_analyzer.cpp     # Loop analysis and parallelization
│   ├── loop_analyzer.h
│   ├── memory_mapper.cpp     # DRAM memory mapping
│   ├── memory_mapper.h
│   ├── isa_converter.cpp     # Converts the obtained ISA op to ISA 24bit format
│   ├── instruction_generator.cpp # Custom ISA instruction generator
│   └── instruction_generator.h
├── include/                  # Header files
│   └── pim_isa.h             # PIM ISA definitions
├── examples/                 # Example matrix multiplication code
│   ├── matrix_mult.cpp       # Matrix multiplication implementation
│   └── CMakeLists.txt        # Build configuration for examples
├── results/                 
│   ├── ThreeAddressCode.txt       # 3AC of the cpp program
│   ├── ISA_Instructions_PaperFormat_24bit.txt       # ISA instructions in research paper format - 24bit
│   └── ISA_Instructions_CustomFormat.txt       # ISA instruction
├── documents/                 
│   ├── LUT_Design.png        # LookUp Table Design Image
│   ├── worflow.png           # Project Workflow Flowchart
│   ├── Research Paper        # PDF file of the reference research paper            
│   └── Final_Report.pdf      # PDF document containing project report
├── build/                    # Build directory (generated)
└── CMakeLists.txt            # Main build configuration
```

## 📦 Dependencies

The following dependencies are required to build and run the compiler:

```bash
# Update package lists
sudo apt update

# Install build essentials (includes g++ compiler)
sudo apt install -y build-essential

# Install CMake
sudo apt install -y cmake

# Install LLVM and Clang
sudo apt install -y llvm llvm-dev clang

# Install ZLIB development package
sudo apt install -y zlib1g-dev

# Install other needed dependencies
sudo apt install -y libzstd-dev libcurl4-openssl-dev

# Install LBEdit package
sudo apt-get install libedit-dev
```

## ⚙️ Building and Running

### 🔨 Building the Project

```bash
#NOTE: The repository already contains pre-built files, so skip to Compilation steps 

# Create and navigate to the build directory
cd build

# Configure with CMake
cmake ..

# Build the project
make
```

### 🚀 Running the Compiler

```bash
# From build directory

# Generate LLVM IR from the matrix multiplication example
clang++ -S -emit-llvm ../examples/matrix_mult.cpp -o matrix_mult.ll

# Run the matrix multiplication example directly
./examples/matrix_mult

# Run the PIM compiler on the LLVM IR
./pim_compiler matrix_mult.ll matrix_mult.isa

# View the three-address code (displayed in terminal)

# View the 32bit ISA instructions
cat matrix_mult.isa

# Convert ISA to ISA 24bit format from Research Paper
./examples/isa_converter matrix_mult.isa matrix_mult_paper.isa

# View the 24bit ISA instructions
cat matrix_mult_paper.isa
```

## ✨ Features

- **LLVM Integration**: Uses the LLVM framework to parse C++ code and generate an intermediate representation.
- **Loop Analysis**: Identifies parallelizable loops in matrix multiplication.
- **Memory Mapping**: Maps matrix data to DRAM rows for efficient access.
- **Custom ISA Generation**: Produces optimized instructions for the PIM architecture.
- **Parallelization**: Exploits parallelism by distributing independent operations across multiple cores.

## 🔍 Implementation Details

The compiler follows a structured approach to process matrix multiplication code:

1. **Parsing**: Uses LLVM to parse the input C++ code and convert it into an intermediate representation (IR).
2. **Three-Address Code Conversion**: Converts the LLVM IR into three-address code for easier manipulation.
3. **Loop Analysis**: Identifies loops that can be parallelized for PIM execution.
4. **Memory Mapping**: Organizes matrix data into DRAM rows for efficient retrieval.
5. **ISA Instruction Generation**: Converts optimized code into PIM-specific instructions.
6. **Parallel Execution Optimization**: Ensures instructions take advantage of multiple PIM cores for performance gains.

The generated instructions conform to the custom ISA, including opcodes for memory operations, LUT programming, and computation.

## 📜 License

This project is licensed under the GNU GPL v3.0 License - see the [LICENSE](LICENSE) file for details.

## 🤝 Contributing

Contributions are welcome! Feel free to open an issue or submit a pull request.

## 📧 Contact

For any inquiries or support, please reach out to the project maintainers or open an issue in the repository.

---

Enjoy coding with PIM-Matrix-Compiler! 🚀

