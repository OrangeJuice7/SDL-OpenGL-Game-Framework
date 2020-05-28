#include "UiManager.hpp"

bool UiManager::initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        return false;
    }

    return true;
}

void UiManager::deinitSDL() {
    SDL_Quit();
}
