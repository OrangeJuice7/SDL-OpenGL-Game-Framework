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

#################################################################################
# Credit: https://github.com/tesch1/SDL2-cmake-example/blob/master/CMakeLists.txt

# CPack
set (CPACK_COMPONENTS_ALL App)

set (CPACK_PACKAGE_NAME "mypackage")
set (CPACK_PACKAGE_DESCRIPTION_SUMMARY "sdl2 app package")
set (CPACK_PACKAGE_VERSION "${VERSION}${VERSION_BUILD}")
set (CPACK_PACKAGE_VERSION_MAJOR "${VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${VERSION_MINOR}")
set (CPACK_PACKAGE_VERSION_PATCH "${VERSION_PATCH}")
set (CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}")
set (CPACK_PACKAGE_URL "http://sdl.org")
set (CPACK_PACKAGE_VENDOR "nobody")
set (CPACK_PACKAGE_CONTACT "nobody@nowhere")
set (CPACK_PACKAGE_RELOCATABLE TRUE)
set (CPACK_STRIP_FILES TRUE)
set (CPACK_SOURCE_STRIP_FILES TRUE)

# WIN32
if (WIN32)
  set (CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-install-win32")
  set (CPACK_NSIS_EXECUTABLES_DIRECTORY ".")
  set (CPACK_NSIS_URL_INFO_ABOUT "http:\\\\\\\\sdl.org")
endif (WIN32)

# macOS
if (APPLE AND NOT XCODE)
  set (CPACK_GENERATOR "DragNDrop")
  set (CPACK_BUNDLE_NAME "${CPACK_PACKAGE_NAME}")
endif (APPLE AND NOT XCODE)

# unix
if (UNIX AND NOT APPLE)
  set (CPACK_GENERATOR "RPM;TGZ;DEB;STGZ")
  set (CPACK_INCLUDE_TOPLEVEL_DIRECTORY 1)
  set (CPACK_VERBATIM_VARIABLES TRUE) # fixes @ in rpm file names
  set (CPACK_RPM_PACKAGE_RELEASE 1)
  set (CPACK_DEBIAN_FILE_NAME "DEB-DEFAULT")
endif (UNIX AND NOT APPLE)

include (CPack)