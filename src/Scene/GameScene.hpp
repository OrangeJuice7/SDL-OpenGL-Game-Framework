#ifndef GAME_SCENE_HPP
#define GAME_SCENE_HPP

#include "Scene.hpp"
class GameModelManager;

class GameScene : public Scene {
    protected:
        /**  UI  **/
        float cameraScaleFactor; // Should be > 1
        float cameraMoveRate; // in pixels per frame, positive
        int moveCameraScreenBorder; // The cursor should be within this number of pixels from the window border in order to move the camera

        Widget *pauseDisplayWidget;

        void loadWidgets();

        GameModelManager* getModel();

    public:
        GameScene();
        ~GameScene();

        /**  UI  **/
        // Checks for camera panning, then checks for active elements like normal
        void updateFromMouse(const SDL_Rect &screenRect, const MouseState &mouseState);
        void updateFromKeys(const KeyboardState &keyboardState);

        // Sends Messages to MainApp
        void handleKeyDownEvent(SDL_Keycode key);
        void handleKeyUpEvent(SDL_Keycode key);
        void handleMouseMDownEvent();
        void handleMouseWheelEvent(Sint32 delta);

        /**  Model  **/
        virtual void pause();
        virtual void unpause();
};

#endif // GAME_SCENE_HPP

