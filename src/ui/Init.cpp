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

    if(!spriteManager.init()) {
        printf("Could not initialize textures and sprites!\n");
        return false;
    }

    if(!initFont()) {
        printf("Could not initialize font!\n");
        return false;
    }

    return true;
}

void MainUiManager::deinit() {
    deinitFont();
    spriteManager.deinit();
    deinitOpenGL();
    deinitRenderer();
    deinitWindow();
    deinitSDL();
}
