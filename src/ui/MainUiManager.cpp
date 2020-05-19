#include "MainUiManager.hpp"

#include <cmath>
#include "../Scene/Scene.hpp"

GLvertex2 vertices[] = { {-1,-1}, {1,-1}, {-1,1}, {1,1} };
GLcolorRGB colors[] = { {0,0,1}, {0,1,0}, {1,0,1}, {1,1,0} };
void spriteDrawfunc() {
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

MainUiManager::MainUiManager(const char *windowTitle, int screenWidth, int screenHeight)
        : shaderProgram()
        , texSprite()
        , geomSprite(4, vertices, colors, spriteDrawfunc)
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

void MainUiManager::draw(Scene* scene) {
    // Clear color buffer
    glClear(GL_COLOR_BUFFER_BIT);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // scene->draw(this);
    setTranslate(2 + sin(uiTick*.1f), .5f*cos(uiTick*.1f));
    setObjectScale(.6f);
    texSprite.draw();

    setTranslate(-2 + sin(uiTick*.1f +.8f), .5f*cos(uiTick*.1f +.8f));
    setObjectScale(1);
    texSprite.draw();

    setTranslate(.5f*cos(uiTick*.1f +.4f), 1 - sin(uiTick*.1f +.4f));
    setObjectScale(1 + .2f*sin(uiTick*.1618f));
    geomSprite.draw();

    //Update screen
    SDL_GL_SwapWindow(mainWindow);

    ++uiTick;
}
