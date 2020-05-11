#include "MainUiManager.hpp"

#include <cstdio>

bool MainUiManager::init() {
    if(!initSDL()) {
        printf("Could not initialize SDL! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    if(!initWindow()) {
        printf("Could not initialize window! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    if(!initRenderer()) {
        printf("Could not initialize renderer!\n");
        return false;
    }

    if(!initOpenGL()) {
        printf("Could not initialize OpenGL!\n");
        return false;
    }

    if(!initFont()) {
        printf("Could not initialize font!\n");
        return false;
    }

    if(!initTextures()) {
        printf("Could not initialize textures!\n");
        return false;
    }

    return true;
}

void MainUiManager::deinit() {
    deinitTextures();
    deinitFont();
    deinitOpenGL();
    deinitRenderer();
    deinitWindow();
    deinitSDL();
}
