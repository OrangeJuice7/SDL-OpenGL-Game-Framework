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
        Widget* activeWidget;// (NOTE: Is not accurate when Widgets can move about, or with Scene transitions)

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

        // Sends Messages to MainApp
        virtual void handleKeyDownEvent(SDL_Keycode key);
        virtual void handleKeyUpEvent(SDL_Keycode key);
        virtual void handleMouseMoveEvent(int mousePosX, int mousePosY);
        virtual void handleMouseLDownEvent(int mousePosX, int mousePosY);
        virtual void handleMouseRDownEvent(int mousePosX, int mousePosY);
        //virtual void handleMouseLUpEvent(int mousePosX, int mousePosY);
        //virtual void handleMouseRUpEvent(int mousePosX, int mousePosY);

        // Draws to the uiManager (called by the uiManager)
        void draw(MainUiManager *uiManager);

        /**  Model  **/
        Uint32 getModelTick();
        void doTick();
};

#endif // SCENE_HPP
