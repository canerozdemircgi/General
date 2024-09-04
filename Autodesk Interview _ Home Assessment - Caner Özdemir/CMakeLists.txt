cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME Home_Assessment_-_Caner_Ozdemir)

project(${PROJECT_NAME} VERSION 1.0 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
	code/main.cpp
	code/data/configuration.h
	code/data/configuration.cpp
	code/component/menubar.h
	code/component/menubar.cpp
	code/component/menubar.ui
	code/component/pensize.h
	code/component/pensize.cpp
	code/component/pencolor.h
	code/component/pencolor.cpp
	code/component/penopacity.h
	code/component/penopacity.cpp
	code/component/pentool.h
	code/component/pentool.cpp
	code/component/erasertool.h
	code/component/erasertool.cpp
	code/component/zoom.h
	code/component/zoom.cpp
	code/component/paintarea.h
	code/component/paintarea.cpp
	code/mainwindow.h
	code/mainwindow.cpp
	code/mainwindow.ui
	resource/resource.qrc
	resource/resource.rc
)

qt_add_executable(${PROJECT_NAME} WIN32 ${PROJECT_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE code)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)
install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/binary)