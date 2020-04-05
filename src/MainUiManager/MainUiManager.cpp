#include "MainUiManager.hpp"

#include "../Scene/Scene.hpp"

MainUiManager::MainUiManager(const char *windowTitle, int screenWidth, int screenHeight)
        : mouseState()
        , keyboardState()
        , WINDOW_TITLE(windowTitle)
        , SCREEN_WIDTH(screenWidth)
        , SCREEN_HEIGHT(screenHeight)
        , SCREEN_RECT{0, 0, SCREEN_WIDTH, SCREEN_HEIGHT} {

    mainWindow = NULL;
    renderer = NULL;

    mainFont = NULL;

    uiTick = 0;
    fps = 0;
}
MainUiManager::~MainUiManager() {}

Uint32 MainUiManager::getUiTick() {
    return uiTick;
}

void MainUiManager::sleep(float duration) {
    SDL_Delay(duration*1000);
}

void MainUiManager::draw(Scene* scene) {
    //Clear screen
    SDL_RenderClear(renderer);

    scene->draw(this);

    // Set background to blue
    SDL_SetRenderDrawColor(renderer, 0x08, 0x10, 0x20, 0xFF);

    //Update screen
    SDL_RenderPresent(renderer);

    ++uiTick;
}
