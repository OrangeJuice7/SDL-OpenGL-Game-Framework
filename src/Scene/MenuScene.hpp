#ifndef MENU_SCENE_HPP
#define MENU_SCENE_HPP

#include "Scene.hpp"

class MenuScene : public Scene {
    protected:
        /**  UI  **/
        Widget *pauseDisplayWidget;

        void loadWidgets();

    public:
        MenuScene();
        ~MenuScene();

        /**  UI  **/

        // Sends Messages to MainApp
        void handleKeyDownEvent(SDL_Keycode key);
        void handleKeyUpEvent(SDL_Keycode key);

        /**  Model  **/
        virtual void pause();
        virtual void unpause();
};

#endif // MENU_SCENE_HPP

