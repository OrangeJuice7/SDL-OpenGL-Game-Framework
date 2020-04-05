#ifndef GAME_SCENE_HPP
#define GAME_SCENE_HPP

#include "Scene.hpp"
class GameModelManager;

class GameScene : public Scene {
    protected:
        /**  UI  **/
        float cameraScaleFactor; // Should be > 1

        void loadWidgets();

        GameModelManager* getModel();

    public:
        GameScene();
        ~GameScene();

        /**  UI  **/

        // Sends Messages to MainApp
        void handleKeyDownEvent(SDL_Keycode key);
        void handleKeyUpEvent(SDL_Keycode key);
        void handleMouseMDownEvent();
        void handleMouseWheelEvent(Sint32 delta);
};

#endif // GAME_SCENE_HPP

