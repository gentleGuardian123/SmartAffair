# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/wentao/workspace/wentao/SmartAffair

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/wentao/workspace/wentao/SmartAffair/build

# Include any dependencies generated for this target.
include native/examples/CMakeFiles/examples.dir/depend.make

# Include the progress variables for this target.
include native/examples/CMakeFiles/examples.dir/progress.make

# Include the compile flags for this target's objects.
include native/examples/CMakeFiles/examples.dir/flags.make

native/examples/CMakeFiles/examples.dir/1_ckks_example.cpp.o: native/examples/CMakeFiles/examples.dir/flags.make
native/examples/CMakeFiles/examples.dir/1_ckks_example.cpp.o: ../native/examples/1_ckks_example.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wentao/workspace/wentao/SmartAffair/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object native/examples/CMakeFiles/examples.dir/1_ckks_example.cpp.o"
	cd /home/wentao/workspace/wentao/SmartAffair/build/native/examples && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/examples.dir/1_ckks_example.cpp.o -c /home/wentao/workspace/wentao/SmartAffair/native/examples/1_ckks_example.cpp

native/examples/CMakeFiles/examples.dir/1_ckks_example.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/examples.dir/1_ckks_example.cpp.i"
	cd /home/wentao/workspace/wentao/SmartAffair/build/native/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wentao/workspace/wentao/SmartAffair/native/examples/1_ckks_example.cpp > CMakeFiles/examples.dir/1_ckks_example.cpp.i

native/examples/CMakeFiles/examples.dir/1_ckks_example.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/examples.dir/1_ckks_example.cpp.s"
	cd /home/wentao/workspace/wentao/SmartAffair/build/native/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wentao/workspace/wentao/SmartAffair/native/examples/1_ckks_example.cpp -o CMakeFiles/examples.dir/1_ckks_example.cpp.s

# Object files for target examples
examples_OBJECTS = \
"CMakeFiles/examples.dir/1_ckks_example.cpp.o"

# External object files for target examples
examples_EXTERNAL_OBJECTS =

native/examples/bin/examples: native/examples/CMakeFiles/examples.dir/1_ckks_example.cpp.o
native/examples/bin/examples: native/examples/CMakeFiles/examples.dir/build.make
native/examples/bin/examples: ../libs/lib/libseal-4.1.a
native/examples/bin/examples: native/examples/CMakeFiles/examples.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/wentao/workspace/wentao/SmartAffair/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/examples"
	cd /home/wentao/workspace/wentao/SmartAffair/build/native/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/examples.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
native/examples/CMakeFiles/examples.dir/build: native/examples/bin/examples

.PHONY : native/examples/CMakeFiles/examples.dir/build

native/examples/CMakeFiles/examples.dir/clean:
	cd /home/wentao/workspace/wentao/SmartAffair/build/native/examples && $(CMAKE_COMMAND) -P CMakeFiles/examples.dir/cmake_clean.cmake
.PHONY : native/examples/CMakeFiles/examples.dir/clean

native/examples/CMakeFiles/examples.dir/depend:
	cd /home/wentao/workspace/wentao/SmartAffair/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wentao/workspace/wentao/SmartAffair /home/wentao/workspace/wentao/SmartAffair/native/examples /home/wentao/workspace/wentao/SmartAffair/build /home/wentao/workspace/wentao/SmartAffair/build/native/examples /home/wentao/workspace/wentao/SmartAffair/build/native/examples/CMakeFiles/examples.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : native/examples/CMakeFiles/examples.dir/depend

