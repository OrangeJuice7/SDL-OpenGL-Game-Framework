# Credit: http://web.archive.org/web/20141116113322/http://preetisblog.com/programming/how-to-write-cmakelists-txt
# Note: above is for old CMake (i.e. before 3.0)

# Require at least CMake version 3.12
cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

# Project name
set(PROJECT_NAME project_template)
project(${PROJECT_NAME})
set(EXECUTABLE_NAME "Project_Template")

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# Find out the packages of additional libraries, if required.
# Each such package should have a Cmake file in them, if not then we may have to manually define the paths.
find_package(SDL2 REQUIRED)

find_file(SDL2_INCLUDE_DIR NAME SDL.h HINTS SDL2)
find_library(SDL2_LIBRARY NAME SDL2)

# here we specify the additional include directories for the project.
include_directories(${SDL2_INCLUDE_DIRS})

# here we add definitions for any package if required.
add_definitions(${SDL2_DEFINITIONS})

add_subdirectory(src)
