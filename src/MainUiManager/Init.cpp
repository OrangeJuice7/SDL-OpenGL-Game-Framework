#include "MainUiManager.hpp"

#include <cstdio>

bool MainUiManager::init() {
    if(!initSDL()) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    if(!initWindow()) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    if(!initRenderer()) {
        return false;
    }

    if(!initFont()) {
        return false;
    }

    if(!initTextures()) {
        return false;
    }

    return true;
}

void MainUiManager::deinit() {
    deinitTextures();
    deinitFont();
    deinitRenderer();
    deinitWindow();
    deinitSDL();
}
