#include "UiManager.hpp"

#include <cstdio>
#include "../system/Settings.hpp"

bool UiManager::initWindow() {
    isFullscreen = Settings::isFullscreen.get();

    {   Uint32 flags = SDL_WINDOW_OPENGL;
        if (isFullscreen) flags |= SDL_WINDOW_FULLSCREEN;

        mainWindow = SDL_CreateWindow(
                WINDOW_TITLE,
                SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED,
                SCREEN_WIDTH,
                SCREEN_HEIGHT,
                flags);
    }

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

    Settings::isFullscreen.set(isFullscreen);
}
