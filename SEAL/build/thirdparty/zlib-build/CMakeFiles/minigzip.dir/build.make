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
CMAKE_SOURCE_DIR = /home/wentao/workspace/wentao/SmartAffair/SEAL

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/wentao/workspace/wentao/SmartAffair/SEAL/build

# Include any dependencies generated for this target.
include thirdparty/zlib-build/CMakeFiles/minigzip.dir/depend.make

# Include the progress variables for this target.
include thirdparty/zlib-build/CMakeFiles/minigzip.dir/progress.make

# Include the compile flags for this target's objects.
include thirdparty/zlib-build/CMakeFiles/minigzip.dir/flags.make

thirdparty/zlib-build/CMakeFiles/minigzip.dir/test/minigzip.o: thirdparty/zlib-build/CMakeFiles/minigzip.dir/flags.make
thirdparty/zlib-build/CMakeFiles/minigzip.dir/test/minigzip.o: thirdparty/zlib-src/test/minigzip.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wentao/workspace/wentao/SmartAffair/SEAL/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object thirdparty/zlib-build/CMakeFiles/minigzip.dir/test/minigzip.o"
	cd /home/wentao/workspace/wentao/SmartAffair/SEAL/build/thirdparty/zlib-build && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/minigzip.dir/test/minigzip.o   -c /home/wentao/workspace/wentao/SmartAffair/SEAL/build/thirdparty/zlib-src/test/minigzip.c

thirdparty/zlib-build/CMakeFiles/minigzip.dir/test/minigzip.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/minigzip.dir/test/minigzip.i"
	cd /home/wentao/workspace/wentao/SmartAffair/SEAL/build/thirdparty/zlib-build && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/wentao/workspace/wentao/SmartAffair/SEAL/build/thirdparty/zlib-src/test/minigzip.c > CMakeFiles/minigzip.dir/test/minigzip.i

thirdparty/zlib-build/CMakeFiles/minigzip.dir/test/minigzip.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/minigzip.dir/test/minigzip.s"
	cd /home/wentao/workspace/wentao/SmartAffair/SEAL/build/thirdparty/zlib-build && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/wentao/workspace/wentao/SmartAffair/SEAL/build/thirdparty/zlib-src/test/minigzip.c -o CMakeFiles/minigzip.dir/test/minigzip.s

# Object files for target minigzip
minigzip_OBJECTS = \
"CMakeFiles/minigzip.dir/test/minigzip.o"

# External object files for target minigzip
minigzip_EXTERNAL_OBJECTS =

bin/minigzip: thirdparty/zlib-build/CMakeFiles/minigzip.dir/test/minigzip.o
bin/minigzip: thirdparty/zlib-build/CMakeFiles/minigzip.dir/build.make
bin/minigzip: lib/libz.so.1.2.13
bin/minigzip: thirdparty/zlib-build/CMakeFiles/minigzip.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/wentao/workspace/wentao/SmartAffair/SEAL/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ../../bin/minigzip"
	cd /home/wentao/workspace/wentao/SmartAffair/SEAL/build/thirdparty/zlib-build && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/minigzip.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
thirdparty/zlib-build/CMakeFiles/minigzip.dir/build: bin/minigzip

.PHONY : thirdparty/zlib-build/CMakeFiles/minigzip.dir/build

thirdparty/zlib-build/CMakeFiles/minigzip.dir/clean:
	cd /home/wentao/workspace/wentao/SmartAffair/SEAL/build/thirdparty/zlib-build && $(CMAKE_COMMAND) -P CMakeFiles/minigzip.dir/cmake_clean.cmake
.PHONY : thirdparty/zlib-build/CMakeFiles/minigzip.dir/clean

thirdparty/zlib-build/CMakeFiles/minigzip.dir/depend:
	cd /home/wentao/workspace/wentao/SmartAffair/SEAL/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wentao/workspace/wentao/SmartAffair/SEAL /home/wentao/workspace/wentao/SmartAffair/SEAL/build/thirdparty/zlib-src /home/wentao/workspace/wentao/SmartAffair/SEAL/build /home/wentao/workspace/wentao/SmartAffair/SEAL/build/thirdparty/zlib-build /home/wentao/workspace/wentao/SmartAffair/SEAL/build/thirdparty/zlib-build/CMakeFiles/minigzip.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : thirdparty/zlib-build/CMakeFiles/minigzip.dir/depend

