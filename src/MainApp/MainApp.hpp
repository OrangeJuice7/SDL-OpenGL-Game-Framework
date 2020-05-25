#ifndef MAIN_APP_HPP_INCLUDED
#define MAIN_APP_HPP_INCLUDED

#include "MessageHandler.hpp"
#include "../ui/UiManager.hpp"
class Scene;

class MainApp {
    protected:
        UiManager uiManager;
        Scene *currScene; // should always exist

        bool quitFlag;

        void executeMessages();
        void doTick();

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
        void transitScene(Scene* newScene);
};

#endif // MAIN_APP_HPP_INCLUDED
