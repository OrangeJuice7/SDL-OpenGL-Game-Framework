#include "GameScene.hpp"

#include "Model/GameModelManager.hpp"

#include "../MainApp/MessageHandler.hpp"
#include "../Message/Message.hpp"
#include "../Message/SceneTransitMessage.hpp"
#include "MenuScene.hpp"

void GameScene::handleKeyDownEvent(SDL_Keycode key) {
    switch (key) {
        default:
            // Unhandled event - do nothing
            break;

        case SDLK_SPACE:
            paused = !paused;
            break;

        case SDLK_LEFT:
            //
            break;

        case SDLK_RIGHT:
            //
            break;

        case SDLK_UP:
            //
            break;

        case SDLK_DOWN:
            //
            break;

        case SDLK_q:
            MessageHandler::postMessage( new SceneTransitMessage( new MenuScene() ) );
            break;
    }
}

void GameScene::handleKeyUpEvent(SDL_Keycode key) {
    switch (key) {
        default:
            // Unhandled event - do nothing
            break;

        //
    }
}

void GameScene::handleMouseMDownEvent() {
    modelManager->resetCamera();
}
void GameScene::handleMouseWheelEvent(Sint32 delta) {
    if (delta > 0) { // away from user
        modelManager->scaleCamera(1/cameraScaleFactor);
    } else if (delta < 0) { // towards user
        modelManager->scaleCamera(cameraScaleFactor);
    }
}
