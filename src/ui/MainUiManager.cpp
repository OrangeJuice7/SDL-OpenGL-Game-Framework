#include "MainUiManager.hpp"

#include "../Scene/Scene.hpp"

MainUiManager::MainUiManager(const char *windowTitle, int screenWidth, int screenHeight)
        : shaderProgram()
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

    //Reset transformations
    //glLoadIdentity();

    // scene->draw(this);
    sprite.draw();

    //Update screen
    SDL_GL_SwapWindow(mainWindow);

    ++uiTick;
}
