#ifndef SCENE_HPP
#define SCENE_HPP

#include <cstdint>
#include <SDL2/SDL.h>
#include "../ui/InputState.hpp"
#include "Widget/WidgetManager.hpp"
class UiManager;
class ModelManager;

class Scene {
    public:
        // modelManager should be a new ModelManager, created when constructing Scene's derived class
        Scene(ModelManager* modelManager);
        virtual ~Scene();

        /**  UI  **/
        void updateFromMouse(const SDL_Rect &screenRect, const MouseState &mouseState);
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
        void draw(UiManager &uiManager); // Not const because Widgets need to update cached data

        /**  Model  **/
        bool getPaused() const;
        uint32_t getModelTick() const;
        void doTick();

        virtual void pause();
        virtual void unpause();

    protected:
        WidgetManager widgetManager;
        ModelManager* modelManager;

        bool paused;

        // Returns true if the Widgets intercept the mouse (and thus control should not be passed to the model stage)
        virtual bool updateWidgetsFromMouse(const SDL_Rect &screenRect, const MouseState &mouseState);
        virtual void updateModelFromMouse(const SDL_Rect &screenRect, const MouseState &mouseState);
};

#endif // SCENE_HPP
