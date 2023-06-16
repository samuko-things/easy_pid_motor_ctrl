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
CMAKE_SOURCE_DIR = /home/samuko/projects/easy_pid_motor_ctrl/main/motor_control_myserial_client_api_cpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/samuko/projects/easy_pid_motor_ctrl/main/motor_control_myserial_client_api_cpp/build

# Include any dependencies generated for this target.
include CMakeFiles/myserial.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/myserial.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/myserial.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/myserial.dir/flags.make

CMakeFiles/myserial.dir/src/serial.cc.o: CMakeFiles/myserial.dir/flags.make
CMakeFiles/myserial.dir/src/serial.cc.o: ../src/serial.cc
CMakeFiles/myserial.dir/src/serial.cc.o: CMakeFiles/myserial.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/samuko/projects/easy_pid_motor_ctrl/main/motor_control_myserial_client_api_cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/myserial.dir/src/serial.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/myserial.dir/src/serial.cc.o -MF CMakeFiles/myserial.dir/src/serial.cc.o.d -o CMakeFiles/myserial.dir/src/serial.cc.o -c /home/samuko/projects/easy_pid_motor_ctrl/main/motor_control_myserial_client_api_cpp/src/serial.cc

CMakeFiles/myserial.dir/src/serial.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/myserial.dir/src/serial.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/samuko/projects/easy_pid_motor_ctrl/main/motor_control_myserial_client_api_cpp/src/serial.cc > CMakeFiles/myserial.dir/src/serial.cc.i

CMakeFiles/myserial.dir/src/serial.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/myserial.dir/src/serial.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/samuko/projects/easy_pid_motor_ctrl/main/motor_control_myserial_client_api_cpp/src/serial.cc -o CMakeFiles/myserial.dir/src/serial.cc.s

CMakeFiles/myserial.dir/src/impl/unix.cc.o: CMakeFiles/myserial.dir/flags.make
CMakeFiles/myserial.dir/src/impl/unix.cc.o: ../src/impl/unix.cc
CMakeFiles/myserial.dir/src/impl/unix.cc.o: CMakeFiles/myserial.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/samuko/projects/easy_pid_motor_ctrl/main/motor_control_myserial_client_api_cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/myserial.dir/src/impl/unix.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/myserial.dir/src/impl/unix.cc.o -MF CMakeFiles/myserial.dir/src/impl/unix.cc.o.d -o CMakeFiles/myserial.dir/src/impl/unix.cc.o -c /home/samuko/projects/easy_pid_motor_ctrl/main/motor_control_myserial_client_api_cpp/src/impl/unix.cc

CMakeFiles/myserial.dir/src/impl/unix.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/myserial.dir/src/impl/unix.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/samuko/projects/easy_pid_motor_ctrl/main/motor_control_myserial_client_api_cpp/src/impl/unix.cc > CMakeFiles/myserial.dir/src/impl/unix.cc.i

CMakeFiles/myserial.dir/src/impl/unix.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/myserial.dir/src/impl/unix.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/samuko/projects/easy_pid_motor_ctrl/main/motor_control_myserial_client_api_cpp/src/impl/unix.cc -o CMakeFiles/myserial.dir/src/impl/unix.cc.s

CMakeFiles/myserial.dir/src/impl/list_ports/list_ports_linux.cc.o: CMakeFiles/myserial.dir/flags.make
CMakeFiles/myserial.dir/src/impl/list_ports/list_ports_linux.cc.o: ../src/impl/list_ports/list_ports_linux.cc
CMakeFiles/myserial.dir/src/impl/list_ports/list_ports_linux.cc.o: CMakeFiles/myserial.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/samuko/projects/easy_pid_motor_ctrl/main/motor_control_myserial_client_api_cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/myserial.dir/src/impl/list_ports/list_ports_linux.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/myserial.dir/src/impl/list_ports/list_ports_linux.cc.o -MF CMakeFiles/myserial.dir/src/impl/list_ports/list_ports_linux.cc.o.d -o CMakeFiles/myserial.dir/src/impl/list_ports/list_ports_linux.cc.o -c /home/samuko/projects/easy_pid_motor_ctrl/main/motor_control_myserial_client_api_cpp/src/impl/list_ports/list_ports_linux.cc

CMakeFiles/myserial.dir/src/impl/list_ports/list_ports_linux.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/myserial.dir/src/impl/list_ports/list_ports_linux.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/samuko/projects/easy_pid_motor_ctrl/main/motor_control_myserial_client_api_cpp/src/impl/list_ports/list_ports_linux.cc > CMakeFiles/myserial.dir/src/impl/list_ports/list_ports_linux.cc.i

CMakeFiles/myserial.dir/src/impl/list_ports/list_ports_linux.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/myserial.dir/src/impl/list_ports/list_ports_linux.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/samuko/projects/easy_pid_motor_ctrl/main/motor_control_myserial_client_api_cpp/src/impl/list_ports/list_ports_linux.cc -o CMakeFiles/myserial.dir/src/impl/list_ports/list_ports_linux.cc.s

# Object files for target myserial
myserial_OBJECTS = \
"CMakeFiles/myserial.dir/src/serial.cc.o" \
"CMakeFiles/myserial.dir/src/impl/unix.cc.o" \
"CMakeFiles/myserial.dir/src/impl/list_ports/list_ports_linux.cc.o"

# External object files for target myserial
myserial_EXTERNAL_OBJECTS =

libmyserial.a: CMakeFiles/myserial.dir/src/serial.cc.o
libmyserial.a: CMakeFiles/myserial.dir/src/impl/unix.cc.o
libmyserial.a: CMakeFiles/myserial.dir/src/impl/list_ports/list_ports_linux.cc.o
libmyserial.a: CMakeFiles/myserial.dir/build.make
libmyserial.a: CMakeFiles/myserial.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/samuko/projects/easy_pid_motor_ctrl/main/motor_control_myserial_client_api_cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library libmyserial.a"
	$(CMAKE_COMMAND) -P CMakeFiles/myserial.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/myserial.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/myserial.dir/build: libmyserial.a
.PHONY : CMakeFiles/myserial.dir/build

CMakeFiles/myserial.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/myserial.dir/cmake_clean.cmake
.PHONY : CMakeFiles/myserial.dir/clean

CMakeFiles/myserial.dir/depend:
	cd /home/samuko/projects/easy_pid_motor_ctrl/main/motor_control_myserial_client_api_cpp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/samuko/projects/easy_pid_motor_ctrl/main/motor_control_myserial_client_api_cpp /home/samuko/projects/easy_pid_motor_ctrl/main/motor_control_myserial_client_api_cpp /home/samuko/projects/easy_pid_motor_ctrl/main/motor_control_myserial_client_api_cpp/build /home/samuko/projects/easy_pid_motor_ctrl/main/motor_control_myserial_client_api_cpp/build /home/samuko/projects/easy_pid_motor_ctrl/main/motor_control_myserial_client_api_cpp/build/CMakeFiles/myserial.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/myserial.dir/depend
