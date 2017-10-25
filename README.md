OpenCL seam carver demo application
===================================

A GUI application built using Qt to demo an OpenCL implementation of [seam carving](http://dl.acm.org/citation.cfm?id=1276390) for content aware image rescaling. Read more about seam carving and the OpenCL kernel code on [my blog](http://bandi.me/seam-carving/). 

Supported operating systems
---------------------------

- macOS
- Windows

Prerequisites
-------------
- Qt (preferably version 5.9)
- cmake
- OpenCL 1.2 (compatible hardware, drivers and SDK with OpenGL interop capability)
- OpenGL 3.2 (compatible hardware, drivers and SDK)
- (Windows) Visual Studio 2017 with Modern C++ (Qt also works with MinGW but I have not tested this)

Instructions (macOS)
--------------------
1. Clone/download repo
3. `cd <path to repo>`
4. `mkdir build`
5. `cd build`
6. `cmake ..`
7. `make`
8. `make install`
9. Run `<path to repo>/release/SeamCarve` to launch the app

Instructions (Windows)
--------------------
1. Clone/download repo
3. `cd <path to repo>`
4. `mkdir build`
5. `cd build`
6. `cmake ..`
7. `cmake --build . --config Debug`
8. `cmake --build . --target install`
9. Run `<path to repo>/release/SeamCarve.exe` to launch the app

Common problems
---------------

`Could not find a package configuration file provided by "Qt5Widgets" with any of the following names`

Make sure to set the `CMAKE_PREFIX_PATH` env variable to your Qt installation path

<br />

(Windows) `LNK1112: module machine type 'x64' conflicts with target machine type 'X86'`

You built the app for x86 but you have x64 libraries. If you only installed the x64 version of Qt, you must instruct Visual Studio to compile for x64
by running `cmake .. -G "Visual Studio 15 2017 Win64"` instead of just `cmake ..` for Step 5. 
