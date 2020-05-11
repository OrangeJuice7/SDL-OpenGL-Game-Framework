#include "MainUiManager.hpp"

bool MainUiManager::initWindow() {
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

    return true;
}

void MainUiManager::deinitWindow() {
    SDL_DestroyWindow(mainWindow);
    mainWindow = NULL;
}
