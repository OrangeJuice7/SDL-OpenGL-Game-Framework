#include "ModelManager.hpp"

#include "../../MainUiManager/MainUiManager.hpp"

ModelManager::ModelManager() {
    modelScale = 1;
    cameraX = cameraY = 0;

    modelTick = 0;
}
ModelManager::~ModelManager() {}

uint32_t ModelManager::getModelTick() {
    return modelTick;
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
