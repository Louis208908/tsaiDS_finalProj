# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/louis/c_project/final_proj

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/louis/c_project/final_proj/build

# Include any dependencies generated for this target.
include CMakeFiles/map_lib.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/map_lib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/map_lib.dir/flags.make

CMakeFiles/map_lib.dir/include/map.cpp.o: CMakeFiles/map_lib.dir/flags.make
CMakeFiles/map_lib.dir/include/map.cpp.o: ../include/map.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/louis/c_project/final_proj/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/map_lib.dir/include/map.cpp.o"
	/usr/bin/x86_64-linux-gnu-g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/map_lib.dir/include/map.cpp.o -c /home/louis/c_project/final_proj/include/map.cpp

CMakeFiles/map_lib.dir/include/map.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/map_lib.dir/include/map.cpp.i"
	/usr/bin/x86_64-linux-gnu-g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/louis/c_project/final_proj/include/map.cpp > CMakeFiles/map_lib.dir/include/map.cpp.i

CMakeFiles/map_lib.dir/include/map.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/map_lib.dir/include/map.cpp.s"
	/usr/bin/x86_64-linux-gnu-g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/louis/c_project/final_proj/include/map.cpp -o CMakeFiles/map_lib.dir/include/map.cpp.s

# Object files for target map_lib
map_lib_OBJECTS = \
"CMakeFiles/map_lib.dir/include/map.cpp.o"

# External object files for target map_lib
map_lib_EXTERNAL_OBJECTS =

../include/lib/libmap_lib.a: CMakeFiles/map_lib.dir/include/map.cpp.o
../include/lib/libmap_lib.a: CMakeFiles/map_lib.dir/build.make
../include/lib/libmap_lib.a: CMakeFiles/map_lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/louis/c_project/final_proj/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library ../include/lib/libmap_lib.a"
	$(CMAKE_COMMAND) -P CMakeFiles/map_lib.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/map_lib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/map_lib.dir/build: ../include/lib/libmap_lib.a

.PHONY : CMakeFiles/map_lib.dir/build

CMakeFiles/map_lib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/map_lib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/map_lib.dir/clean

CMakeFiles/map_lib.dir/depend:
	cd /home/louis/c_project/final_proj/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/louis/c_project/final_proj /home/louis/c_project/final_proj /home/louis/c_project/final_proj/build /home/louis/c_project/final_proj/build /home/louis/c_project/final_proj/build/CMakeFiles/map_lib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/map_lib.dir/depend
