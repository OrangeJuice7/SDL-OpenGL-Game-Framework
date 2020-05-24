#include "UiManager.hpp"

bool UiManager::initSDL() {
    return (SDL_Init(SDL_INIT_VIDEO) == 0);
}

void UiManager::deinitSDL() {
    SDL_Quit();
}
