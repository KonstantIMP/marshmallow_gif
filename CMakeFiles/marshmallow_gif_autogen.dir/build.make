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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/konstantin/Projects/marshmallow_gif

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/konstantin/Projects/marshmallow_gif

# Utility rule file for marshmallow_gif_autogen.

# Include the progress variables for this target.
include CMakeFiles/marshmallow_gif_autogen.dir/progress.make

CMakeFiles/marshmallow_gif_autogen:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/konstantin/Projects/marshmallow_gif/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target marshmallow_gif"
	/usr/bin/cmake -E cmake_autogen /home/konstantin/Projects/marshmallow_gif/CMakeFiles/marshmallow_gif_autogen.dir/AutogenInfo.json Build

marshmallow_gif_autogen: CMakeFiles/marshmallow_gif_autogen
marshmallow_gif_autogen: CMakeFiles/marshmallow_gif_autogen.dir/build.make

.PHONY : marshmallow_gif_autogen

# Rule to build all files generated by this target.
CMakeFiles/marshmallow_gif_autogen.dir/build: marshmallow_gif_autogen

.PHONY : CMakeFiles/marshmallow_gif_autogen.dir/build

CMakeFiles/marshmallow_gif_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/marshmallow_gif_autogen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/marshmallow_gif_autogen.dir/clean

CMakeFiles/marshmallow_gif_autogen.dir/depend:
	cd /home/konstantin/Projects/marshmallow_gif && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/konstantin/Projects/marshmallow_gif /home/konstantin/Projects/marshmallow_gif /home/konstantin/Projects/marshmallow_gif /home/konstantin/Projects/marshmallow_gif /home/konstantin/Projects/marshmallow_gif/CMakeFiles/marshmallow_gif_autogen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/marshmallow_gif_autogen.dir/depend

