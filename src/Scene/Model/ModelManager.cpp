#include "ModelManager.hpp"

ModelManager::ModelManager() {
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

void ModelManager::pickActiveEntity(int x, int y) {}
void ModelManager::click() {}

void ModelManager::draw(MainUiManager *uiManager) {}
