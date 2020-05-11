#include "MainUiManager.hpp"

#include <cstdio>

bool MainUiManager::initFont() {
    const char* fontFilename = "data/ARLRDBD.TTF";
    const int fontSize = 20;

    if (TTF_Init() < 0) {
        printf("SDL_TTF could not be initialized! TTF_Error: %s\n", TTF_GetError());
        return false;
    }

    mainFont = TTF_OpenFont(fontFilename, fontSize);
    if (mainFont == NULL) {
        printf("Font file %s could not be loaded! TTF_Error: %s\n", fontFilename, TTF_GetError());
        return false;
    }
    //TTF_SetFontOutline(mainFont, 1);

    return true;
}

void MainUiManager::deinitFont() {
    TTF_Quit();
}
