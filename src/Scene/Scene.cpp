#include "Scene.hpp"

#include "../MainUiManager/MainUiManager.hpp"
#include "Widget/Widget.hpp"

Scene::Scene() {
    //loadWidgets(); // virtual members should not be called in constructors

    activeWidget = nullptr;

	modelTick = 0;
    paused = false;
}
Scene::~Scene() {
	unloadWidgets();
}

void Scene::loadWidget(Widget* widget) {
	widgets.push_back(widget);
}
//void Scene::loadWidgets() {} // Load no widgets
void Scene::unloadWidgets() {
	for (Widget* widget : widgets) {
		delete widget;
	}
	widgets.clear();
}

Uint32 Scene::getModelTick() {
    return modelTick;
}

void Scene::doTick() {
    if (paused) return;

    updateOneTick();
    ++modelTick;
}

void Scene::updateFromMouse(int mousePosX, int mousePosY) {
    if (activeWidget) {
        Widget* pWidget = activeWidget->checkOn(mousePosX, mousePosY);
        if (pWidget == activeWidget) // Active Widget remains active
            return;
        else if (pWidget) { // It's now a child widget that is active
            activeWidget->deactivate();
            pWidget->activate();
            activeWidget = pWidget;
            return;
        } else { // Active Widget is no longer active
            activeWidget->deactivate();
            activeWidget = nullptr;
        }
    }

    // No activeWidget (or activeWidget got deactivated): Check if any other Widget is activated
    for (Widget* widget : widgets) {
		Widget* pWidget = widget->checkOn(mousePosX, mousePosY);
		if (pWidget) { // A Widget can indeed be activated
            pWidget->activate(); // Activate it
            activeWidget = pWidget; // Track the widget as the new activeWidget
            return; // Nothing more to do
		}
	}

	// Check for Model intercepts
	//
}
void Scene::handleMouseLDownEvent() {
    // If we have an activeWidget, just activate it and we are done
    if (activeWidget) {
        activeWidget->click();
        return;
    }

	// Check for Model intercepts
	//
}

void Scene::drawGui(MainUiManager *uiManager) {
    for (Widget* widget : widgets) {
		widget->update(uiManager->SCREEN_RECT);
	}
    for (Widget* widget : widgets) {
		widget->draw(uiManager);
	}
}
void Scene::draw(MainUiManager *uiManager) {
    drawGui(uiManager);
    //drawModel(uiManager);
}

// Do nothing
void Scene::handleKeyDownEvent(SDL_Keycode key) {}
void Scene::handleKeyUpEvent(SDL_Keycode key) {}
void Scene::handleMouseRDownEvent() {}
void Scene::updateOneTick() {}
