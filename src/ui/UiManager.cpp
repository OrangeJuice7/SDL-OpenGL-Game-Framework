#include "UiManager.hpp"

#include <cmath>
#include "../Scene/Scene.hpp"

UiManager::UiManager(const char *windowTitle, int screenWidth, int screenHeight)
        : shaderProgram()
        , spriteManager()
        , textManager()
        , mouseState()
        , keyboardState()
        , WINDOW_TITLE(windowTitle)
        , SCREEN_WIDTH(screenWidth)
        , SCREEN_HEIGHT(screenHeight)
        , SCREEN_RECT{0, 0, SCREEN_WIDTH, SCREEN_HEIGHT} {

    mainWindow = NULL;

    uiTick = 0;
    fps = 0;
}
UiManager::~UiManager() {}

Uint32 UiManager::getUiTick() {
    return uiTick;
}

void UiManager::sleep(float duration) {
    SDL_Delay(duration*1000);
}

Sprite* UiManager::getSprite(SpriteId id) {
    return spriteManager.getSprite(id);
}

void UiManager::draw(Scene* scene) {
    // Clear color buffer
    glClear(GL_COLOR_BUFFER_BIT);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    scene->draw(this);

    //Update screen
    SDL_GL_SwapWindow(mainWindow);

    ++uiTick;
}
