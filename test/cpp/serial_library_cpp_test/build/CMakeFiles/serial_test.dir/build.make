# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/samuko/projects/easy_pid_motor_ctrl/test/cpp/serial_library_cpp_test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/samuko/projects/easy_pid_motor_ctrl/test/cpp/serial_library_cpp_test/build

# Include any dependencies generated for this target.
include CMakeFiles/serial_test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/serial_test.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/serial_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/serial_test.dir/flags.make

CMakeFiles/serial_test.dir/examples/serial_test.cpp.o: CMakeFiles/serial_test.dir/flags.make
CMakeFiles/serial_test.dir/examples/serial_test.cpp.o: ../examples/serial_test.cpp
CMakeFiles/serial_test.dir/examples/serial_test.cpp.o: CMakeFiles/serial_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/samuko/projects/easy_pid_motor_ctrl/test/cpp/serial_library_cpp_test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/serial_test.dir/examples/serial_test.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/serial_test.dir/examples/serial_test.cpp.o -MF CMakeFiles/serial_test.dir/examples/serial_test.cpp.o.d -o CMakeFiles/serial_test.dir/examples/serial_test.cpp.o -c /home/samuko/projects/easy_pid_motor_ctrl/test/cpp/serial_library_cpp_test/examples/serial_test.cpp

CMakeFiles/serial_test.dir/examples/serial_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/serial_test.dir/examples/serial_test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/samuko/projects/easy_pid_motor_ctrl/test/cpp/serial_library_cpp_test/examples/serial_test.cpp > CMakeFiles/serial_test.dir/examples/serial_test.cpp.i

CMakeFiles/serial_test.dir/examples/serial_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/serial_test.dir/examples/serial_test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/samuko/projects/easy_pid_motor_ctrl/test/cpp/serial_library_cpp_test/examples/serial_test.cpp -o CMakeFiles/serial_test.dir/examples/serial_test.cpp.s

# Object files for target serial_test
serial_test_OBJECTS = \
"CMakeFiles/serial_test.dir/examples/serial_test.cpp.o"

# External object files for target serial_test
serial_test_EXTERNAL_OBJECTS =

serial_test: CMakeFiles/serial_test.dir/examples/serial_test.cpp.o
serial_test: CMakeFiles/serial_test.dir/build.make
serial_test: libserial.a
serial_test: CMakeFiles/serial_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/samuko/projects/easy_pid_motor_ctrl/test/cpp/serial_library_cpp_test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable serial_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/serial_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/serial_test.dir/build: serial_test
.PHONY : CMakeFiles/serial_test.dir/build

CMakeFiles/serial_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/serial_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/serial_test.dir/clean

CMakeFiles/serial_test.dir/depend:
	cd /home/samuko/projects/easy_pid_motor_ctrl/test/cpp/serial_library_cpp_test/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/samuko/projects/easy_pid_motor_ctrl/test/cpp/serial_library_cpp_test /home/samuko/projects/easy_pid_motor_ctrl/test/cpp/serial_library_cpp_test /home/samuko/projects/easy_pid_motor_ctrl/test/cpp/serial_library_cpp_test/build /home/samuko/projects/easy_pid_motor_ctrl/test/cpp/serial_library_cpp_test/build /home/samuko/projects/easy_pid_motor_ctrl/test/cpp/serial_library_cpp_test/build/CMakeFiles/serial_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/serial_test.dir/depend

