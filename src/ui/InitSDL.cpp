#include "MainUiManager.hpp"

bool MainUiManager::initSDL() {
    return (SDL_Init(SDL_INIT_VIDEO) == 0);
}

void MainUiManager::deinitSDL() {
    SDL_Quit();
}
