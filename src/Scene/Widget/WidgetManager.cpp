#include "WidgetManager.hpp"

#include "../../ui/UiManager.hpp"
#include "Widget.hpp"

WidgetManager::WidgetManager() {
    selectedWidget = nullptr;
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
    selectedWidget = nullptr;
}

bool WidgetManager::pickSelectedWidget(int x, int y) {
    if (selectedWidget) {
        Widget* pWidget = selectedWidget->checkOn(x, y);
        if (pWidget == selectedWidget) // selectedWidget remains selected
            return true;
        else if (pWidget) { // It's now a child widget that is selected
            selectedWidget->deselect();
            pWidget->select();
            selectedWidget = pWidget;
            return true;
        } else { // selectedWidget is no longer selected
            selectedWidget->deselect();
            selectedWidget = nullptr;
        }
    }

    // No selectedWidget (or selectedWidget got deselected): Check if any other Widget is selected
    for (Widget* widget : widgets) {
		Widget* pWidget = widget->checkOn(x, y);
		if (pWidget) { // A Widget can indeed be selected
            pWidget->select(); // Select it
            selectedWidget = pWidget; // Track the widget as the new selectedWidget
            return true; // Nothing more to do
		}
	}

	return false;
}
bool WidgetManager::click() {
    if (selectedWidget) {
        selectedWidget->click();
        return true;
    }
    return false;
}
bool WidgetManager::releaseMouse() {
    if (selectedWidget) {
        selectedWidget->releaseMouse();
        return true;
    }
    return false;
}

void WidgetManager::draw(UiManager &uiManager) {
    for (Widget* widget : widgets) {
		widget->update(uiManager.getScreenRect());
	}
    for (Widget* widget : widgets) {
		widget->draw(uiManager);
	}
}
