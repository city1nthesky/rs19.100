# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

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
CMAKE_SOURCE_DIR = /home/dong/rising/Source_Code/9.18-text/UnixRav3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dong/rising/Source_Code/9.18-text/build

# Include any dependencies generated for this target.
include DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/compiler_depend.make

# Include the progress variables for this target.
include DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/progress.make

# Include the compile flags for this target's objects.
include DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/flags.make

DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/main.cpp.o: DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/flags.make
DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/main.cpp.o: /home/dong/rising/Source_Code/9.18-text/UnixRav3/DefenMod/main.cpp
DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/main.cpp.o: DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dong/rising/Source_Code/9.18-text/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/main.cpp.o"
	cd /home/dong/rising/Source_Code/9.18-text/build/DefenMod && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/main.cpp.o -MF CMakeFiles/ravdefenbinder_inotify.dir/main.cpp.o.d -o CMakeFiles/ravdefenbinder_inotify.dir/main.cpp.o -c /home/dong/rising/Source_Code/9.18-text/UnixRav3/DefenMod/main.cpp

DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ravdefenbinder_inotify.dir/main.cpp.i"
	cd /home/dong/rising/Source_Code/9.18-text/build/DefenMod && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dong/rising/Source_Code/9.18-text/UnixRav3/DefenMod/main.cpp > CMakeFiles/ravdefenbinder_inotify.dir/main.cpp.i

DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ravdefenbinder_inotify.dir/main.cpp.s"
	cd /home/dong/rising/Source_Code/9.18-text/build/DefenMod && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dong/rising/Source_Code/9.18-text/UnixRav3/DefenMod/main.cpp -o CMakeFiles/ravdefenbinder_inotify.dir/main.cpp.s

DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/defenmodproxy.cpp.o: DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/flags.make
DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/defenmodproxy.cpp.o: /home/dong/rising/Source_Code/9.18-text/UnixRav3/DefenMod/defenmodproxy.cpp
DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/defenmodproxy.cpp.o: DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dong/rising/Source_Code/9.18-text/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/defenmodproxy.cpp.o"
	cd /home/dong/rising/Source_Code/9.18-text/build/DefenMod && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/defenmodproxy.cpp.o -MF CMakeFiles/ravdefenbinder_inotify.dir/defenmodproxy.cpp.o.d -o CMakeFiles/ravdefenbinder_inotify.dir/defenmodproxy.cpp.o -c /home/dong/rising/Source_Code/9.18-text/UnixRav3/DefenMod/defenmodproxy.cpp

DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/defenmodproxy.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ravdefenbinder_inotify.dir/defenmodproxy.cpp.i"
	cd /home/dong/rising/Source_Code/9.18-text/build/DefenMod && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dong/rising/Source_Code/9.18-text/UnixRav3/DefenMod/defenmodproxy.cpp > CMakeFiles/ravdefenbinder_inotify.dir/defenmodproxy.cpp.i

DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/defenmodproxy.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ravdefenbinder_inotify.dir/defenmodproxy.cpp.s"
	cd /home/dong/rising/Source_Code/9.18-text/build/DefenMod && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dong/rising/Source_Code/9.18-text/UnixRav3/DefenMod/defenmodproxy.cpp -o CMakeFiles/ravdefenbinder_inotify.dir/defenmodproxy.cpp.s

DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/defenplugins.cpp.o: DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/flags.make
DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/defenplugins.cpp.o: /home/dong/rising/Source_Code/9.18-text/UnixRav3/DefenMod/defenplugins.cpp
DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/defenplugins.cpp.o: DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dong/rising/Source_Code/9.18-text/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/defenplugins.cpp.o"
	cd /home/dong/rising/Source_Code/9.18-text/build/DefenMod && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/defenplugins.cpp.o -MF CMakeFiles/ravdefenbinder_inotify.dir/defenplugins.cpp.o.d -o CMakeFiles/ravdefenbinder_inotify.dir/defenplugins.cpp.o -c /home/dong/rising/Source_Code/9.18-text/UnixRav3/DefenMod/defenplugins.cpp

DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/defenplugins.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ravdefenbinder_inotify.dir/defenplugins.cpp.i"
	cd /home/dong/rising/Source_Code/9.18-text/build/DefenMod && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dong/rising/Source_Code/9.18-text/UnixRav3/DefenMod/defenplugins.cpp > CMakeFiles/ravdefenbinder_inotify.dir/defenplugins.cpp.i

DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/defenplugins.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ravdefenbinder_inotify.dir/defenplugins.cpp.s"
	cd /home/dong/rising/Source_Code/9.18-text/build/DefenMod && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dong/rising/Source_Code/9.18-text/UnixRav3/DefenMod/defenplugins.cpp -o CMakeFiles/ravdefenbinder_inotify.dir/defenplugins.cpp.s

DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/defenengine.cpp.o: DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/flags.make
DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/defenengine.cpp.o: /home/dong/rising/Source_Code/9.18-text/UnixRav3/DefenMod/defenengine.cpp
DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/defenengine.cpp.o: DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dong/rising/Source_Code/9.18-text/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/defenengine.cpp.o"
	cd /home/dong/rising/Source_Code/9.18-text/build/DefenMod && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/defenengine.cpp.o -MF CMakeFiles/ravdefenbinder_inotify.dir/defenengine.cpp.o.d -o CMakeFiles/ravdefenbinder_inotify.dir/defenengine.cpp.o -c /home/dong/rising/Source_Code/9.18-text/UnixRav3/DefenMod/defenengine.cpp

DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/defenengine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ravdefenbinder_inotify.dir/defenengine.cpp.i"
	cd /home/dong/rising/Source_Code/9.18-text/build/DefenMod && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dong/rising/Source_Code/9.18-text/UnixRav3/DefenMod/defenengine.cpp > CMakeFiles/ravdefenbinder_inotify.dir/defenengine.cpp.i

DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/defenengine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ravdefenbinder_inotify.dir/defenengine.cpp.s"
	cd /home/dong/rising/Source_Code/9.18-text/build/DefenMod && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dong/rising/Source_Code/9.18-text/UnixRav3/DefenMod/defenengine.cpp -o CMakeFiles/ravdefenbinder_inotify.dir/defenengine.cpp.s

DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/__/CommonAPI/crypt/crc32.c.o: DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/flags.make
DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/__/CommonAPI/crypt/crc32.c.o: /home/dong/rising/Source_Code/9.18-text/UnixRav3/CommonAPI/crypt/crc32.c
DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/__/CommonAPI/crypt/crc32.c.o: DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dong/rising/Source_Code/9.18-text/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/__/CommonAPI/crypt/crc32.c.o"
	cd /home/dong/rising/Source_Code/9.18-text/build/DefenMod && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/__/CommonAPI/crypt/crc32.c.o -MF CMakeFiles/ravdefenbinder_inotify.dir/__/CommonAPI/crypt/crc32.c.o.d -o CMakeFiles/ravdefenbinder_inotify.dir/__/CommonAPI/crypt/crc32.c.o -c /home/dong/rising/Source_Code/9.18-text/UnixRav3/CommonAPI/crypt/crc32.c

DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/__/CommonAPI/crypt/crc32.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ravdefenbinder_inotify.dir/__/CommonAPI/crypt/crc32.c.i"
	cd /home/dong/rising/Source_Code/9.18-text/build/DefenMod && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dong/rising/Source_Code/9.18-text/UnixRav3/CommonAPI/crypt/crc32.c > CMakeFiles/ravdefenbinder_inotify.dir/__/CommonAPI/crypt/crc32.c.i

DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/__/CommonAPI/crypt/crc32.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ravdefenbinder_inotify.dir/__/CommonAPI/crypt/crc32.c.s"
	cd /home/dong/rising/Source_Code/9.18-text/build/DefenMod && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dong/rising/Source_Code/9.18-text/UnixRav3/CommonAPI/crypt/crc32.c -o CMakeFiles/ravdefenbinder_inotify.dir/__/CommonAPI/crypt/crc32.c.s

DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/__/RavDaemon/COMMON/kernelapplication.cpp.o: DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/flags.make
DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/__/RavDaemon/COMMON/kernelapplication.cpp.o: /home/dong/rising/Source_Code/9.18-text/UnixRav3/RavDaemon/COMMON/kernelapplication.cpp
DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/__/RavDaemon/COMMON/kernelapplication.cpp.o: DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dong/rising/Source_Code/9.18-text/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/__/RavDaemon/COMMON/kernelapplication.cpp.o"
	cd /home/dong/rising/Source_Code/9.18-text/build/DefenMod && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/__/RavDaemon/COMMON/kernelapplication.cpp.o -MF CMakeFiles/ravdefenbinder_inotify.dir/__/RavDaemon/COMMON/kernelapplication.cpp.o.d -o CMakeFiles/ravdefenbinder_inotify.dir/__/RavDaemon/COMMON/kernelapplication.cpp.o -c /home/dong/rising/Source_Code/9.18-text/UnixRav3/RavDaemon/COMMON/kernelapplication.cpp

DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/__/RavDaemon/COMMON/kernelapplication.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ravdefenbinder_inotify.dir/__/RavDaemon/COMMON/kernelapplication.cpp.i"
	cd /home/dong/rising/Source_Code/9.18-text/build/DefenMod && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dong/rising/Source_Code/9.18-text/UnixRav3/RavDaemon/COMMON/kernelapplication.cpp > CMakeFiles/ravdefenbinder_inotify.dir/__/RavDaemon/COMMON/kernelapplication.cpp.i

DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/__/RavDaemon/COMMON/kernelapplication.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ravdefenbinder_inotify.dir/__/RavDaemon/COMMON/kernelapplication.cpp.s"
	cd /home/dong/rising/Source_Code/9.18-text/build/DefenMod && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dong/rising/Source_Code/9.18-text/UnixRav3/RavDaemon/COMMON/kernelapplication.cpp -o CMakeFiles/ravdefenbinder_inotify.dir/__/RavDaemon/COMMON/kernelapplication.cpp.s

# Object files for target ravdefenbinder_inotify
ravdefenbinder_inotify_OBJECTS = \
"CMakeFiles/ravdefenbinder_inotify.dir/main.cpp.o" \
"CMakeFiles/ravdefenbinder_inotify.dir/defenmodproxy.cpp.o" \
"CMakeFiles/ravdefenbinder_inotify.dir/defenplugins.cpp.o" \
"CMakeFiles/ravdefenbinder_inotify.dir/defenengine.cpp.o" \
"CMakeFiles/ravdefenbinder_inotify.dir/__/CommonAPI/crypt/crc32.c.o" \
"CMakeFiles/ravdefenbinder_inotify.dir/__/RavDaemon/COMMON/kernelapplication.cpp.o"

# External object files for target ravdefenbinder_inotify
ravdefenbinder_inotify_EXTERNAL_OBJECTS =

3.0.0.1/lib/libravdefenbinder_inotify.so: DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/main.cpp.o
3.0.0.1/lib/libravdefenbinder_inotify.so: DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/defenmodproxy.cpp.o
3.0.0.1/lib/libravdefenbinder_inotify.so: DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/defenplugins.cpp.o
3.0.0.1/lib/libravdefenbinder_inotify.so: DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/defenengine.cpp.o
3.0.0.1/lib/libravdefenbinder_inotify.so: DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/__/CommonAPI/crypt/crc32.c.o
3.0.0.1/lib/libravdefenbinder_inotify.so: DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/__/RavDaemon/COMMON/kernelapplication.cpp.o
3.0.0.1/lib/libravdefenbinder_inotify.so: DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/build.make
3.0.0.1/lib/libravdefenbinder_inotify.so: DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dong/rising/Source_Code/9.18-text/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX shared library ../3.0.0.1/lib/libravdefenbinder_inotify.so"
	cd /home/dong/rising/Source_Code/9.18-text/build/DefenMod && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ravdefenbinder_inotify.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/build: 3.0.0.1/lib/libravdefenbinder_inotify.so
.PHONY : DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/build

DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/clean:
	cd /home/dong/rising/Source_Code/9.18-text/build/DefenMod && $(CMAKE_COMMAND) -P CMakeFiles/ravdefenbinder_inotify.dir/cmake_clean.cmake
.PHONY : DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/clean

DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/depend:
	cd /home/dong/rising/Source_Code/9.18-text/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dong/rising/Source_Code/9.18-text/UnixRav3 /home/dong/rising/Source_Code/9.18-text/UnixRav3/DefenMod /home/dong/rising/Source_Code/9.18-text/build /home/dong/rising/Source_Code/9.18-text/build/DefenMod /home/dong/rising/Source_Code/9.18-text/build/DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : DefenMod/CMakeFiles/ravdefenbinder_inotify.dir/depend

