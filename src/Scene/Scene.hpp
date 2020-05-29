#ifndef SCENE_HPP
#define SCENE_HPP

#include <cstdint>
#include <SDL2/SDL.h>
#include "../ui/InputState.hpp"
#include "Widget/WidgetManager.hpp"
class UiManager;
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
        // Basically updates the active elements e.g. selectedWidget
        virtual void updateFromMouse(const SDL_Rect &screenRect, const MouseState &mouseState);
        virtual void updateFromKeys(const KeyboardState &keyboardState);

        // Handle input. May send Messages to MainApp
        virtual void handleKeyDownEvent(SDL_Keycode key);
        virtual void handleKeyUpEvent(SDL_Keycode key);
        virtual void handleMouseLDownEvent();
        virtual void handleMouseLUpEvent();
        virtual void handleMouseRDownEvent();
        virtual void handleMouseRUpEvent();
        virtual void handleMouseMDownEvent();
        virtual void handleMouseMUpEvent();
        virtual void handleMouseWheelEvent(Sint32 delta); // positive delta: away from the user

        // Draws to the uiManager (called by the uiManager)
        void draw(UiManager &uiManager);

        /**  Model  **/
        bool getPaused() const;
        uint32_t getModelTick() const;
        void doTick();

        virtual void pause();
        virtual void unpause();
};

#endif // SCENE_HPP
