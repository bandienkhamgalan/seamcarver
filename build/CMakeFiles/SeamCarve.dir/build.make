# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.9.0/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.9.0/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/bandi/Desktop/seamcarve_Windows

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/bandi/Desktop/seamcarve_Windows/build

# Include any dependencies generated for this target.
include CMakeFiles/SeamCarve.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/SeamCarve.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SeamCarve.dir/flags.make

CMakeFiles/SeamCarve.dir/main.cpp.o: CMakeFiles/SeamCarve.dir/flags.make
CMakeFiles/SeamCarve.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/bandi/Desktop/seamcarve_Windows/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/SeamCarve.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SeamCarve.dir/main.cpp.o -c /Users/bandi/Desktop/seamcarve_Windows/main.cpp

CMakeFiles/SeamCarve.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SeamCarve.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/bandi/Desktop/seamcarve_Windows/main.cpp > CMakeFiles/SeamCarve.dir/main.cpp.i

CMakeFiles/SeamCarve.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SeamCarve.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/bandi/Desktop/seamcarve_Windows/main.cpp -o CMakeFiles/SeamCarve.dir/main.cpp.s

CMakeFiles/SeamCarve.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/SeamCarve.dir/main.cpp.o.requires

CMakeFiles/SeamCarve.dir/main.cpp.o.provides: CMakeFiles/SeamCarve.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/SeamCarve.dir/build.make CMakeFiles/SeamCarve.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/SeamCarve.dir/main.cpp.o.provides

CMakeFiles/SeamCarve.dir/main.cpp.o.provides.build: CMakeFiles/SeamCarve.dir/main.cpp.o


CMakeFiles/SeamCarve.dir/MainWindow.cpp.o: CMakeFiles/SeamCarve.dir/flags.make
CMakeFiles/SeamCarve.dir/MainWindow.cpp.o: ../MainWindow.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/bandi/Desktop/seamcarve_Windows/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/SeamCarve.dir/MainWindow.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SeamCarve.dir/MainWindow.cpp.o -c /Users/bandi/Desktop/seamcarve_Windows/MainWindow.cpp

CMakeFiles/SeamCarve.dir/MainWindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SeamCarve.dir/MainWindow.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/bandi/Desktop/seamcarve_Windows/MainWindow.cpp > CMakeFiles/SeamCarve.dir/MainWindow.cpp.i

CMakeFiles/SeamCarve.dir/MainWindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SeamCarve.dir/MainWindow.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/bandi/Desktop/seamcarve_Windows/MainWindow.cpp -o CMakeFiles/SeamCarve.dir/MainWindow.cpp.s

CMakeFiles/SeamCarve.dir/MainWindow.cpp.o.requires:

.PHONY : CMakeFiles/SeamCarve.dir/MainWindow.cpp.o.requires

CMakeFiles/SeamCarve.dir/MainWindow.cpp.o.provides: CMakeFiles/SeamCarve.dir/MainWindow.cpp.o.requires
	$(MAKE) -f CMakeFiles/SeamCarve.dir/build.make CMakeFiles/SeamCarve.dir/MainWindow.cpp.o.provides.build
.PHONY : CMakeFiles/SeamCarve.dir/MainWindow.cpp.o.provides

CMakeFiles/SeamCarve.dir/MainWindow.cpp.o.provides.build: CMakeFiles/SeamCarve.dir/MainWindow.cpp.o


CMakeFiles/SeamCarve.dir/GLImageWidget.cpp.o: CMakeFiles/SeamCarve.dir/flags.make
CMakeFiles/SeamCarve.dir/GLImageWidget.cpp.o: ../GLImageWidget.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/bandi/Desktop/seamcarve_Windows/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/SeamCarve.dir/GLImageWidget.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SeamCarve.dir/GLImageWidget.cpp.o -c /Users/bandi/Desktop/seamcarve_Windows/GLImageWidget.cpp

CMakeFiles/SeamCarve.dir/GLImageWidget.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SeamCarve.dir/GLImageWidget.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/bandi/Desktop/seamcarve_Windows/GLImageWidget.cpp > CMakeFiles/SeamCarve.dir/GLImageWidget.cpp.i

CMakeFiles/SeamCarve.dir/GLImageWidget.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SeamCarve.dir/GLImageWidget.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/bandi/Desktop/seamcarve_Windows/GLImageWidget.cpp -o CMakeFiles/SeamCarve.dir/GLImageWidget.cpp.s

CMakeFiles/SeamCarve.dir/GLImageWidget.cpp.o.requires:

.PHONY : CMakeFiles/SeamCarve.dir/GLImageWidget.cpp.o.requires

CMakeFiles/SeamCarve.dir/GLImageWidget.cpp.o.provides: CMakeFiles/SeamCarve.dir/GLImageWidget.cpp.o.requires
	$(MAKE) -f CMakeFiles/SeamCarve.dir/build.make CMakeFiles/SeamCarve.dir/GLImageWidget.cpp.o.provides.build
.PHONY : CMakeFiles/SeamCarve.dir/GLImageWidget.cpp.o.provides

CMakeFiles/SeamCarve.dir/GLImageWidget.cpp.o.provides.build: CMakeFiles/SeamCarve.dir/GLImageWidget.cpp.o


CMakeFiles/SeamCarve.dir/CLSeamCarver.cpp.o: CMakeFiles/SeamCarve.dir/flags.make
CMakeFiles/SeamCarve.dir/CLSeamCarver.cpp.o: ../CLSeamCarver.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/bandi/Desktop/seamcarve_Windows/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/SeamCarve.dir/CLSeamCarver.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SeamCarve.dir/CLSeamCarver.cpp.o -c /Users/bandi/Desktop/seamcarve_Windows/CLSeamCarver.cpp

CMakeFiles/SeamCarve.dir/CLSeamCarver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SeamCarve.dir/CLSeamCarver.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/bandi/Desktop/seamcarve_Windows/CLSeamCarver.cpp > CMakeFiles/SeamCarve.dir/CLSeamCarver.cpp.i

CMakeFiles/SeamCarve.dir/CLSeamCarver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SeamCarve.dir/CLSeamCarver.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/bandi/Desktop/seamcarve_Windows/CLSeamCarver.cpp -o CMakeFiles/SeamCarve.dir/CLSeamCarver.cpp.s

CMakeFiles/SeamCarve.dir/CLSeamCarver.cpp.o.requires:

.PHONY : CMakeFiles/SeamCarve.dir/CLSeamCarver.cpp.o.requires

CMakeFiles/SeamCarve.dir/CLSeamCarver.cpp.o.provides: CMakeFiles/SeamCarve.dir/CLSeamCarver.cpp.o.requires
	$(MAKE) -f CMakeFiles/SeamCarve.dir/build.make CMakeFiles/SeamCarve.dir/CLSeamCarver.cpp.o.provides.build
.PHONY : CMakeFiles/SeamCarve.dir/CLSeamCarver.cpp.o.provides

CMakeFiles/SeamCarve.dir/CLSeamCarver.cpp.o.provides.build: CMakeFiles/SeamCarve.dir/CLSeamCarver.cpp.o


CMakeFiles/SeamCarve.dir/SeamCarverWidget.cpp.o: CMakeFiles/SeamCarve.dir/flags.make
CMakeFiles/SeamCarve.dir/SeamCarverWidget.cpp.o: ../SeamCarverWidget.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/bandi/Desktop/seamcarve_Windows/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/SeamCarve.dir/SeamCarverWidget.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SeamCarve.dir/SeamCarverWidget.cpp.o -c /Users/bandi/Desktop/seamcarve_Windows/SeamCarverWidget.cpp

CMakeFiles/SeamCarve.dir/SeamCarverWidget.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SeamCarve.dir/SeamCarverWidget.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/bandi/Desktop/seamcarve_Windows/SeamCarverWidget.cpp > CMakeFiles/SeamCarve.dir/SeamCarverWidget.cpp.i

CMakeFiles/SeamCarve.dir/SeamCarverWidget.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SeamCarve.dir/SeamCarverWidget.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/bandi/Desktop/seamcarve_Windows/SeamCarverWidget.cpp -o CMakeFiles/SeamCarve.dir/SeamCarverWidget.cpp.s

CMakeFiles/SeamCarve.dir/SeamCarverWidget.cpp.o.requires:

.PHONY : CMakeFiles/SeamCarve.dir/SeamCarverWidget.cpp.o.requires

CMakeFiles/SeamCarve.dir/SeamCarverWidget.cpp.o.provides: CMakeFiles/SeamCarve.dir/SeamCarverWidget.cpp.o.requires
	$(MAKE) -f CMakeFiles/SeamCarve.dir/build.make CMakeFiles/SeamCarve.dir/SeamCarverWidget.cpp.o.provides.build
.PHONY : CMakeFiles/SeamCarve.dir/SeamCarverWidget.cpp.o.provides

CMakeFiles/SeamCarve.dir/SeamCarverWidget.cpp.o.provides.build: CMakeFiles/SeamCarve.dir/SeamCarverWidget.cpp.o


CMakeFiles/SeamCarve.dir/CCocoaGLContext.mm.o: CMakeFiles/SeamCarve.dir/flags.make
CMakeFiles/SeamCarve.dir/CCocoaGLContext.mm.o: ../CCocoaGLContext.mm
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/bandi/Desktop/seamcarve_Windows/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/SeamCarve.dir/CCocoaGLContext.mm.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SeamCarve.dir/CCocoaGLContext.mm.o -c /Users/bandi/Desktop/seamcarve_Windows/CCocoaGLContext.mm

CMakeFiles/SeamCarve.dir/CCocoaGLContext.mm.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SeamCarve.dir/CCocoaGLContext.mm.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/bandi/Desktop/seamcarve_Windows/CCocoaGLContext.mm > CMakeFiles/SeamCarve.dir/CCocoaGLContext.mm.i

CMakeFiles/SeamCarve.dir/CCocoaGLContext.mm.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SeamCarve.dir/CCocoaGLContext.mm.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/bandi/Desktop/seamcarve_Windows/CCocoaGLContext.mm -o CMakeFiles/SeamCarve.dir/CCocoaGLContext.mm.s

CMakeFiles/SeamCarve.dir/CCocoaGLContext.mm.o.requires:

.PHONY : CMakeFiles/SeamCarve.dir/CCocoaGLContext.mm.o.requires

CMakeFiles/SeamCarve.dir/CCocoaGLContext.mm.o.provides: CMakeFiles/SeamCarve.dir/CCocoaGLContext.mm.o.requires
	$(MAKE) -f CMakeFiles/SeamCarve.dir/build.make CMakeFiles/SeamCarve.dir/CCocoaGLContext.mm.o.provides.build
.PHONY : CMakeFiles/SeamCarve.dir/CCocoaGLContext.mm.o.provides

CMakeFiles/SeamCarve.dir/CCocoaGLContext.mm.o.provides.build: CMakeFiles/SeamCarve.dir/CCocoaGLContext.mm.o


CMakeFiles/SeamCarve.dir/SeamCarve_autogen/mocs_compilation.cpp.o: CMakeFiles/SeamCarve.dir/flags.make
CMakeFiles/SeamCarve.dir/SeamCarve_autogen/mocs_compilation.cpp.o: SeamCarve_autogen/mocs_compilation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/bandi/Desktop/seamcarve_Windows/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/SeamCarve.dir/SeamCarve_autogen/mocs_compilation.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SeamCarve.dir/SeamCarve_autogen/mocs_compilation.cpp.o -c /Users/bandi/Desktop/seamcarve_Windows/build/SeamCarve_autogen/mocs_compilation.cpp

CMakeFiles/SeamCarve.dir/SeamCarve_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SeamCarve.dir/SeamCarve_autogen/mocs_compilation.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/bandi/Desktop/seamcarve_Windows/build/SeamCarve_autogen/mocs_compilation.cpp > CMakeFiles/SeamCarve.dir/SeamCarve_autogen/mocs_compilation.cpp.i

CMakeFiles/SeamCarve.dir/SeamCarve_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SeamCarve.dir/SeamCarve_autogen/mocs_compilation.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/bandi/Desktop/seamcarve_Windows/build/SeamCarve_autogen/mocs_compilation.cpp -o CMakeFiles/SeamCarve.dir/SeamCarve_autogen/mocs_compilation.cpp.s

CMakeFiles/SeamCarve.dir/SeamCarve_autogen/mocs_compilation.cpp.o.requires:

.PHONY : CMakeFiles/SeamCarve.dir/SeamCarve_autogen/mocs_compilation.cpp.o.requires

CMakeFiles/SeamCarve.dir/SeamCarve_autogen/mocs_compilation.cpp.o.provides: CMakeFiles/SeamCarve.dir/SeamCarve_autogen/mocs_compilation.cpp.o.requires
	$(MAKE) -f CMakeFiles/SeamCarve.dir/build.make CMakeFiles/SeamCarve.dir/SeamCarve_autogen/mocs_compilation.cpp.o.provides.build
.PHONY : CMakeFiles/SeamCarve.dir/SeamCarve_autogen/mocs_compilation.cpp.o.provides

CMakeFiles/SeamCarve.dir/SeamCarve_autogen/mocs_compilation.cpp.o.provides.build: CMakeFiles/SeamCarve.dir/SeamCarve_autogen/mocs_compilation.cpp.o


# Object files for target SeamCarve
SeamCarve_OBJECTS = \
"CMakeFiles/SeamCarve.dir/main.cpp.o" \
"CMakeFiles/SeamCarve.dir/MainWindow.cpp.o" \
"CMakeFiles/SeamCarve.dir/GLImageWidget.cpp.o" \
"CMakeFiles/SeamCarve.dir/CLSeamCarver.cpp.o" \
"CMakeFiles/SeamCarve.dir/SeamCarverWidget.cpp.o" \
"CMakeFiles/SeamCarve.dir/CCocoaGLContext.mm.o" \
"CMakeFiles/SeamCarve.dir/SeamCarve_autogen/mocs_compilation.cpp.o"

# External object files for target SeamCarve
SeamCarve_EXTERNAL_OBJECTS =

SeamCarve: CMakeFiles/SeamCarve.dir/main.cpp.o
SeamCarve: CMakeFiles/SeamCarve.dir/MainWindow.cpp.o
SeamCarve: CMakeFiles/SeamCarve.dir/GLImageWidget.cpp.o
SeamCarve: CMakeFiles/SeamCarve.dir/CLSeamCarver.cpp.o
SeamCarve: CMakeFiles/SeamCarve.dir/SeamCarverWidget.cpp.o
SeamCarve: CMakeFiles/SeamCarve.dir/CCocoaGLContext.mm.o
SeamCarve: CMakeFiles/SeamCarve.dir/SeamCarve_autogen/mocs_compilation.cpp.o
SeamCarve: CMakeFiles/SeamCarve.dir/build.make
SeamCarve: /Users/bandi/Qt/5.9.2/clang_64/lib/QtWidgets.framework/QtWidgets
SeamCarve: /Users/bandi/Qt/5.9.2/clang_64/lib/QtGui.framework/QtGui
SeamCarve: /Users/bandi/Qt/5.9.2/clang_64/lib/QtCore.framework/QtCore
SeamCarve: CMakeFiles/SeamCarve.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/bandi/Desktop/seamcarve_Windows/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable SeamCarve"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SeamCarve.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SeamCarve.dir/build: SeamCarve

.PHONY : CMakeFiles/SeamCarve.dir/build

CMakeFiles/SeamCarve.dir/requires: CMakeFiles/SeamCarve.dir/main.cpp.o.requires
CMakeFiles/SeamCarve.dir/requires: CMakeFiles/SeamCarve.dir/MainWindow.cpp.o.requires
CMakeFiles/SeamCarve.dir/requires: CMakeFiles/SeamCarve.dir/GLImageWidget.cpp.o.requires
CMakeFiles/SeamCarve.dir/requires: CMakeFiles/SeamCarve.dir/CLSeamCarver.cpp.o.requires
CMakeFiles/SeamCarve.dir/requires: CMakeFiles/SeamCarve.dir/SeamCarverWidget.cpp.o.requires
CMakeFiles/SeamCarve.dir/requires: CMakeFiles/SeamCarve.dir/CCocoaGLContext.mm.o.requires
CMakeFiles/SeamCarve.dir/requires: CMakeFiles/SeamCarve.dir/SeamCarve_autogen/mocs_compilation.cpp.o.requires

.PHONY : CMakeFiles/SeamCarve.dir/requires

CMakeFiles/SeamCarve.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SeamCarve.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SeamCarve.dir/clean

CMakeFiles/SeamCarve.dir/depend:
	cd /Users/bandi/Desktop/seamcarve_Windows/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/bandi/Desktop/seamcarve_Windows /Users/bandi/Desktop/seamcarve_Windows /Users/bandi/Desktop/seamcarve_Windows/build /Users/bandi/Desktop/seamcarve_Windows/build /Users/bandi/Desktop/seamcarve_Windows/build/CMakeFiles/SeamCarve.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/SeamCarve.dir/depend

