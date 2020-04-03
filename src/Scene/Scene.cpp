#include "Scene.hpp"

#include "../MainUiManager/MainUiManager.hpp"
#include "Widget/Widget.hpp"
#include "Model/ModelManager.hpp"

Scene::Scene(ModelManager* modelManager) {
    //loadWidgets(); // virtual members should not be called in constructors

    activeWidget = nullptr;

    this->modelManager = modelManager;

    paused = false;
}
Scene::~Scene() {
	delete modelManager;
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

uint32_t Scene::getModelTick() {
    return modelManager->getModelTick();
}

void Scene::doTick() {
    // Update Widgets?

    if (!paused) {
        modelManager->doTick();
    }
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
	modelManager->pickActiveEntity(mousePosX, mousePosY);
}
void Scene::handleMouseLDownEvent() {
    // If we have an activeWidget, just activate it and we are done
    if (activeWidget) {
        activeWidget->click();
        return;
    }

	// Check for Model intercepts
	modelManager->click();
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
    modelManager->draw(uiManager);
}

// Do nothing
void Scene::handleKeyDownEvent(SDL_Keycode key) {}
void Scene::handleKeyUpEvent(SDL_Keycode key) {}
void Scene::handleMouseRDownEvent() {}
