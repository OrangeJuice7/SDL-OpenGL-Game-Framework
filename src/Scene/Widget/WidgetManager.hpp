#ifndef WIDGET_MANAGER_HPP
#define WIDGET_MANAGER_HPP

#include <vector>
class MainUiManager;
class Widget;

class WidgetManager {
    protected:
        std::vector<Widget*> widgets;
        Widget* activeWidget;

    public:
        WidgetManager();
        ~WidgetManager();

        void loadWidget(Widget* widget);
        void unloadWidgets();

        // returns true if there is a widget under (x,y)
        bool pickActiveWidget(int x, int y);
        // returns true if there is an activeWidget
        bool click();

        void draw(MainUiManager *uiManager);
};

#endif // WIDGET_MANAGER_HPP

