#include "MainUiManager.hpp"

#include <cmath>
#include "../Scene/Scene.hpp"

MainUiManager::MainUiManager(const char *windowTitle, int screenWidth, int screenHeight)
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
    renderer = NULL;

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

    setDrawToGameSpace();
    setMapScale(64);

    setObjectScale(1 + .8f*sin(uiTick*.01618f +.8f));
    drawSprite(-3 + sin(uiTick*.01f +.8f), .5f*cos(uiTick*.01f +.8f), SPRITE_ID_TEX1);

    setObjectScale(1 + .2f*sin(uiTick*.01618f));
    drawSprite(.5f*cos(uiTick*.01f +.4f), 1 - sin(uiTick*.01f +.4f), SPRITE_ID_GEOM);

    setObjectScale(1);
    drawSprite(3 + sin(uiTick*.01f), .5f*cos(uiTick*.01f), SPRITE_ID_TEX1);

    setObjectScale(1);
    drawSprite(3 + sin(uiTick*.01f +.3f), 3 + .5f*cos(uiTick*.01f +.3f), SPRITE_ID_TEX2);

    setObjectScale(1);
    drawSprite(-3 + sin(uiTick*.01f), 1 + .5f*cos(uiTick*.01f), SPRITE_ID_TEX3);

    setObjectScale(1);
    drawSprite(-3 + sin(uiTick*.015f), -2 + cos(uiTick*.015f), SPRITE_ID_TEX4);

    setDrawToScreenSpace();

    setFont(FONT_ID_STANDARD, FONTSIZE_ID_SMALL);
    drawText(0, 0, "The quick brown fox: 1234567890DQIl");
    setFont(FONT_ID_STANDARD, FONTSIZE_ID_NORMAL);
    drawText(0, 32, "The quick brown fox: 1234567890DQIl");
    setFont(FONT_ID_STANDARD, FONTSIZE_ID_SUBHEADING);
    drawText(0, 64, "The quick brown fox: 1234567890DQIl");
    setFont(FONT_ID_STANDARD, FONTSIZE_ID_HEADING);
    drawText(0, 96, "The quick brown fox: 1234567890DQIl");

    setFont(FONT_ID_MONOSPACE, FONTSIZE_ID_SMALL);
    drawText(0, 200, "The quick brown fox: 1234567890DQIl");
    setFont(FONT_ID_MONOSPACE, FONTSIZE_ID_NORMAL);
    drawText(0, 232, "The quick brown fox: 1234567890DQIl");
    setFont(FONT_ID_MONOSPACE, FONTSIZE_ID_SUBHEADING);
    drawText(0, 264, "The quick brown fox: 1234567890DQIl");
    setFont(FONT_ID_MONOSPACE, FONTSIZE_ID_HEADING);
    drawText(0, 296, "The quick brown fox: 1234567890DQIl");

    //Update screen
    SDL_GL_SwapWindow(mainWindow);

    ++uiTick;
}
