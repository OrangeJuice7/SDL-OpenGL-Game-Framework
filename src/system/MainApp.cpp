#include "MainApp.hpp"

#include <cstdio>
#include "Settings.hpp"
#include "Message.hpp"
#include "../Scene/Scene.hpp"
#include "../Scene/MenuScene.hpp"
#include "../util/Timer.hpp"

MainApp::MainApp()
        : TARGET_FPS(60)
        , FPS_UPDATE_RATE(1)
        , LAG_COMPENSATION_THRESHOLD(1)
        , uiManager("[PROJECT TITLE]")
        , currScene( new MenuScene() )
        , nextScene(nullptr)
        , quitFlag(false) {}
MainApp::~MainApp() {
    delete currScene;
}

bool MainApp::init() {
    Timer initializeTimer;
    printf("Initializing...\n");
    initializeTimer.start();

    printf("Loading settings...\n");
    Settings::load();

    printf("Loading UI...\n");
    if(!uiManager.init()) {
        printf("Main UI Manager failed to initialize.\n");
        return false;
    }

    printf("Subscribing to messages...\n");
    subToMessages();

    initializeTimer.stop();
    printf("Initialized! (%.3f s)\n", initializeTimer.getTime());

    return true;
}

void MainApp::deinit() {
    printf("Unloading UI...\n");
    uiManager.deinit();

    printf("Saving settings...\n");
    Settings::save();
}

void MainApp::subToMessages() {
    subscribe<QuitMessage>("closeMainApp", [&](const QuitMessage& msg) {
        quit();
    });

    subscribe<SceneTransitMessage>("MainAppTransitScene", [&](const SceneTransitMessage& msg) {
        setNextScene(msg.scene);
    });
}

void MainApp::doTick() {
    // Poll for inputs
    uiManager.getInputs(*currScene);

    // Transit to the nextScene, if set
    if (nextScene) transitScene();

    // Do model tick
    currScene->doTick();

    // Draw
    uiManager.draw(*currScene);
}
void MainApp::run() {
    const float TARGET_FRAMETIME = 1.0f / TARGET_FPS; // seconds per frame
    float currTime, uiTime;
    float lagCompensation = 0; // Reduce the lag gap by this much
    Timer realTime;
    Timer tickTimer;

    Uint32 numOfFrames = 0;
    Timer fpsUpdateTimer;

    while (!quitFlag) {
        do {
            tickTimer.start();
            doTick();
            tickTimer.stop();
            ++numOfFrames;

            currTime = realTime.getTime();
            uiTime = uiManager.getUiTick()*TARGET_FRAMETIME + lagCompensation;

        } while ( // Continue to do ticks while
            tickTimer.getTime() < TARGET_FRAMETIME && // The time taken per frame is faster than required, and
            uiTime < currTime); // The UI is lagging behind

        // update FPS
        if (fpsUpdateTimer.getTime() >= FPS_UPDATE_RATE) {
            uiManager.fps = (float)numOfFrames / fpsUpdateTimer.getTime();
            numOfFrames = 0;
            fpsUpdateTimer.start();
        }

        float lagTime = currTime - uiTime; // The UI is behind real time by this much

        if (lagTime > LAG_COMPENSATION_THRESHOLD) // If the lag is too much
            lagCompensation += lagTime; // just ignore it
        else if (lagTime < 0) { // If the lag is actually negative (i.e. UI is ahead of real time)
            float sleepTime = -lagTime;
            uiManager.sleep(sleepTime); // sleep off the real time
        }
    }
}

void MainApp::quit() {
    quitFlag = true;
}

void MainApp::setNextScene(Scene* newScene) {
    nextScene = newScene;
}
void MainApp::transitScene() {
    delete currScene;
    currScene = nextScene;
    nextScene = nullptr;
}
