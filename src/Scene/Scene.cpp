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

void Scene::updateFromMouse(const SDL_Rect &screenRect, int mousePosX, int mousePosY, bool LMouseDown, bool RMouseDown) {
	// Do not update the active element if the mouse is currently being held down, to preserve the existing active element (if any)
	if (LMouseDown) return;

	// Check for Widget intercepts
    if ( widgetManager.pickActiveWidget(mousePosX, mousePosY) ) return;

	// Check for Model intercepts
	{   float gameX, gameY;
        modelManager->screenToGameCoords(screenRect, gameX, gameY, mousePosX, mousePosY);
        modelManager->pickActiveEntity(gameX, gameY);
	}
}
void Scene::handleMouseLDownEvent() {
    // If we have an activeWidget, just activate it and we are done
    if ( widgetManager.click() ) return;

	// Check for Model intercepts
	modelManager->click();
}
void Scene::handleMouseRDownEvent() {}
void Scene::handleMouseLUpEvent() {
    // If we have an activeWidget, just release it and we are done
    if ( widgetManager.releaseMouse() ) return;

	// Check for Model intercepts
	modelManager->releaseMouse();
}
void Scene::handleMouseRUpEvent() {}

void Scene::draw(MainUiManager *uiManager) {
    modelManager->draw(uiManager); // draw model first
    widgetManager.draw(uiManager); // draw widgets on top
}
