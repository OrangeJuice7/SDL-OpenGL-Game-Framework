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

    //Reset transformations
    glLoadIdentity();

    //glTranslatef(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f, 0);
    glBegin(GL_QUADS);
        glColor3f(0.f, 1.f, 1.f);
        /*glVertex2f(-50.f, -50.f);
        glVertex2f( 50.f, -50.f);
        glVertex2f( 50.f,  50.f);
        glVertex2f(-50.f,  50.f);*/
        glVertex2f(-0.2f, -0.2f);
        glVertex2f( 0.2f, -0.2f);
        glVertex2f( 0.2f,  0.2f);
        glVertex2f(-0.2f,  0.2f);
    glEnd();

    // Enable vertex position
    /*glEnableVertexAttribArray(glVertexPos2DLocation);

    // Set vertex data
    glBindBuffer(GL_ARRAY_BUFFER, glVBO);
    glVertexAttribPointer(glVertexPos2DLocation, 2, GL_FLOAT, GL_FALSE, 2*sizeof(GLfloat), NULL);

    // Set index data and render
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glIBO);
    glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL);

    // Disable vertex position
    glDisableVertexAttribArray(glVertexPos2DLocation);*/

    //Update screen
    SDL_GL_SwapWindow(mainWindow);

    ++uiTick;
}
