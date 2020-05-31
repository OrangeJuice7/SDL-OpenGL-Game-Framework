#include "UiManager.hpp"

#include <cstdio>
#include "../system/Settings.hpp"

bool UiManager::initWindow() {
    isFullscreen = Settings::isFullscreen.get();
    setScreenRect(Settings::screenWidth.get(), Settings::screenHeight.get());

    {   Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
        if (isFullscreen) flags |= SDL_WINDOW_FULLSCREEN;

        mainWindow = SDL_CreateWindow(
                WINDOW_TITLE,
                SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED,
                getScreenWidth(),
                getScreenHeight(),
                flags);
    }

    if (mainWindow == NULL) {
        return false;
    }

    {   SDL_DisplayMode mode;
        for (int i = 0; i < SDL_GetNumVideoDisplays(); ++i) {
            SDL_GetCurrentDisplayMode(i, &mode);
            printf("Display #%d: %dx%dpx @ %dhz.\n", i, mode.w, mode.h, mode.refresh_rate);
        }
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
    Settings::screenWidth.set(getScreenWidth());
    Settings::screenHeight.set(getScreenHeight());
}
