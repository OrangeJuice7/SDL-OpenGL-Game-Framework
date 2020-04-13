# Credit: http://web.archive.org/web/20141116113322/http://preetisblog.com/programming/how-to-write-cmakelists-txt
# Note: above is for old CMake (i.e. before 3.0)

# Require at least CMake version 3.12
cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

# Project name
set(PROJECT_NAME project_template)
project(${PROJECT_NAME})
set(EXECUTABLE_NAME "Project_Template")

#set(CMAKE_CXX_STANDARD 11)

# Find out the packages of additional libraries, if required.
# Each such package should have a Cmake file in them, if not then we may have to manually define the paths.
find_package(SDL2 REQUIRED)

find_file(SDL2_INCLUDE_DIR NAME SDL.h HINTS SDL2)
find_library(SDL2_LIBRARY NAME SDL2)

# here we specify the additional include directories for the project.
include_directories(${SDL2_INCLUDE_DIRS})

# here we add definitions for any package if required.
add_definitions(${SDL2_DEFINITIONS})

# Specifies the executable. Here the executable
# The executable name is the first parameter, then comes all the source and header files.
# All cpp fles will be clubbed into source folder and all .h files will be added to header files folder of the project.
add_executable( ${EXECUTABLE_NAME}
	basicmath.hpp basicmath.cpp
	main.cpp
	Timer.hpp Timer.cpp
	MainApp/MainApp.hpp MainApp/MainApp.cpp
	MainApp/MessageHandler.hpp MainApp/MessageHandler.cpp
	MainUiManager/Init.cpp
	MainUiManager/InitFont.cpp
	MainUiManager/InitRenderer.cpp
	MainUiManager/InitSDL.cpp
	MainUiManager/InitTextures.cpp
	MainUiManager/InitWindow.cpp
	MainUiManager/Input.cpp
	MainUiManager/InputState.hpp MainUiManager/InputState.cpp
	MainUiManager/MainUiManager.hpp MainUiManager/MainUiManager.cpp
	MainUiManager/Render.cpp
	MainUiManager/Texture.hpp MainUiManager/Texture.cpp
	Message/Message.hpp Message/Message.cpp
	Message/SceneTransitMessage.hpp Message/SceneTransitMessage.cpp
	Scene/GameScene.hpp Scene/GameScene.cpp
	Scene/GameSceneInput.cpp
	Scene/MenuScene.hpp Scene/MenuScene.cpp
	Scene/MenuSceneInput.cpp
	Scene/Scene.hpp Scene/Scene.cpp
	Scene/Model/Entity.hpp Scene/Model/Entity.cpp
	Scene/Model/EntityManager.hpp
	Scene/Model/Explosion.hpp Scene/Model/Explosion.cpp
	Scene/Model/GameModelManager.hpp Scene/Model/GameModelManager.cpp
	Scene/Model/MenuModelManager.hpp Scene/Model/MenuModelManager.cpp
	Scene/Model/Mob.hpp Scene/Model/Mob.cpp
	Scene/Model/ModelManager.hpp Scene/Model/ModelManager.cpp
	Scene/Model/Particle.hpp Scene/Model/Particle.cpp
	Scene/Model/Projectile.hpp Scene/Model/Projectile.cpp
	Scene/Widget/Widget.hpp Scene/Widget/Widget.cpp
	Scene/Widget/WidgetManager.hpp Scene/Widget/WidgetManager.cpp
)

target_include_directories(${EXECUTABLE_NAME} PUBLIC ${SDL2_INCLUDE_DIR})

# There may be some additional dependencies which you may have to specify for the project, which you may do as in following lines.
# Note that first parameter is the executable name.
target_link_libraries(${EXECUTABLE_NAME} ${SDL2_LIBRARIES})