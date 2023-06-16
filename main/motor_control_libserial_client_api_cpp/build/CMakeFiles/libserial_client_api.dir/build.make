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
CMAKE_SOURCE_DIR = /home/samuko/projects/easy_pid_motor_ctrl/main/motor_control_libserial_client_api_cpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/samuko/projects/easy_pid_motor_ctrl/main/motor_control_libserial_client_api_cpp/build

# Include any dependencies generated for this target.
include CMakeFiles/libserial_client_api.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/libserial_client_api.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/libserial_client_api.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/libserial_client_api.dir/flags.make

CMakeFiles/libserial_client_api.dir/examples/libserial_client_api.cpp.o: CMakeFiles/libserial_client_api.dir/flags.make
CMakeFiles/libserial_client_api.dir/examples/libserial_client_api.cpp.o: ../examples/libserial_client_api.cpp
CMakeFiles/libserial_client_api.dir/examples/libserial_client_api.cpp.o: CMakeFiles/libserial_client_api.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/samuko/projects/easy_pid_motor_ctrl/main/motor_control_libserial_client_api_cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/libserial_client_api.dir/examples/libserial_client_api.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/libserial_client_api.dir/examples/libserial_client_api.cpp.o -MF CMakeFiles/libserial_client_api.dir/examples/libserial_client_api.cpp.o.d -o CMakeFiles/libserial_client_api.dir/examples/libserial_client_api.cpp.o -c /home/samuko/projects/easy_pid_motor_ctrl/main/motor_control_libserial_client_api_cpp/examples/libserial_client_api.cpp

CMakeFiles/libserial_client_api.dir/examples/libserial_client_api.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libserial_client_api.dir/examples/libserial_client_api.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/samuko/projects/easy_pid_motor_ctrl/main/motor_control_libserial_client_api_cpp/examples/libserial_client_api.cpp > CMakeFiles/libserial_client_api.dir/examples/libserial_client_api.cpp.i

CMakeFiles/libserial_client_api.dir/examples/libserial_client_api.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libserial_client_api.dir/examples/libserial_client_api.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/samuko/projects/easy_pid_motor_ctrl/main/motor_control_libserial_client_api_cpp/examples/libserial_client_api.cpp -o CMakeFiles/libserial_client_api.dir/examples/libserial_client_api.cpp.s

# Object files for target libserial_client_api
libserial_client_api_OBJECTS = \
"CMakeFiles/libserial_client_api.dir/examples/libserial_client_api.cpp.o"

# External object files for target libserial_client_api
libserial_client_api_EXTERNAL_OBJECTS =

libserial_client_api: CMakeFiles/libserial_client_api.dir/examples/libserial_client_api.cpp.o
libserial_client_api: CMakeFiles/libserial_client_api.dir/build.make
libserial_client_api: CMakeFiles/libserial_client_api.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/samuko/projects/easy_pid_motor_ctrl/main/motor_control_libserial_client_api_cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable libserial_client_api"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/libserial_client_api.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/libserial_client_api.dir/build: libserial_client_api
.PHONY : CMakeFiles/libserial_client_api.dir/build

CMakeFiles/libserial_client_api.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/libserial_client_api.dir/cmake_clean.cmake
.PHONY : CMakeFiles/libserial_client_api.dir/clean

CMakeFiles/libserial_client_api.dir/depend:
	cd /home/samuko/projects/easy_pid_motor_ctrl/main/motor_control_libserial_client_api_cpp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/samuko/projects/easy_pid_motor_ctrl/main/motor_control_libserial_client_api_cpp /home/samuko/projects/easy_pid_motor_ctrl/main/motor_control_libserial_client_api_cpp /home/samuko/projects/easy_pid_motor_ctrl/main/motor_control_libserial_client_api_cpp/build /home/samuko/projects/easy_pid_motor_ctrl/main/motor_control_libserial_client_api_cpp/build /home/samuko/projects/easy_pid_motor_ctrl/main/motor_control_libserial_client_api_cpp/build/CMakeFiles/libserial_client_api.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/libserial_client_api.dir/depend
