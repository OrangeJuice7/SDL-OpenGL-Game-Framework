#ifndef MAIN_APP_HPP_INCLUDED
#define MAIN_APP_HPP_INCLUDED

#include "../ui/UiManager.hpp"
class Scene;

class MainApp {
    public:
        const float TARGET_FPS;
        const float FPS_UPDATE_RATE; // in seconds
        const float LAG_COMPENSATION_THRESHOLD; // do not compensate for lag if it is beyond this threshold (in seconds)

        MainApp();
        ~MainApp();
        bool init();
        void deinit();

        // Runs the main game loop
        void run();

        // Message/misc commands
        void quit();

    protected:
        UiManager uiManager;
        Scene *currScene; // should always exist
        Scene *nextScene; // Next scene to load. Is a buffer so that a new Scene is not loaded in the middle of updating currScene.

        bool quitFlag;

        void subToMessages();
        void doTick();
        void setNextScene(Scene* newScene);
        void transitScene();
};

#endif // MAIN_APP_HPP_INCLUDED
