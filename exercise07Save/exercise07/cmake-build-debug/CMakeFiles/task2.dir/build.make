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
CMAKE_COMMAND = /snap/clion/112/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/112/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/benedikt/CLionProjects/ps_os_2020/exercise07

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/benedikt/CLionProjects/ps_os_2020/exercise07/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/task2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/task2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/task2.dir/flags.make

CMakeFiles/task2.dir/task2.c.o: CMakeFiles/task2.dir/flags.make
CMakeFiles/task2.dir/task2.c.o: ../task2.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/benedikt/CLionProjects/ps_os_2020/exercise07/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/task2.dir/task2.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/task2.dir/task2.c.o   -c /home/benedikt/CLionProjects/ps_os_2020/exercise07/task2.c

CMakeFiles/task2.dir/task2.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/task2.dir/task2.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/benedikt/CLionProjects/ps_os_2020/exercise07/task2.c > CMakeFiles/task2.dir/task2.c.i

CMakeFiles/task2.dir/task2.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/task2.dir/task2.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/benedikt/CLionProjects/ps_os_2020/exercise07/task2.c -o CMakeFiles/task2.dir/task2.c.s

# Object files for target task2
task2_OBJECTS = \
"CMakeFiles/task2.dir/task2.c.o"

# External object files for target task2
task2_EXTERNAL_OBJECTS =

task2: CMakeFiles/task2.dir/task2.c.o
task2: CMakeFiles/task2.dir/build.make
task2: CMakeFiles/task2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/benedikt/CLionProjects/ps_os_2020/exercise07/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable task2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/task2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/task2.dir/build: task2

.PHONY : CMakeFiles/task2.dir/build

CMakeFiles/task2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/task2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/task2.dir/clean

CMakeFiles/task2.dir/depend:
	cd /home/benedikt/CLionProjects/ps_os_2020/exercise07/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/benedikt/CLionProjects/ps_os_2020/exercise07 /home/benedikt/CLionProjects/ps_os_2020/exercise07 /home/benedikt/CLionProjects/ps_os_2020/exercise07/cmake-build-debug /home/benedikt/CLionProjects/ps_os_2020/exercise07/cmake-build-debug /home/benedikt/CLionProjects/ps_os_2020/exercise07/cmake-build-debug/CMakeFiles/task2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/task2.dir/depend

