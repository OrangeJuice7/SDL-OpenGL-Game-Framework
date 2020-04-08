#ifndef MENU_SCENE_HPP
#define MENU_SCENE_HPP

#include "Scene.hpp"

class MenuScene : public Scene {
    protected:
        /**  UI  **/
        void loadWidgets();

    public:
        MenuScene();
        ~MenuScene();

        /**  UI  **/

        // Sends Messages to MainApp
        void handleKeyDownEvent(SDL_Keycode key);
        void handleKeyUpEvent(SDL_Keycode key);
};

#endif // MENU_SCENE_HPP

