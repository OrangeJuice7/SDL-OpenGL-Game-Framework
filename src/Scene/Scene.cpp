#include "Scene.hpp"

#include "Model/ModelManager.hpp"

Scene::Scene(ModelManager* modelManager)
        : widgetManager() {

    this->modelManager = modelManager;

    paused = false;
}
Scene::~Scene() {
	delete modelManager;
}

uint32_t Scene::getModelTick() {
    return modelManager->getModelTick();
}

void Scene::doTick() {
    // Update Widgets?

    if (!paused) {
        modelManager->doTick();
    }
}

void Scene::handleKeyDownEvent(SDL_Keycode key) {}
void Scene::handleKeyUpEvent(SDL_Keycode key) {}

void Scene::updateFromMouse(int mousePosX, int mousePosY) {
	// Check for Widget intercepts
    if ( widgetManager.pickActiveWidget(mousePosX, mousePosY) ) return;

	// Check for Model intercepts
	modelManager->pickActiveEntity(mousePosX, mousePosY);
}
void Scene::handleMouseLDownEvent() {
    // If we have an activeWidget, just activate it and we are done
    if ( widgetManager.click() ) return;

	// Check for Model intercepts
	modelManager->click();
}
void Scene::handleMouseRDownEvent() {}

void Scene::draw(MainUiManager *uiManager) {
    widgetManager.draw(uiManager);
    modelManager->draw(uiManager);
}
