#include "Scene.hpp"

#include "Model/ModelManager.hpp"
#include "../ui/UiManager.hpp"

Scene::Scene(ModelManager* modelManager)
        : widgetManager() {

    this->modelManager = modelManager;

    paused = false;
}
Scene::~Scene() {
	delete modelManager;
}

bool Scene::getPaused() const {
    return paused;
}
uint32_t Scene::getModelTick() const {
    return modelManager->getModelTick();
}

void Scene::pause() {
    paused = true;
}
void Scene::unpause() {
    paused = false;
}

void Scene::doTick() {
    // Update Widgets?

    if (!paused) {
        modelManager->doTick();
    }
}

void Scene::handleKeyDownEvent(SDL_Keycode key) {}
void Scene::handleKeyUpEvent(SDL_Keycode key) {}
void Scene::updateFromKeys(const KeyboardState &keyboardState) {}

bool Scene::updateWidgetsFromMouse(const SDL_Rect &screenRect, const MouseState &mouseState) {
    return widgetManager.pickSelectedWidget(mouseState.x, mouseState.y);
}
void Scene::updateModelFromMouse(const SDL_Rect &screenRect, const MouseState &mouseState) {
    modelManager->pickSelectedEntity(mouseState.gameX, mouseState.gameY);
}
void Scene::updateFromMouse(const SDL_Rect &screenRect, const MouseState &mouseState) {
	// Check for Widget intercepts
    if ( updateWidgetsFromMouse(screenRect, mouseState) ) return;

	// Check for Model intercepts
	updateModelFromMouse(screenRect, mouseState);
}

void Scene::handleMouseLDownEvent() {
    // If we have a selectedWidget, just click it and we are done
    if ( widgetManager.click() ) return;

	// Check for Model intercepts
	modelManager->click();
}
void Scene::handleMouseLUpEvent() {
    // If we have a selectedWidget, just release it and we are done
    if ( widgetManager.releaseMouse() ) return;

	// Check for Model intercepts
	modelManager->releaseMouse();
}
void Scene::handleMouseRDownEvent() {}
void Scene::handleMouseRUpEvent() {}
void Scene::handleMouseMDownEvent() {}
void Scene::handleMouseMUpEvent() {}
void Scene::handleMouseWheelEvent(Sint32 delta) {}

void Scene::draw(UiManager &uiManager) {
    // Assign camera
    // (Would it be better to do this on Scene load, rather than per draw call?)
    uiManager.setCamera(modelManager->camera);

    // Draw model first
    uiManager.setDrawToGameSpace();
    modelManager->draw(uiManager);

    // Draw widgets on top
    uiManager.setDrawToScreenSpace();
    widgetManager.draw(uiManager);
}
