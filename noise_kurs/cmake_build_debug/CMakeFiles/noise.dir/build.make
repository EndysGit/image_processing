# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.10.1/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.10.1/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Volumes/Date/ProgrammingProjects/cppFolder/image_proc/noise

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Volumes/Date/ProgrammingProjects/cppFolder/image_proc/noise/cmake_build_debug

# Include any dependencies generated for this target.
include CMakeFiles/noise.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/noise.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/noise.dir/flags.make

CMakeFiles/noise.dir/main.cpp.o: CMakeFiles/noise.dir/flags.make
CMakeFiles/noise.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Volumes/Date/ProgrammingProjects/cppFolder/image_proc/noise/cmake_build_debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/noise.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/noise.dir/main.cpp.o -c /Volumes/Date/ProgrammingProjects/cppFolder/image_proc/noise/main.cpp

CMakeFiles/noise.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/noise.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Volumes/Date/ProgrammingProjects/cppFolder/image_proc/noise/main.cpp > CMakeFiles/noise.dir/main.cpp.i

CMakeFiles/noise.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/noise.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Volumes/Date/ProgrammingProjects/cppFolder/image_proc/noise/main.cpp -o CMakeFiles/noise.dir/main.cpp.s

CMakeFiles/noise.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/noise.dir/main.cpp.o.requires

CMakeFiles/noise.dir/main.cpp.o.provides: CMakeFiles/noise.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/noise.dir/build.make CMakeFiles/noise.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/noise.dir/main.cpp.o.provides

CMakeFiles/noise.dir/main.cpp.o.provides.build: CMakeFiles/noise.dir/main.cpp.o


CMakeFiles/noise.dir/FastNoise.cpp.o: CMakeFiles/noise.dir/flags.make
CMakeFiles/noise.dir/FastNoise.cpp.o: ../FastNoise.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Volumes/Date/ProgrammingProjects/cppFolder/image_proc/noise/cmake_build_debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/noise.dir/FastNoise.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/noise.dir/FastNoise.cpp.o -c /Volumes/Date/ProgrammingProjects/cppFolder/image_proc/noise/FastNoise.cpp

CMakeFiles/noise.dir/FastNoise.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/noise.dir/FastNoise.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Volumes/Date/ProgrammingProjects/cppFolder/image_proc/noise/FastNoise.cpp > CMakeFiles/noise.dir/FastNoise.cpp.i

CMakeFiles/noise.dir/FastNoise.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/noise.dir/FastNoise.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Volumes/Date/ProgrammingProjects/cppFolder/image_proc/noise/FastNoise.cpp -o CMakeFiles/noise.dir/FastNoise.cpp.s

CMakeFiles/noise.dir/FastNoise.cpp.o.requires:

.PHONY : CMakeFiles/noise.dir/FastNoise.cpp.o.requires

CMakeFiles/noise.dir/FastNoise.cpp.o.provides: CMakeFiles/noise.dir/FastNoise.cpp.o.requires
	$(MAKE) -f CMakeFiles/noise.dir/build.make CMakeFiles/noise.dir/FastNoise.cpp.o.provides.build
.PHONY : CMakeFiles/noise.dir/FastNoise.cpp.o.provides

CMakeFiles/noise.dir/FastNoise.cpp.o.provides.build: CMakeFiles/noise.dir/FastNoise.cpp.o


# Object files for target noise
noise_OBJECTS = \
"CMakeFiles/noise.dir/main.cpp.o" \
"CMakeFiles/noise.dir/FastNoise.cpp.o"

# External object files for target noise
noise_EXTERNAL_OBJECTS =

noise: CMakeFiles/noise.dir/main.cpp.o
noise: CMakeFiles/noise.dir/FastNoise.cpp.o
noise: CMakeFiles/noise.dir/build.make
noise: /usr/local/lib/libopencv_highgui.3.4.0.dylib
noise: /usr/local/lib/libopencv_videoio.3.4.0.dylib
noise: /usr/local/lib/libopencv_imgcodecs.3.4.0.dylib
noise: /usr/local/lib/libopencv_imgproc.3.4.0.dylib
noise: /usr/local/lib/libopencv_core.3.4.0.dylib
noise: CMakeFiles/noise.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Volumes/Date/ProgrammingProjects/cppFolder/image_proc/noise/cmake_build_debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable noise"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/noise.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/noise.dir/build: noise

.PHONY : CMakeFiles/noise.dir/build

CMakeFiles/noise.dir/requires: CMakeFiles/noise.dir/main.cpp.o.requires
CMakeFiles/noise.dir/requires: CMakeFiles/noise.dir/FastNoise.cpp.o.requires

.PHONY : CMakeFiles/noise.dir/requires

CMakeFiles/noise.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/noise.dir/cmake_clean.cmake
.PHONY : CMakeFiles/noise.dir/clean

CMakeFiles/noise.dir/depend:
	cd /Volumes/Date/ProgrammingProjects/cppFolder/image_proc/noise/cmake_build_debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Volumes/Date/ProgrammingProjects/cppFolder/image_proc/noise /Volumes/Date/ProgrammingProjects/cppFolder/image_proc/noise /Volumes/Date/ProgrammingProjects/cppFolder/image_proc/noise/cmake_build_debug /Volumes/Date/ProgrammingProjects/cppFolder/image_proc/noise/cmake_build_debug /Volumes/Date/ProgrammingProjects/cppFolder/image_proc/noise/cmake_build_debug/CMakeFiles/noise.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/noise.dir/depend

