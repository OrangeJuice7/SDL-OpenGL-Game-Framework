#ifndef SCENE_HPP
#define SCENE_HPP

#include <SDL.h>
#include <vector>
class MainUiManager;
class Widget;

class Scene {
    protected:
        /**  UI  **/
        // Use a WidgetManager?
        std::vector<Widget*> widgets;
        Widget* activeWidget;

        void loadWidget(Widget* widget);
        //virtual void loadWidgets(); // doesn't work in the constructor
        void unloadWidgets();

        void drawGui(MainUiManager *uiManager);

        /**  Model  **/
        //

        //int cameraX, cameraY;

        //virtual void drawModel(MainUiManager *uiManager);

        Uint32 modelTick;
        bool paused;

        virtual void updateOneTick();

    public:
        Scene();
        virtual ~Scene();

        /**  UI  **/
        // Basically updates the active elements e.g. activeWidget
        virtual void updateFromMouse(int mousePosX, int mousePosY);

        // Sends Messages to MainApp
        virtual void handleKeyDownEvent(SDL_Keycode key);
        virtual void handleKeyUpEvent(SDL_Keycode key);
        virtual void handleMouseLDownEvent();
        virtual void handleMouseRDownEvent();
        //virtual void handleMouseLUpEvent();
        //virtual void handleMouseRUpEvent();

        // Draws to the uiManager (called by the uiManager)
        void draw(MainUiManager *uiManager);

        /**  Model  **/
        Uint32 getModelTick();
        void doTick();
};

#endif // SCENE_HPP
