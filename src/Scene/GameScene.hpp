#ifndef GAME_SCENE_HPP
#define GAME_SCENE_HPP

#include "Scene.hpp"
#include "Widget/LabelWidget.hpp"
class GameModelManager;

class GameScene : public Scene {
    public:
        GameScene();
        ~GameScene();

        /**  UI  **/
        void updateFromKeys(const KeyboardState &keyboardState);

        // Sends Messages to MainApp
        void handleKeyDownEvent(SDL_Keycode key);
        void handleKeyUpEvent(SDL_Keycode key);
        void handleMouseMDownEvent();
        void handleMouseWheelEvent(Sint32 delta);

        /**  Model  **/
        virtual void pause();
        virtual void unpause();

    protected:
        /**  UI  **/
        float cameraScaleFactor; // Should be > 1
        float cameraMoveRate; // in pixels per frame, positive
        int moveCameraScreenBorder; // The cursor should be within this number of pixels from the window border in order to move the camera

        LabelWidget *pauseInstructionWidget;
        Widget *pauseDisplayWidget;

        void loadWidgets();

        GameModelManager* getModel();

        void updateModelFromMouse(const SDL_Rect &screenRect, const MouseState &mouseState);
};

#endif // GAME_SCENE_HPP

