# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /root/cmake_practice/tencentdays

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/cmake_practice/tencentdays/build

# Include any dependencies generated for this target.
include try_gdb/CMakeFiles/pdb_try.dir/depend.make

# Include the progress variables for this target.
include try_gdb/CMakeFiles/pdb_try.dir/progress.make

# Include the compile flags for this target's objects.
include try_gdb/CMakeFiles/pdb_try.dir/flags.make

try_gdb/CMakeFiles/pdb_try.dir/src/gdb_try.cpp.o: try_gdb/CMakeFiles/pdb_try.dir/flags.make
try_gdb/CMakeFiles/pdb_try.dir/src/gdb_try.cpp.o: ../try_gdb/src/gdb_try.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /root/cmake_practice/tencentdays/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object try_gdb/CMakeFiles/pdb_try.dir/src/gdb_try.cpp.o"
	cd /root/cmake_practice/tencentdays/build/try_gdb && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/pdb_try.dir/src/gdb_try.cpp.o -c /root/cmake_practice/tencentdays/try_gdb/src/gdb_try.cpp

try_gdb/CMakeFiles/pdb_try.dir/src/gdb_try.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pdb_try.dir/src/gdb_try.cpp.i"
	cd /root/cmake_practice/tencentdays/build/try_gdb && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /root/cmake_practice/tencentdays/try_gdb/src/gdb_try.cpp > CMakeFiles/pdb_try.dir/src/gdb_try.cpp.i

try_gdb/CMakeFiles/pdb_try.dir/src/gdb_try.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pdb_try.dir/src/gdb_try.cpp.s"
	cd /root/cmake_practice/tencentdays/build/try_gdb && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /root/cmake_practice/tencentdays/try_gdb/src/gdb_try.cpp -o CMakeFiles/pdb_try.dir/src/gdb_try.cpp.s

try_gdb/CMakeFiles/pdb_try.dir/src/gdb_try.cpp.o.requires:
.PHONY : try_gdb/CMakeFiles/pdb_try.dir/src/gdb_try.cpp.o.requires

try_gdb/CMakeFiles/pdb_try.dir/src/gdb_try.cpp.o.provides: try_gdb/CMakeFiles/pdb_try.dir/src/gdb_try.cpp.o.requires
	$(MAKE) -f try_gdb/CMakeFiles/pdb_try.dir/build.make try_gdb/CMakeFiles/pdb_try.dir/src/gdb_try.cpp.o.provides.build
.PHONY : try_gdb/CMakeFiles/pdb_try.dir/src/gdb_try.cpp.o.provides

try_gdb/CMakeFiles/pdb_try.dir/src/gdb_try.cpp.o.provides.build: try_gdb/CMakeFiles/pdb_try.dir/src/gdb_try.cpp.o

# Object files for target pdb_try
pdb_try_OBJECTS = \
"CMakeFiles/pdb_try.dir/src/gdb_try.cpp.o"

# External object files for target pdb_try
pdb_try_EXTERNAL_OBJECTS =

../lib/libpdb_try.so: try_gdb/CMakeFiles/pdb_try.dir/src/gdb_try.cpp.o
../lib/libpdb_try.so: try_gdb/CMakeFiles/pdb_try.dir/build.make
../lib/libpdb_try.so: try_gdb/CMakeFiles/pdb_try.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared library ../../lib/libpdb_try.so"
	cd /root/cmake_practice/tencentdays/build/try_gdb && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pdb_try.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
try_gdb/CMakeFiles/pdb_try.dir/build: ../lib/libpdb_try.so
.PHONY : try_gdb/CMakeFiles/pdb_try.dir/build

try_gdb/CMakeFiles/pdb_try.dir/requires: try_gdb/CMakeFiles/pdb_try.dir/src/gdb_try.cpp.o.requires
.PHONY : try_gdb/CMakeFiles/pdb_try.dir/requires

try_gdb/CMakeFiles/pdb_try.dir/clean:
	cd /root/cmake_practice/tencentdays/build/try_gdb && $(CMAKE_COMMAND) -P CMakeFiles/pdb_try.dir/cmake_clean.cmake
.PHONY : try_gdb/CMakeFiles/pdb_try.dir/clean

try_gdb/CMakeFiles/pdb_try.dir/depend:
	cd /root/cmake_practice/tencentdays/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/cmake_practice/tencentdays /root/cmake_practice/tencentdays/try_gdb /root/cmake_practice/tencentdays/build /root/cmake_practice/tencentdays/build/try_gdb /root/cmake_practice/tencentdays/build/try_gdb/CMakeFiles/pdb_try.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : try_gdb/CMakeFiles/pdb_try.dir/depend
