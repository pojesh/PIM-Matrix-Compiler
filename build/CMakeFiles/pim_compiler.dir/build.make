# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/Users/Pojesh/Documents/OfficialWorks/CompilerDA3/Documents/Working

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/Pojesh/Documents/OfficialWorks/CompilerDA3/Documents/Working/build

# Include any dependencies generated for this target.
include CMakeFiles/pim_compiler.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/pim_compiler.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/pim_compiler.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/pim_compiler.dir/flags.make

CMakeFiles/pim_compiler.dir/src/main.cpp.o: CMakeFiles/pim_compiler.dir/flags.make
CMakeFiles/pim_compiler.dir/src/main.cpp.o: /mnt/c/Users/Pojesh/Documents/OfficialWorks/CompilerDA3/Documents/Working/src/main.cpp
CMakeFiles/pim_compiler.dir/src/main.cpp.o: CMakeFiles/pim_compiler.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/mnt/c/Users/Pojesh/Documents/OfficialWorks/CompilerDA3/Documents/Working/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/pim_compiler.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/pim_compiler.dir/src/main.cpp.o -MF CMakeFiles/pim_compiler.dir/src/main.cpp.o.d -o CMakeFiles/pim_compiler.dir/src/main.cpp.o -c /mnt/c/Users/Pojesh/Documents/OfficialWorks/CompilerDA3/Documents/Working/src/main.cpp

CMakeFiles/pim_compiler.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/pim_compiler.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/Pojesh/Documents/OfficialWorks/CompilerDA3/Documents/Working/src/main.cpp > CMakeFiles/pim_compiler.dir/src/main.cpp.i

CMakeFiles/pim_compiler.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/pim_compiler.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/Pojesh/Documents/OfficialWorks/CompilerDA3/Documents/Working/src/main.cpp -o CMakeFiles/pim_compiler.dir/src/main.cpp.s

CMakeFiles/pim_compiler.dir/src/parser.cpp.o: CMakeFiles/pim_compiler.dir/flags.make
CMakeFiles/pim_compiler.dir/src/parser.cpp.o: /mnt/c/Users/Pojesh/Documents/OfficialWorks/CompilerDA3/Documents/Working/src/parser.cpp
CMakeFiles/pim_compiler.dir/src/parser.cpp.o: CMakeFiles/pim_compiler.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/mnt/c/Users/Pojesh/Documents/OfficialWorks/CompilerDA3/Documents/Working/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/pim_compiler.dir/src/parser.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/pim_compiler.dir/src/parser.cpp.o -MF CMakeFiles/pim_compiler.dir/src/parser.cpp.o.d -o CMakeFiles/pim_compiler.dir/src/parser.cpp.o -c /mnt/c/Users/Pojesh/Documents/OfficialWorks/CompilerDA3/Documents/Working/src/parser.cpp

CMakeFiles/pim_compiler.dir/src/parser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/pim_compiler.dir/src/parser.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/Pojesh/Documents/OfficialWorks/CompilerDA3/Documents/Working/src/parser.cpp > CMakeFiles/pim_compiler.dir/src/parser.cpp.i

CMakeFiles/pim_compiler.dir/src/parser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/pim_compiler.dir/src/parser.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/Pojesh/Documents/OfficialWorks/CompilerDA3/Documents/Working/src/parser.cpp -o CMakeFiles/pim_compiler.dir/src/parser.cpp.s

CMakeFiles/pim_compiler.dir/src/loop_analyzer.cpp.o: CMakeFiles/pim_compiler.dir/flags.make
CMakeFiles/pim_compiler.dir/src/loop_analyzer.cpp.o: /mnt/c/Users/Pojesh/Documents/OfficialWorks/CompilerDA3/Documents/Working/src/loop_analyzer.cpp
CMakeFiles/pim_compiler.dir/src/loop_analyzer.cpp.o: CMakeFiles/pim_compiler.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/mnt/c/Users/Pojesh/Documents/OfficialWorks/CompilerDA3/Documents/Working/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/pim_compiler.dir/src/loop_analyzer.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/pim_compiler.dir/src/loop_analyzer.cpp.o -MF CMakeFiles/pim_compiler.dir/src/loop_analyzer.cpp.o.d -o CMakeFiles/pim_compiler.dir/src/loop_analyzer.cpp.o -c /mnt/c/Users/Pojesh/Documents/OfficialWorks/CompilerDA3/Documents/Working/src/loop_analyzer.cpp

CMakeFiles/pim_compiler.dir/src/loop_analyzer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/pim_compiler.dir/src/loop_analyzer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/Pojesh/Documents/OfficialWorks/CompilerDA3/Documents/Working/src/loop_analyzer.cpp > CMakeFiles/pim_compiler.dir/src/loop_analyzer.cpp.i

CMakeFiles/pim_compiler.dir/src/loop_analyzer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/pim_compiler.dir/src/loop_analyzer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/Pojesh/Documents/OfficialWorks/CompilerDA3/Documents/Working/src/loop_analyzer.cpp -o CMakeFiles/pim_compiler.dir/src/loop_analyzer.cpp.s

CMakeFiles/pim_compiler.dir/src/memory_mapper.cpp.o: CMakeFiles/pim_compiler.dir/flags.make
CMakeFiles/pim_compiler.dir/src/memory_mapper.cpp.o: /mnt/c/Users/Pojesh/Documents/OfficialWorks/CompilerDA3/Documents/Working/src/memory_mapper.cpp
CMakeFiles/pim_compiler.dir/src/memory_mapper.cpp.o: CMakeFiles/pim_compiler.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/mnt/c/Users/Pojesh/Documents/OfficialWorks/CompilerDA3/Documents/Working/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/pim_compiler.dir/src/memory_mapper.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/pim_compiler.dir/src/memory_mapper.cpp.o -MF CMakeFiles/pim_compiler.dir/src/memory_mapper.cpp.o.d -o CMakeFiles/pim_compiler.dir/src/memory_mapper.cpp.o -c /mnt/c/Users/Pojesh/Documents/OfficialWorks/CompilerDA3/Documents/Working/src/memory_mapper.cpp

CMakeFiles/pim_compiler.dir/src/memory_mapper.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/pim_compiler.dir/src/memory_mapper.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/Pojesh/Documents/OfficialWorks/CompilerDA3/Documents/Working/src/memory_mapper.cpp > CMakeFiles/pim_compiler.dir/src/memory_mapper.cpp.i

CMakeFiles/pim_compiler.dir/src/memory_mapper.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/pim_compiler.dir/src/memory_mapper.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/Pojesh/Documents/OfficialWorks/CompilerDA3/Documents/Working/src/memory_mapper.cpp -o CMakeFiles/pim_compiler.dir/src/memory_mapper.cpp.s

CMakeFiles/pim_compiler.dir/src/instruction_generator.cpp.o: CMakeFiles/pim_compiler.dir/flags.make
CMakeFiles/pim_compiler.dir/src/instruction_generator.cpp.o: /mnt/c/Users/Pojesh/Documents/OfficialWorks/CompilerDA3/Documents/Working/src/instruction_generator.cpp
CMakeFiles/pim_compiler.dir/src/instruction_generator.cpp.o: CMakeFiles/pim_compiler.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/mnt/c/Users/Pojesh/Documents/OfficialWorks/CompilerDA3/Documents/Working/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/pim_compiler.dir/src/instruction_generator.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/pim_compiler.dir/src/instruction_generator.cpp.o -MF CMakeFiles/pim_compiler.dir/src/instruction_generator.cpp.o.d -o CMakeFiles/pim_compiler.dir/src/instruction_generator.cpp.o -c /mnt/c/Users/Pojesh/Documents/OfficialWorks/CompilerDA3/Documents/Working/src/instruction_generator.cpp

CMakeFiles/pim_compiler.dir/src/instruction_generator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/pim_compiler.dir/src/instruction_generator.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/Pojesh/Documents/OfficialWorks/CompilerDA3/Documents/Working/src/instruction_generator.cpp > CMakeFiles/pim_compiler.dir/src/instruction_generator.cpp.i

CMakeFiles/pim_compiler.dir/src/instruction_generator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/pim_compiler.dir/src/instruction_generator.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/Pojesh/Documents/OfficialWorks/CompilerDA3/Documents/Working/src/instruction_generator.cpp -o CMakeFiles/pim_compiler.dir/src/instruction_generator.cpp.s

# Object files for target pim_compiler
pim_compiler_OBJECTS = \
"CMakeFiles/pim_compiler.dir/src/main.cpp.o" \
"CMakeFiles/pim_compiler.dir/src/parser.cpp.o" \
"CMakeFiles/pim_compiler.dir/src/loop_analyzer.cpp.o" \
"CMakeFiles/pim_compiler.dir/src/memory_mapper.cpp.o" \
"CMakeFiles/pim_compiler.dir/src/instruction_generator.cpp.o"

# External object files for target pim_compiler
pim_compiler_EXTERNAL_OBJECTS =

pim_compiler: CMakeFiles/pim_compiler.dir/src/main.cpp.o
pim_compiler: CMakeFiles/pim_compiler.dir/src/parser.cpp.o
pim_compiler: CMakeFiles/pim_compiler.dir/src/loop_analyzer.cpp.o
pim_compiler: CMakeFiles/pim_compiler.dir/src/memory_mapper.cpp.o
pim_compiler: CMakeFiles/pim_compiler.dir/src/instruction_generator.cpp.o
pim_compiler: CMakeFiles/pim_compiler.dir/build.make
pim_compiler: /usr/lib/llvm-18/lib/libLLVMSupport.a
pim_compiler: /usr/lib/llvm-18/lib/libLLVMCore.a
pim_compiler: /usr/lib/llvm-18/lib/libLLVMIRReader.a
pim_compiler: /usr/lib/llvm-18/lib/libLLVMAnalysis.a
pim_compiler: /usr/lib/llvm-18/lib/libLLVMProfileData.a
pim_compiler: /usr/lib/llvm-18/lib/libLLVMSymbolize.a
pim_compiler: /usr/lib/llvm-18/lib/libLLVMDebugInfoPDB.a
pim_compiler: /usr/lib/llvm-18/lib/libLLVMDebugInfoMSF.a
pim_compiler: /usr/lib/llvm-18/lib/libLLVMDebugInfoBTF.a
pim_compiler: /usr/lib/llvm-18/lib/libLLVMDebugInfoDWARF.a
pim_compiler: /usr/lib/llvm-18/lib/libLLVMObject.a
pim_compiler: /usr/lib/llvm-18/lib/libLLVMIRReader.a
pim_compiler: /usr/lib/llvm-18/lib/libLLVMAsmParser.a
pim_compiler: /usr/lib/llvm-18/lib/libLLVMBitReader.a
pim_compiler: /usr/lib/llvm-18/lib/libLLVMCore.a
pim_compiler: /usr/lib/llvm-18/lib/libLLVMRemarks.a
pim_compiler: /usr/lib/llvm-18/lib/libLLVMBitstreamReader.a
pim_compiler: /usr/lib/llvm-18/lib/libLLVMMCParser.a
pim_compiler: /usr/lib/llvm-18/lib/libLLVMMC.a
pim_compiler: /usr/lib/llvm-18/lib/libLLVMDebugInfoCodeView.a
pim_compiler: /usr/lib/llvm-18/lib/libLLVMTextAPI.a
pim_compiler: /usr/lib/llvm-18/lib/libLLVMBinaryFormat.a
pim_compiler: /usr/lib/llvm-18/lib/libLLVMTargetParser.a
pim_compiler: /usr/lib/llvm-18/lib/libLLVMSupport.a
pim_compiler: /usr/lib/x86_64-linux-gnu/libz.so
pim_compiler: /usr/lib/x86_64-linux-gnu/libzstd.so
pim_compiler: /usr/lib/x86_64-linux-gnu/libtinfo.so
pim_compiler: /usr/lib/llvm-18/lib/libLLVMDemangle.a
pim_compiler: CMakeFiles/pim_compiler.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/mnt/c/Users/Pojesh/Documents/OfficialWorks/CompilerDA3/Documents/Working/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable pim_compiler"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pim_compiler.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/pim_compiler.dir/build: pim_compiler
.PHONY : CMakeFiles/pim_compiler.dir/build

CMakeFiles/pim_compiler.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/pim_compiler.dir/cmake_clean.cmake
.PHONY : CMakeFiles/pim_compiler.dir/clean

CMakeFiles/pim_compiler.dir/depend:
	cd /mnt/c/Users/Pojesh/Documents/OfficialWorks/CompilerDA3/Documents/Working/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/Pojesh/Documents/OfficialWorks/CompilerDA3/Documents/Working /mnt/c/Users/Pojesh/Documents/OfficialWorks/CompilerDA3/Documents/Working /mnt/c/Users/Pojesh/Documents/OfficialWorks/CompilerDA3/Documents/Working/build /mnt/c/Users/Pojesh/Documents/OfficialWorks/CompilerDA3/Documents/Working/build /mnt/c/Users/Pojesh/Documents/OfficialWorks/CompilerDA3/Documents/Working/build/CMakeFiles/pim_compiler.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/pim_compiler.dir/depend

