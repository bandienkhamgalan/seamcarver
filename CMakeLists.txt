cmake_minimum_required(VERSION 2.6)
project (SeamCarve)
set (CMAKE_CXX_STANDARD 14)
set (CMAKE_BUILD_TYPE Debug)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc and uic automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

# Find the QtWidgets library
find_package(Qt5Widgets REQUIRED)

find_package (OpenCL REQUIRED)

find_library(jpeg jpeg)
add_executable(SeamCarve RGBAImage.cpp JPEG.cpp main.cpp MainWindow.cpp GLImageWidget.cpp CCocoaGLContext.mm CLSeamCarver.cpp SeamCarverWidget.cpp)

if(APPLE)
	foreach(directory ${Qt5Widgets_INCLUDE_DIRS})
		if(directory MATCHES QtCore.framework$)
			get_filename_component(Qt5_INCLUDE_ROOT "${directory}/../.." ABSOLUTE)
			break()
		endif()
	endforeach()
	target_include_directories(SeamCarve PRIVATE "${Qt5_INCLUDE_ROOT}/include/QtPlatformHeaders")

	target_link_libraries(SeamCarve "-framework Foundation -framework OpenGL")
endif()

target_compile_options(SeamCarve PRIVATE -Wall -Werror) 
target_link_libraries(SeamCarve ${OpenCL_LIBRARIES} ${jpeg} Qt5::Widgets)