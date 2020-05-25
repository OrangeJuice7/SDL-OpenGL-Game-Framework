#include "Scene.hpp"

#include "Model/ModelManager.hpp"
#include "../Ui/UiManager.hpp"

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

void Scene::updateFromMouse(const SDL_Rect &screenRect, const MouseState &mouseState) {
	// Do not update the active element if the mouse is currently being held down, to preserve the existing active element (if any)
	if (mouseState.isLDown) return;

	// Check for Widget intercepts
    if ( widgetManager.pickActiveWidget(mouseState.x, mouseState.y) ) return;

	// Check for Model intercepts
	{   float gameX, gameY;
        modelManager->screenToGameCoords(screenRect, gameX, gameY, mouseState.x, mouseState.y);
        modelManager->pickActiveEntity(gameX, gameY);
	}
}
void Scene::updateFromKeys(const KeyboardState &keyboardState) {}
void Scene::handleMouseLDownEvent() {
    // If we have an activeWidget, just activate it and we are done
    if ( widgetManager.click() ) return;

	// Check for Model intercepts
	modelManager->click();
}
void Scene::handleMouseLUpEvent() {
    // If we have an activeWidget, just release it and we are done
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
    // Draw model first
    uiManager.setDrawToGameSpace();
    modelManager->draw(uiManager);

    // Draw widgets on top
    uiManager.setDrawToScreenSpace();
    widgetManager.draw(uiManager);
}
