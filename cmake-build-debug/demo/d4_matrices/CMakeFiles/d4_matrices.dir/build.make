# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/chiayuanchang/Desktop/p4

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/chiayuanchang/Desktop/p4/cmake-build-debug

# Include any dependencies generated for this target.
include demo/d4_matrices/CMakeFiles/d4_matrices.dir/depend.make

# Include the progress variables for this target.
include demo/d4_matrices/CMakeFiles/d4_matrices.dir/progress.make

# Include the compile flags for this target's objects.
include demo/d4_matrices/CMakeFiles/d4_matrices.dir/flags.make

demo/d4_matrices/CMakeFiles/d4_matrices.dir/main.cpp.o: demo/d4_matrices/CMakeFiles/d4_matrices.dir/flags.make
demo/d4_matrices/CMakeFiles/d4_matrices.dir/main.cpp.o: ../demo/d4_matrices/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/chiayuanchang/Desktop/p4/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object demo/d4_matrices/CMakeFiles/d4_matrices.dir/main.cpp.o"
	cd /Users/chiayuanchang/Desktop/p4/cmake-build-debug/demo/d4_matrices && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/d4_matrices.dir/main.cpp.o -c /Users/chiayuanchang/Desktop/p4/demo/d4_matrices/main.cpp

demo/d4_matrices/CMakeFiles/d4_matrices.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/d4_matrices.dir/main.cpp.i"
	cd /Users/chiayuanchang/Desktop/p4/cmake-build-debug/demo/d4_matrices && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/chiayuanchang/Desktop/p4/demo/d4_matrices/main.cpp > CMakeFiles/d4_matrices.dir/main.cpp.i

demo/d4_matrices/CMakeFiles/d4_matrices.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/d4_matrices.dir/main.cpp.s"
	cd /Users/chiayuanchang/Desktop/p4/cmake-build-debug/demo/d4_matrices && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/chiayuanchang/Desktop/p4/demo/d4_matrices/main.cpp -o CMakeFiles/d4_matrices.dir/main.cpp.s

# Object files for target d4_matrices
d4_matrices_OBJECTS = \
"CMakeFiles/d4_matrices.dir/main.cpp.o"

# External object files for target d4_matrices
d4_matrices_EXTERNAL_OBJECTS =

d4_matrices: demo/d4_matrices/CMakeFiles/d4_matrices.dir/main.cpp.o
d4_matrices: demo/d4_matrices/CMakeFiles/d4_matrices.dir/build.make
d4_matrices: util/libutil-core-3.3.a
d4_matrices: imgui-1.79/libimgui-core-3.3.a
d4_matrices: glad-core-3.3/libglad-core-3.3.a
d4_matrices: /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd
d4_matrices: /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd
d4_matrices: glfw-3.3.2/src/libglfw3.a
d4_matrices: demo/d4_matrices/CMakeFiles/d4_matrices.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/chiayuanchang/Desktop/p4/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../d4_matrices"
	cd /Users/chiayuanchang/Desktop/p4/cmake-build-debug/demo/d4_matrices && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/d4_matrices.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
demo/d4_matrices/CMakeFiles/d4_matrices.dir/build: d4_matrices

.PHONY : demo/d4_matrices/CMakeFiles/d4_matrices.dir/build

demo/d4_matrices/CMakeFiles/d4_matrices.dir/clean:
	cd /Users/chiayuanchang/Desktop/p4/cmake-build-debug/demo/d4_matrices && $(CMAKE_COMMAND) -P CMakeFiles/d4_matrices.dir/cmake_clean.cmake
.PHONY : demo/d4_matrices/CMakeFiles/d4_matrices.dir/clean

demo/d4_matrices/CMakeFiles/d4_matrices.dir/depend:
	cd /Users/chiayuanchang/Desktop/p4/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/chiayuanchang/Desktop/p4 /Users/chiayuanchang/Desktop/p4/demo/d4_matrices /Users/chiayuanchang/Desktop/p4/cmake-build-debug /Users/chiayuanchang/Desktop/p4/cmake-build-debug/demo/d4_matrices /Users/chiayuanchang/Desktop/p4/cmake-build-debug/demo/d4_matrices/CMakeFiles/d4_matrices.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : demo/d4_matrices/CMakeFiles/d4_matrices.dir/depend
