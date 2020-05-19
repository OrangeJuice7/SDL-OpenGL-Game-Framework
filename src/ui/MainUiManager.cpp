#include "MainUiManager.hpp"

#include <cmath>
#include "../Scene/Scene.hpp"

GLvertex2 vertices[] = { {-1,-1}, {1,-1}, {-1,1}, {1,1} };
GLcolorRGBA colors[] = { {0,0,1,.5f}, {0,1,0,1}, {1,0,1,1}, {1,1,0,1} };
void spriteDrawfunc() {
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

MainUiManager::MainUiManager(const char *windowTitle, int screenWidth, int screenHeight)
        : shaderProgram()
        , texSprite()
        , texSprite2()
        , texSprite3()
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

    setTranslate(-3 + sin(uiTick*.01f +.8f), .5f*cos(uiTick*.01f +.8f));
    //setTranslate(-3, 0);
    setObjectScale(1 + .8f*sin(uiTick*.01618f +.8f));
    texSprite.draw();

    setTranslate(.5f*cos(uiTick*.01f +.4f), 1 - sin(uiTick*.01f +.4f));
    //setTranslate(0, 2);
    setObjectScale(1 + .2f*sin(uiTick*.01618f));
    geomSprite.draw();

    setTranslate(3 + sin(uiTick*.01f), .5f*cos(uiTick*.01f));
    //setTranslate(3, 0);
    setObjectScale(1);
    texSprite.draw();

    setTranslate(3 + sin(uiTick*.01f +.3f), 3 + .5f*cos(uiTick*.01f +.3f));
    setObjectScale(1);
    texSprite2.draw();

    setTranslate(-3 + sin(uiTick*.01f), 1 + .5f*cos(uiTick*.01f));
    setObjectScale(1);
    texSprite3.draw();

    //Update screen
    SDL_GL_SwapWindow(mainWindow);

    ++uiTick;
}
