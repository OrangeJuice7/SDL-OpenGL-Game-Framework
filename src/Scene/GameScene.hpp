#ifndef GAME_SCENE_HPP
#define GAME_SCENE_HPP

#include "Scene.hpp"

class GameScene : public Scene {
    protected:
        /**  Model  **/
        void updateOneTick();

    public:
        GameScene();
        ~GameScene();

        /**  UI  **/

        // Sends Messages to MainApp
        void handleKeyDownEvent(SDL_Keycode key);
        void handleKeyUpEvent(SDL_Keycode key);
        //void handleMouseMoveEvent(int mousePosX, int mousePosY);
        //void handleMouseLDownEvent(int mousePosX, int mousePosY);
        //void handleMouseRDownEvent(int mousePosX, int mousePosY);
        //void handleMouseLUpEvent(int mousePosX, int mousePosY);
        //void handleMouseRUpEvent(int mousePosX, int mousePosY);

        // Draws to the uiManager (called by the uiManager)
        void draw(MainUiManager *uiManager);
};

#endif // GAME_SCENE_HPP

