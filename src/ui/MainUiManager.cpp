#include "MainUiManager.hpp"

#include <cmath>
#include "../Scene/Scene.hpp"

MainUiManager::MainUiManager(const char *windowTitle, int screenWidth, int screenHeight)
        : shaderProgram()
        , spriteManager()
        , mouseState()
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

Sprite* MainUiManager::getSprite(SpriteId id) {
    return spriteManager.getSprite(id);
}

void MainUiManager::draw(Scene* scene) {
    // Clear color buffer
    glClear(GL_COLOR_BUFFER_BIT);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // scene->draw(this);

    setTranslate(-3 + sin(uiTick*.01f +.8f), .5f*cos(uiTick*.01f +.8f));
    setObjectScale(1 + .8f*sin(uiTick*.01618f +.8f));
    getSprite(SPRITE_ID_TEX1)->draw();

    setTranslate(.5f*cos(uiTick*.01f +.4f), 1 - sin(uiTick*.01f +.4f));
    setObjectScale(1 + .2f*sin(uiTick*.01618f));
    getSprite(SPRITE_ID_GEOM)->draw();

    setTranslate(3 + sin(uiTick*.01f), .5f*cos(uiTick*.01f));
    setObjectScale(1);
    getSprite(SPRITE_ID_TEX1)->draw();

    setTranslate(3 + sin(uiTick*.01f +.3f), 3 + .5f*cos(uiTick*.01f +.3f));
    setObjectScale(1);
    getSprite(SPRITE_ID_TEX2)->draw();

    setTranslate(-3 + sin(uiTick*.01f), 1 + .5f*cos(uiTick*.01f));
    setObjectScale(1);
    getSprite(SPRITE_ID_TEX3)->draw();

    setTranslate(-3 + sin(uiTick*.015f), -2 + cos(uiTick*.015f));
    setObjectScale(1);
    getSprite(SPRITE_ID_TEX4)->draw();

    //Update screen
    SDL_GL_SwapWindow(mainWindow);

    ++uiTick;
}
