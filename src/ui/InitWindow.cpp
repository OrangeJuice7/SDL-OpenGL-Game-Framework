#include "UiManager.hpp"

#include <cstdio>

bool UiManager::initWindow() {
    mainWindow = SDL_CreateWindow(
            WINDOW_TITLE,
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    if (mainWindow == NULL) {
        return false;
    }

    // Disable showing the standard cursor, since we're rendering our own custom one
    if (SDL_ShowCursor(SDL_DISABLE) < 0) {
        printf("Could not disable cursor! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

void UiManager::deinitWindow() {
    SDL_DestroyWindow(mainWindow);
    mainWindow = NULL;
}
