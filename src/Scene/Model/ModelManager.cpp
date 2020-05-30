#include "ModelManager.hpp"

#include "../../ui/UiManager.hpp"

ModelManager::ModelManager(float initialModelScale)
        : camera(initialModelScale) {

    modelTick = 0;
}
ModelManager::~ModelManager() {}

uint32_t ModelManager::getModelTick() const {
    return modelTick;
}

void ModelManager::updateOneTick() {}
void ModelManager::doTick() {
    updateOneTick();
    ++modelTick;
}

void ModelManager::pickSelectedEntity(float x, float y) {}
void ModelManager::click() {}
void ModelManager::releaseMouse() {}

void ModelManager::draw(UiManager &uiManager) {}
