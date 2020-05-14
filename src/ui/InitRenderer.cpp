#include "MainUiManager.hpp"

#include <cstdio>

bool MainUiManager::initRenderer() {
    renderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

void MainUiManager::deinitRenderer() {
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
}
