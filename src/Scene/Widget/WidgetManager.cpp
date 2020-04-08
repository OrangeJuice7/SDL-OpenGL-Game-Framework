#include "WidgetManager.hpp"

#include "../../MainUiManager/MainUiManager.hpp"
#include "Widget.hpp"

WidgetManager::WidgetManager() {
    activeWidget = nullptr;
}
WidgetManager::~WidgetManager() {
    unloadWidgets();
}

void WidgetManager::loadWidget(Widget* widget) {
	widgets.push_back(widget);
}

void WidgetManager::unloadWidgets() {
	for (Widget* widget : widgets) {
		delete widget;
	}
	widgets.clear();
    activeWidget = nullptr;
}

bool WidgetManager::pickActiveWidget(int x, int y) {
    if (activeWidget) {
        Widget* pWidget = activeWidget->checkOn(x, y);
        if (pWidget == activeWidget) // Active Widget remains active
            return true;
        else if (pWidget) { // It's now a child widget that is active
            activeWidget->deactivate();
            pWidget->activate();
            activeWidget = pWidget;
            return true;
        } else { // Active Widget is no longer active
            activeWidget->deactivate();
            activeWidget = nullptr;
        }
    }

    // No activeWidget (or activeWidget got deactivated): Check if any other Widget is activated
    for (Widget* widget : widgets) {
		Widget* pWidget = widget->checkOn(x, y);
		if (pWidget) { // A Widget can indeed be activated
            pWidget->activate(); // Activate it
            activeWidget = pWidget; // Track the widget as the new activeWidget
            return true; // Nothing more to do
		}
	}

	return false;
}
bool WidgetManager::click() {
    if (activeWidget) {
        activeWidget->click();
        return true;
    }
    return false;
}
bool WidgetManager::releaseMouse() {
    if (activeWidget) {
        activeWidget->releaseMouse();
        return true;
    }
    return false;
}

void WidgetManager::draw(MainUiManager *uiManager) {
    for (Widget* widget : widgets) {
		widget->update(uiManager->SCREEN_RECT);
	}
    for (Widget* widget : widgets) {
		widget->draw(uiManager);
	}
}
