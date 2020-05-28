#include "UiManager.hpp"

// For screenshots
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

#include <cstdio>
#include "../Scene/Scene.hpp"

UiManager::UiManager(const char *windowTitle, int screenWidth, int screenHeight)
        : shaderProgram()
        , spriteManager()
        , textManager()
        , mouseState()
        , keyboardState()
        , _dummy_camera(1)
        , WINDOW_TITLE(windowTitle)
        , SCREEN_WIDTH(screenWidth)
        , SCREEN_HEIGHT(screenHeight)
        , SCREEN_HALF_WIDTH(SCREEN_WIDTH / 2.f)
        , SCREEN_HALF_HEIGHT(SCREEN_HEIGHT / 2.f)
        , SCREEN_RECT{0, 0, SCREEN_WIDTH, SCREEN_HEIGHT} {

    mainWindow = nullptr;
    camera = &_dummy_camera;
    orthoMode = false;
    isFullscreen = false;

    uiTick = 0;
    fps = 0;
}
UiManager::~UiManager() {}

Uint32 UiManager::getUiTick() const {
    return uiTick;
}
bool UiManager::getIsFullscreen() const {
    return isFullscreen;
}

Sprite* UiManager::getSprite(SpriteId id) const {
    return spriteManager.getSprite(id);
}

void UiManager::screenToGameCoords(float& gameX, float& gameY, float screenX, float screenY) {
    gameX = (screenX - SCREEN_HALF_WIDTH )/camera->getScale() + camera->getX();
    gameY = (screenY - SCREEN_HALF_HEIGHT)/camera->getScale() + camera->getY();
}
void UiManager::gameToScreenCoords(float& screenX, float& screenY, float gameX, float gameY) {
    screenX = (gameX - camera->getX())*camera->getScale() + SCREEN_HALF_WIDTH ;
    screenY = (gameY - camera->getY())*camera->getScale() + SCREEN_HALF_HEIGHT;
}

void UiManager::sleep(float duration) {
    SDL_Delay(duration*1000);
}

void UiManager::setFullscreen() {
    if (SDL_SetWindowFullscreen(mainWindow, SDL_WINDOW_FULLSCREEN) < 0) {
        printf("Could not set to fullscreen mode! SDL_Error: %s\n", SDL_GetError());
        return;
    }
    isFullscreen = true;
}
void UiManager::setWindowed() {
    if (SDL_SetWindowFullscreen(mainWindow, 0) < 0) {
        printf("Could not set to windowed mode! SDL_Error: %s\n", SDL_GetError());
        return;
    }
    isFullscreen = false;
}
void UiManager::toggleFullscreen() {
    if (isFullscreen) setWindowed();
    else setFullscreen();
}

void UiManager::draw(Scene* scene) {
    // Clear color buffer
    glClear(GL_COLOR_BUFFER_BIT);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw the scene
    scene->draw(*this);

    // Draw the cursor
    setDrawToScreenSpace();
    setObjectScale(32);
    drawSprite(mouseState.x, mouseState.y, SPRITE_ID_CURSOR);

    //Update screen
    SDL_GL_SwapWindow(mainWindow);

    ++uiTick;
}

void UiManager::saveScreenshot(const char* filename) {
    char fullFilename[256];
    sprintf(fullFilename, "%s.bmp", filename);

    // Collect screen data
    GLubyte *data = (GLubyte*)malloc(3 * SCREEN_WIDTH * SCREEN_HEIGHT);
    glReadPixels(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, data);

    // Note: PNG file saving is not optimally compressed. Also has a "stride_in_bytes" param which idk how to use
    stbi_flip_vertically_on_write(1);
    stbi_write_bmp(fullFilename, SCREEN_WIDTH, SCREEN_HEIGHT, 3, data);

    // Free data
    free(data);
}
