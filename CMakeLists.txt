cmake_minimum_required(VERSION 3.16)

project(LxUI VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Gui)
qt_standard_project_setup(REQUIRES 6.5)

add_subdirectory(LxUI)


option(BUILD_DEMO "Build the demo application" ON)

if(BUILD_DEMO)
    add_subdirectory(demo)
endif()
