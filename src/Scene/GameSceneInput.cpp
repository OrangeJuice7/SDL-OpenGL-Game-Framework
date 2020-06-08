#include "GameScene.hpp"

#include "../util/math.hpp"
#include "Model/GameModelManager.hpp"

#include "../system/MessageHandler.hpp"
#include "../system/Message.hpp"
#include "../system/SceneTransitMessage.hpp"
#include "MenuScene.hpp"

void GameScene::updateModelFromMouse(const SDL_Rect &screenRect, const MouseState &mouseState) {
    // Pan camera
    {   float panAmount = cameraMoveRate / modelManager->camera.getScale(); // convert pixels per frame to game coords per frame
        if      (mouseState.x <=              moveCameraScreenBorder) modelManager->camera.move(-panAmount,0);
        else if (mouseState.x >= screenRect.w-moveCameraScreenBorder) modelManager->camera.move( panAmount,0);
        if      (mouseState.y <=              moveCameraScreenBorder) modelManager->camera.move(0,-panAmount);
        else if (mouseState.y >= screenRect.h-moveCameraScreenBorder) modelManager->camera.move(0, panAmount);
    }

    // Fire bullets
    while (true) { // Fake loop just to use break statements
        if (paused) break;

        Mob* playerMob = getModel()->getPlayerMob();
        if (!playerMob) break;

        if (mouseState.isLDown) playerMob->fireAtPositionIfReady(0, *getModel(), mouseState.gameX, mouseState.gameY);
        if (mouseState.isRDown) playerMob->fireAtPositionIfReady(1, *getModel(), mouseState.gameX, mouseState.gameY);

        break;
    }

    // Update like normal
    Scene::updateModelFromMouse(screenRect, mouseState);
}
void GameScene::updateFromKeys(const KeyboardState &keyboardState) {
    // Move player character
    {   Mob* playerMob = getModel()->getPlayerMob();
        if (playerMob) {
            float maxVel = .2f;
            float maxForce = .2f;
            float forceX = 0,
                  forceY = 0;

            if ((keyboardState.isKeyDown(SDLK_LEFT) ||
                 keyboardState.isKeyDown(SDLK_a)) &&
                playerMob->xvel > -maxVel)
                forceX -= 1;

            if ((keyboardState.isKeyDown(SDLK_RIGHT) ||
                 keyboardState.isKeyDown(SDLK_d)) &&
                playerMob->xvel < maxVel)
                forceX += 1;

            if ((keyboardState.isKeyDown(SDLK_UP) ||
                 keyboardState.isKeyDown(SDLK_w)) &&
                playerMob->yvel < maxVel)
                forceY += 1;

            if ((keyboardState.isKeyDown(SDLK_DOWN) ||
                 keyboardState.isKeyDown(SDLK_s)) &&
                playerMob->yvel > -maxVel)
                forceY -= 1;

            if (forceX != 0 || forceY != 0) {
                float forgeMag = getdist(forceX, forceY);
                playerMob->applyForce((forceX/forgeMag) *maxForce, (forceY/forgeMag) *maxForce);
            }
        }
    }
}

void GameScene::handleKeyDownEvent(SDL_Keycode key) {
    switch (key) {
        default:
            // Unhandled event - do nothing
            break;

        case SDLK_ESCAPE:
            if (paused) unpause();
            else        pause();
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
    modelManager->camera.reset();
}
void GameScene::handleMouseWheelEvent(Sint32 delta) {
    if (delta > 0) { // away from user
        modelManager->camera.scale(cameraScaleFactor); // zoom in
    } else if (delta < 0) { // towards user
        modelManager->camera.scale(1.f/cameraScaleFactor); // zoom out
    }
}
