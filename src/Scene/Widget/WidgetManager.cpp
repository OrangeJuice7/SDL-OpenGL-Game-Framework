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
    // Deselect the selectedWidget if it exists
    if (selectedWidget) {
        selectedWidget->deselect();
        selectedWidget = nullptr;
    }

    // Scan for widgets in reverse order
    for (auto rit = widgets.rbegin(); rit != widgets.rend(); ++rit) {
		Widget* widget = *rit;
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
