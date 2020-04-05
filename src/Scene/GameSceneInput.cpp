#include "GameScene.hpp"

#include "Model/GameModelManager.hpp"

#include "../MainApp/MessageHandler.hpp"
#include "../Message/Message.hpp"
#include "../Message/SceneTransitMessage.hpp"
#include "MenuScene.hpp"

void GameScene::updateFromMouse(const SDL_Rect &screenRect, const MouseState &mouseState) {
    // Pan camera
    {   float panAmount = cameraMoveRate / modelManager->getModelScale(); // convert pixels per frame to game coords per frame
             if (mouseState.x <=              moveCameraScreenBorder) modelManager->moveCamera(-panAmount,0);
        else if (mouseState.x >= screenRect.w-moveCameraScreenBorder) modelManager->moveCamera( panAmount,0);
             if (mouseState.y <=              moveCameraScreenBorder) modelManager->moveCamera(0, panAmount);
        else if (mouseState.y >= screenRect.h-moveCameraScreenBorder) modelManager->moveCamera(0,-panAmount);
    }

    // Update like normal
    Scene::updateFromMouse(screenRect, mouseState);
}
void GameScene::updateFromKeys(const KeyboardState &keyboardState) {
    // Move player character
    {   Mob* playerMob = getModel()->getPlayerMob();
        if (playerMob) {
            float maxVel = .2f;
            float force = .2f;
            float forceX = 0,
                  forceY = 0;

            if ((keyboardState.isKeyDown(SDLK_LEFT) ||
                 keyboardState.isKeyDown(SDLK_a)) &&
                playerMob->xvel > -maxVel)
                forceX -= force;

            if ((keyboardState.isKeyDown(SDLK_RIGHT) ||
                 keyboardState.isKeyDown(SDLK_d)) &&
                playerMob->xvel < maxVel)
                forceX += force;

            if ((keyboardState.isKeyDown(SDLK_UP) ||
                 keyboardState.isKeyDown(SDLK_w)) &&
                playerMob->yvel < maxVel)
                forceY += force;

            if ((keyboardState.isKeyDown(SDLK_DOWN) ||
                 keyboardState.isKeyDown(SDLK_s)) &&
                playerMob->yvel > -maxVel)
                forceY -= force;

            if (forceX != 0 || forceY != 0)
                playerMob->applyForce(forceX, forceY);
        }
    }
}

void GameScene::handleKeyDownEvent(SDL_Keycode key) {
    switch (key) {
        default:
            // Unhandled event - do nothing
            break;

        case SDLK_SPACE:
            paused = !paused;
            break;

        //

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
        modelManager->scaleCamera(cameraScaleFactor); // zoom in
    } else if (delta < 0) { // towards user
        modelManager->scaleCamera(1/cameraScaleFactor); // zoom out
    }
}
