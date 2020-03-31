#include "Scene.hpp"

Scene::Scene() {
    modelTick = 0;
    paused = false;
}
Scene::~Scene() {}

Uint32 Scene::getModelTick() {
    return modelTick;
}

void Scene::doTick() {
    if (paused) return;

    updateOneTick();
    ++modelTick;
}

// Do nothing
void Scene::handleKeyDownEvent(SDL_Keycode key) {}
void Scene::handleKeyUpEvent(SDL_Keycode key) {}
void Scene::draw(MainUiManager *uiManager) {}
void Scene::updateOneTick() {}
