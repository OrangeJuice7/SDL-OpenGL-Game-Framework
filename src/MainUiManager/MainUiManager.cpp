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

    glProgramID = 0;
    glVertexPos2DLocation = -1;
    glVBO = 0;
    glIBO = 0;

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
    // Clear screen
    /*SDL_RenderClear(renderer);

    scene->draw(this);

    // Set background to blue
    SDL_SetRenderDrawColor(renderer, 0x08, 0x10, 0x20, 0xFF);

    // Update screen
    SDL_RenderPresent(renderer);*/

    // Clear color buffer
    glClear(GL_COLOR_BUFFER_BIT);

    // Bind shader program
    glUseProgram(glProgramID);

    // Enable vertex position
    glEnableVertexAttribArray(glVertexPos2DLocation);

    // Set vertex data
    glBindBuffer(GL_ARRAY_BUFFER, glVBO);
    glVertexAttribPointer(glVertexPos2DLocation, 2, GL_FLOAT, GL_FALSE, 2*sizeof(GLfloat), NULL);

    // Set index data and render
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glIBO);
    glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL);

    // Disable vertex position
    glDisableVertexAttribArray(glVertexPos2DLocation);

    // Unbind shader program
    glUseProgram(0);

    //Update screen
    SDL_GL_SwapWindow(mainWindow);

    ++uiTick;
}
