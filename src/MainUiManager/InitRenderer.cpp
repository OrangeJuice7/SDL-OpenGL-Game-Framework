#include "MainUiManager.hpp"

#include <cstdio>

bool MainUiManager::initRenderer() {
    renderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    // Set background to blue
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x10, 0xFF);

    Texture::setRenderer(renderer);
    return true;
}

void MainUiManager::deinitRenderer() {
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
}
