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
include CMakeFiles/task3_atomic.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/task3_atomic.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/task3_atomic.dir/flags.make

CMakeFiles/task3_atomic.dir/task3_atomic.c.o: CMakeFiles/task3_atomic.dir/flags.make
CMakeFiles/task3_atomic.dir/task3_atomic.c.o: ../task3_atomic.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/benedikt/CLionProjects/ps_os_2020/exercise07/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/task3_atomic.dir/task3_atomic.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/task3_atomic.dir/task3_atomic.c.o   -c /home/benedikt/CLionProjects/ps_os_2020/exercise07/task3_atomic.c

CMakeFiles/task3_atomic.dir/task3_atomic.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/task3_atomic.dir/task3_atomic.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/benedikt/CLionProjects/ps_os_2020/exercise07/task3_atomic.c > CMakeFiles/task3_atomic.dir/task3_atomic.c.i

CMakeFiles/task3_atomic.dir/task3_atomic.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/task3_atomic.dir/task3_atomic.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/benedikt/CLionProjects/ps_os_2020/exercise07/task3_atomic.c -o CMakeFiles/task3_atomic.dir/task3_atomic.c.s

# Object files for target task3_atomic
task3_atomic_OBJECTS = \
"CMakeFiles/task3_atomic.dir/task3_atomic.c.o"

# External object files for target task3_atomic
task3_atomic_EXTERNAL_OBJECTS =

task3_atomic: CMakeFiles/task3_atomic.dir/task3_atomic.c.o
task3_atomic: CMakeFiles/task3_atomic.dir/build.make
task3_atomic: CMakeFiles/task3_atomic.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/benedikt/CLionProjects/ps_os_2020/exercise07/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable task3_atomic"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/task3_atomic.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/task3_atomic.dir/build: task3_atomic

.PHONY : CMakeFiles/task3_atomic.dir/build

CMakeFiles/task3_atomic.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/task3_atomic.dir/cmake_clean.cmake
.PHONY : CMakeFiles/task3_atomic.dir/clean

CMakeFiles/task3_atomic.dir/depend:
	cd /home/benedikt/CLionProjects/ps_os_2020/exercise07/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/benedikt/CLionProjects/ps_os_2020/exercise07 /home/benedikt/CLionProjects/ps_os_2020/exercise07 /home/benedikt/CLionProjects/ps_os_2020/exercise07/cmake-build-debug /home/benedikt/CLionProjects/ps_os_2020/exercise07/cmake-build-debug /home/benedikt/CLionProjects/ps_os_2020/exercise07/cmake-build-debug/CMakeFiles/task3_atomic.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/task3_atomic.dir/depend

