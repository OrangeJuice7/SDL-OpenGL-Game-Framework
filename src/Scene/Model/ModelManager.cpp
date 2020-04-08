#include "ModelManager.hpp"

#include "../../MainUiManager/MainUiManager.hpp"

ModelManager::ModelManager(float initialModelScale) {
    this->initialModelScale = initialModelScale;
    resetCamera();

    modelTick = 0;
}
ModelManager::~ModelManager() {}

uint32_t ModelManager::getModelTick() {
    return modelTick;
}
float ModelManager::getModelScale() {
    return modelScale;
}
float ModelManager::getCameraX() {
    return cameraX;
}
float ModelManager::getCameraY() {
    return cameraY;
}

void ModelManager::updateOneTick() {}
void ModelManager::doTick() {
    updateOneTick();
    ++modelTick;
}

void ModelManager::screenToGameCoords(const SDL_Rect &screenRect, float& gameX, float& gameY, int screenX, int screenY) const {
    gameX = (screenX - screenRect.w/2)/modelScale + cameraX;
    gameY = (screenRect.h/2 - screenY)/modelScale + cameraY;
}
void ModelManager::gameToScreenCoords(const SDL_Rect &screenRect, int& screenX, int& screenY, float gameX, float gameY) const {
    screenX = screenRect.w/2 + (gameX - cameraX)*modelScale;
    screenY = screenRect.h/2 - (gameY - cameraY)*modelScale;
}
float ModelManager::gameToScreenLength(float gameLength) const {
    return gameLength * modelScale;
}

void ModelManager::resetCamera() {
    modelScale = initialModelScale;
    cameraX = cameraY = 0;
}
void ModelManager::moveCamera(float x, float y) {
    cameraX += x;
    cameraY += y;
}
void ModelManager::scaleCamera(float scale) {
    // Can add some limits to the scale here
    modelScale *= scale;
}

void ModelManager::pickActiveEntity(float x, float y) {}
void ModelManager::click() {}
void ModelManager::releaseMouse() {}

std::function<void(int&, int&, float, float)> ModelManager::getGameToScreenCoordsFunc(MainUiManager *uiManager) {
    return [=](int& screenX, int& screenY, float gameX, float gameY) {
        gameToScreenCoords(uiManager->SCREEN_RECT, screenX, screenY, gameX, gameY);
    };
}
std::function<float(float)> ModelManager::getGameToScreenLengthFunc() {
    return [=](float gameLength) -> float {
        return gameToScreenLength(gameLength);
    };
}
void ModelManager::draw(MainUiManager *uiManager) {}
