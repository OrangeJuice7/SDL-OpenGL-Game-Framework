#ifndef SCENE_HPP
#define SCENE_HPP

#include <cstdint>
#include <SDL.h>
#include "Widget/WidgetManager.hpp"
class MainUiManager;
class ModelManager;

class Scene {
    protected:
        WidgetManager widgetManager;
        ModelManager* modelManager;

        bool paused;

    public:
        // modelManager should be a new ModelManager, created when constructing Scene's derived class
        Scene(ModelManager* modelManager);
        virtual ~Scene();

        /**  UI  **/
        // Basically updates the active elements e.g. activeWidget
        virtual void updateFromMouse(const SDL_Rect &screenRect, int mousePosX, int mousePosY, bool LMouseDown, bool RMouseDown);

        // May send Messages to MainApp
        virtual void handleKeyDownEvent(SDL_Keycode key);
        virtual void handleKeyUpEvent(SDL_Keycode key);
        virtual void handleMouseLDownEvent();
        virtual void handleMouseRDownEvent();
        virtual void handleMouseLUpEvent();
        virtual void handleMouseRUpEvent();

        // Draws to the uiManager (called by the uiManager)
        void draw(MainUiManager *uiManager);

        /**  Model  **/
        uint32_t getModelTick();
        void doTick();
};

#endif // SCENE_HPP
