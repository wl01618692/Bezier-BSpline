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
CMAKE_SOURCE_DIR = /Users/chiayuanchang/Desktop/assignment

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/chiayuanchang/Desktop/assignment/cmake-build-debug

# Include any dependencies generated for this target.
include projects/skeleton_p2/CMakeFiles/run_p2.dir/depend.make

# Include the progress variables for this target.
include projects/skeleton_p2/CMakeFiles/run_p2.dir/progress.make

# Include the compile flags for this target's objects.
include projects/skeleton_p2/CMakeFiles/run_p2.dir/flags.make

projects/skeleton_p2/CMakeFiles/run_p2.dir/main.cpp.o: projects/skeleton_p2/CMakeFiles/run_p2.dir/flags.make
projects/skeleton_p2/CMakeFiles/run_p2.dir/main.cpp.o: ../projects/skeleton_p2/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/chiayuanchang/Desktop/assignment/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object projects/skeleton_p2/CMakeFiles/run_p2.dir/main.cpp.o"
	cd /Users/chiayuanchang/Desktop/assignment/cmake-build-debug/projects/skeleton_p2 && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/run_p2.dir/main.cpp.o -c /Users/chiayuanchang/Desktop/assignment/projects/skeleton_p2/main.cpp

projects/skeleton_p2/CMakeFiles/run_p2.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/run_p2.dir/main.cpp.i"
	cd /Users/chiayuanchang/Desktop/assignment/cmake-build-debug/projects/skeleton_p2 && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/chiayuanchang/Desktop/assignment/projects/skeleton_p2/main.cpp > CMakeFiles/run_p2.dir/main.cpp.i

projects/skeleton_p2/CMakeFiles/run_p2.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/run_p2.dir/main.cpp.s"
	cd /Users/chiayuanchang/Desktop/assignment/cmake-build-debug/projects/skeleton_p2 && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/chiayuanchang/Desktop/assignment/projects/skeleton_p2/main.cpp -o CMakeFiles/run_p2.dir/main.cpp.s

# Object files for target run_p2
run_p2_OBJECTS = \
"CMakeFiles/run_p2.dir/main.cpp.o"

# External object files for target run_p2
run_p2_EXTERNAL_OBJECTS =

run_p2: projects/skeleton_p2/CMakeFiles/run_p2.dir/main.cpp.o
run_p2: projects/skeleton_p2/CMakeFiles/run_p2.dir/build.make
run_p2: util/libutil-core-3.3.a
run_p2: imgui-1.79/libimgui-core-3.3.a
run_p2: glad-core-3.3/libglad-core-3.3.a
run_p2: /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd
run_p2: /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd
run_p2: glfw-3.3.2/src/libglfw3.a
run_p2: projects/skeleton_p2/CMakeFiles/run_p2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/chiayuanchang/Desktop/assignment/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../run_p2"
	cd /Users/chiayuanchang/Desktop/assignment/cmake-build-debug/projects/skeleton_p2 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/run_p2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
projects/skeleton_p2/CMakeFiles/run_p2.dir/build: run_p2

.PHONY : projects/skeleton_p2/CMakeFiles/run_p2.dir/build

projects/skeleton_p2/CMakeFiles/run_p2.dir/clean:
	cd /Users/chiayuanchang/Desktop/assignment/cmake-build-debug/projects/skeleton_p2 && $(CMAKE_COMMAND) -P CMakeFiles/run_p2.dir/cmake_clean.cmake
.PHONY : projects/skeleton_p2/CMakeFiles/run_p2.dir/clean

projects/skeleton_p2/CMakeFiles/run_p2.dir/depend:
	cd /Users/chiayuanchang/Desktop/assignment/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/chiayuanchang/Desktop/assignment /Users/chiayuanchang/Desktop/assignment/projects/skeleton_p2 /Users/chiayuanchang/Desktop/assignment/cmake-build-debug /Users/chiayuanchang/Desktop/assignment/cmake-build-debug/projects/skeleton_p2 /Users/chiayuanchang/Desktop/assignment/cmake-build-debug/projects/skeleton_p2/CMakeFiles/run_p2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : projects/skeleton_p2/CMakeFiles/run_p2.dir/depend

