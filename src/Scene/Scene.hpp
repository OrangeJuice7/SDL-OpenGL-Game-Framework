#ifndef SCENE_HPP
#define SCENE_HPP

#include <SDL.h> // Uint32 defined in here
class MainUiManager;

class Scene {
    protected:
        /**  UI  **/
        //

        /**  Model  **/
        //

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
        //virtual void handleMouseMoveEvent(int mousePosX, int mousePosY);
        //virtual void handleMouseLDownEvent(int mousePosX, int mousePosY);
        //virtual void handleMouseRDownEvent(int mousePosX, int mousePosY);
        //virtual void handleMouseLUpEvent(int mousePosX, int mousePosY);
        //virtual void handleMouseRUpEvent(int mousePosX, int mousePosY);

        // Draws to the uiManager (called by the uiManager)
        virtual void draw(MainUiManager *uiManager);

        /**  Model  **/
        Uint32 getModelTick();
        void doTick();
};

#endif // SCENE_HPP
