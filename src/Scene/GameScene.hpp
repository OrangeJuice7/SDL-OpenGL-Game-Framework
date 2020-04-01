#ifndef GAME_SCENE_HPP
#define GAME_SCENE_HPP

#include "Scene.hpp"

class GameScene : public Scene {
    protected:
        /**  UI  **/
        void loadWidgets();

        /**  Model  **/
        void updateOneTick();

    public:
        GameScene();
        ~GameScene();

        /**  UI  **/

        // Sends Messages to MainApp
        void handleKeyDownEvent(SDL_Keycode key);
        void handleKeyUpEvent(SDL_Keycode key);
};

#endif // GAME_SCENE_HPP

