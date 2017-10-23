cmake_minimum_required(VERSION 2.8.11)
project (SeamCarve)
set (CMAKE_CXX_STANDARD 14)
set (CMAKE_BUILD_TYPE Debug)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc and uic automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

# Find the QtWidgets library
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package (OpenCL REQUIRED)

add_executable(SeamCarve WIN32 main.cpp MainWindow.cpp GLImageWidget.cpp CLSeamCarver.cpp SeamCarverWidget.cpp)
install(TARGETS SeamCarve DESTINATION ${CMAKE_SOURCE_DIR}/release)

if(APPLE)
	foreach(directory ${Qt5Widgets_INCLUDE_DIRS})
		if(directory MATCHES QtCore.framework$)
			get_filename_component(Qt5_ROOT "${directory}/../.." ABSOLUTE)
			break()
		endif()
	endforeach()
	target_include_directories(SeamCarve PRIVATE "${Qt5_ROOT}/include/QtPlatformHeaders")
	target_sources(SeamCarve PRIVATE CCocoaGLContext.mm)
	target_link_libraries(SeamCarve "-framework Foundation -framework OpenGL")
elseif(WIN32)
	foreach(directory ${Qt5Widgets_INCLUDE_DIRS})
		if(directory MATCHES /QtWidgets$)
			get_filename_component(Qt5_ROOT "${directory}/../.." ABSOLUTE)
		endif()
	endforeach()
	target_include_directories(SeamCarve PRIVATE "${Qt5_ROOT}/include/QtPlatformHeaders" ${Qt5Gui_PRIVATE_INCLUDE_DIRS})

	# Qt Libraries
	get_target_property(QtCore_LOCATION Qt5::Core LOCATION)
	get_filename_component(QT_DLL_DIR ${QtCore_LOCATION} PATH)
	install(FILES
	${QT_DLL_DIR}/Qt5Cored.dll
	${QT_DLL_DIR}/Qt5Guid.dll
	${QT_DLL_DIR}/Qt5Widgetsd.dll
	DESTINATION ${CMAKE_SOURCE_DIR}/release)

	find_package(OpenGL REQUIRED)
	target_link_libraries(SeamCarve ${OPENGL_LIBRARIES})
endif()


target_include_directories(SeamCarve PRIVATE ${OpenCL_INCLUDE_DIR})
target_compile_options(SeamCarve PRIVATE -Wall) 
target_link_libraries(SeamCarve ${OpenCL_LIBRARIES} Qt5::Widgets)