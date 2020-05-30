#ifndef WIDGET_MANAGER_HPP
#define WIDGET_MANAGER_HPP

#include <vector>
class UiManager;
class Widget;

class WidgetManager {
    protected:
        std::vector<Widget*> widgets;
        Widget* selectedWidget;

    public:
        WidgetManager();
        ~WidgetManager();

        void loadWidget(Widget* widget); // Note: load the widgets in the order that they are drawn, i.e. widgets drawn on top are loaded last
        void unloadWidgets();

        // returns true if there is a widget under (x,y)
        bool pickSelectedWidget(int x, int y);
        // returns true if there is a selectedWidget
        bool click();
        bool releaseMouse();

        void draw(UiManager &uiManager);
};

#endif // WIDGET_MANAGER_HPP

