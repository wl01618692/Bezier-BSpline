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
include demo/d3_simple_shader/CMakeFiles/d3_simple_shader_embeded.dir/depend.make

# Include the progress variables for this target.
include demo/d3_simple_shader/CMakeFiles/d3_simple_shader_embeded.dir/progress.make

# Include the compile flags for this target's objects.
include demo/d3_simple_shader/CMakeFiles/d3_simple_shader_embeded.dir/flags.make

demo/d3_simple_shader/CMakeFiles/d3_simple_shader_embeded.dir/main_embeded.cpp.o: demo/d3_simple_shader/CMakeFiles/d3_simple_shader_embeded.dir/flags.make
demo/d3_simple_shader/CMakeFiles/d3_simple_shader_embeded.dir/main_embeded.cpp.o: ../demo/d3_simple_shader/main_embeded.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/chiayuanchang/Desktop/p4/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object demo/d3_simple_shader/CMakeFiles/d3_simple_shader_embeded.dir/main_embeded.cpp.o"
	cd /Users/chiayuanchang/Desktop/p4/cmake-build-debug/demo/d3_simple_shader && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/d3_simple_shader_embeded.dir/main_embeded.cpp.o -c /Users/chiayuanchang/Desktop/p4/demo/d3_simple_shader/main_embeded.cpp

demo/d3_simple_shader/CMakeFiles/d3_simple_shader_embeded.dir/main_embeded.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/d3_simple_shader_embeded.dir/main_embeded.cpp.i"
	cd /Users/chiayuanchang/Desktop/p4/cmake-build-debug/demo/d3_simple_shader && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/chiayuanchang/Desktop/p4/demo/d3_simple_shader/main_embeded.cpp > CMakeFiles/d3_simple_shader_embeded.dir/main_embeded.cpp.i

demo/d3_simple_shader/CMakeFiles/d3_simple_shader_embeded.dir/main_embeded.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/d3_simple_shader_embeded.dir/main_embeded.cpp.s"
	cd /Users/chiayuanchang/Desktop/p4/cmake-build-debug/demo/d3_simple_shader && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/chiayuanchang/Desktop/p4/demo/d3_simple_shader/main_embeded.cpp -o CMakeFiles/d3_simple_shader_embeded.dir/main_embeded.cpp.s

# Object files for target d3_simple_shader_embeded
d3_simple_shader_embeded_OBJECTS = \
"CMakeFiles/d3_simple_shader_embeded.dir/main_embeded.cpp.o"

# External object files for target d3_simple_shader_embeded
d3_simple_shader_embeded_EXTERNAL_OBJECTS =

d3_simple_shader_embeded: demo/d3_simple_shader/CMakeFiles/d3_simple_shader_embeded.dir/main_embeded.cpp.o
d3_simple_shader_embeded: demo/d3_simple_shader/CMakeFiles/d3_simple_shader_embeded.dir/build.make
d3_simple_shader_embeded: util/libutil-core-3.3.a
d3_simple_shader_embeded: imgui-1.79/libimgui-core-3.3.a
d3_simple_shader_embeded: glad-core-3.3/libglad-core-3.3.a
d3_simple_shader_embeded: /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd
d3_simple_shader_embeded: /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd
d3_simple_shader_embeded: glfw-3.3.2/src/libglfw3.a
d3_simple_shader_embeded: demo/d3_simple_shader/CMakeFiles/d3_simple_shader_embeded.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/chiayuanchang/Desktop/p4/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../d3_simple_shader_embeded"
	cd /Users/chiayuanchang/Desktop/p4/cmake-build-debug/demo/d3_simple_shader && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/d3_simple_shader_embeded.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
demo/d3_simple_shader/CMakeFiles/d3_simple_shader_embeded.dir/build: d3_simple_shader_embeded

.PHONY : demo/d3_simple_shader/CMakeFiles/d3_simple_shader_embeded.dir/build

demo/d3_simple_shader/CMakeFiles/d3_simple_shader_embeded.dir/clean:
	cd /Users/chiayuanchang/Desktop/p4/cmake-build-debug/demo/d3_simple_shader && $(CMAKE_COMMAND) -P CMakeFiles/d3_simple_shader_embeded.dir/cmake_clean.cmake
.PHONY : demo/d3_simple_shader/CMakeFiles/d3_simple_shader_embeded.dir/clean

demo/d3_simple_shader/CMakeFiles/d3_simple_shader_embeded.dir/depend:
	cd /Users/chiayuanchang/Desktop/p4/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/chiayuanchang/Desktop/p4 /Users/chiayuanchang/Desktop/p4/demo/d3_simple_shader /Users/chiayuanchang/Desktop/p4/cmake-build-debug /Users/chiayuanchang/Desktop/p4/cmake-build-debug/demo/d3_simple_shader /Users/chiayuanchang/Desktop/p4/cmake-build-debug/demo/d3_simple_shader/CMakeFiles/d3_simple_shader_embeded.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : demo/d3_simple_shader/CMakeFiles/d3_simple_shader_embeded.dir/depend

