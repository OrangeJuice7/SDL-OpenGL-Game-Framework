#include "MainUiManager.hpp"

#include "../Scene/Scene.hpp"

MainUiManager::MainUiManager()
        : WINDOW_TITLE("[PROJECT TITLE]")
        , SCREEN_WIDTH(1080)
        , SCREEN_HEIGHT(720)
        , SCREEN_RECT{0, 0, SCREEN_WIDTH, SCREEN_HEIGHT} {

    mainWindow = NULL;
    renderer = NULL;

    mainFont = NULL;

    mousePosX = mousePosY = 0;

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

    //Update screen
    SDL_RenderPresent(renderer);

    ++uiTick;
}
