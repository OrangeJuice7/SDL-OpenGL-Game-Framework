#include "GameScene.hpp"

#include "../basicmath.hpp"
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

    // Fire bullets
    Mob* playerMob = getModel()->getPlayerMob();
    if (playerMob) {
        // Grab player position and radius
        float px = playerMob->x,
              py = playerMob->y;
        float pr = playerMob->getRadius();

        // Get cursor position in game coords
        float gameX, gameY;
        modelManager->screenToGameCoords(screenRect, gameX, gameY, mouseState.x, mouseState.y);

        // Get direction vector of cursor from player
        float dirX = gameX - px,
              dirY = gameY - py;

        // Normalize direction vector
        float dist = getdist(dirX, dirY);
        dirX /= dist;
        dirY /= dist;

        float vel = 1;
        if (mouseState.isLDown && getModelTick()%10 == 0) getModel()->spawnProjectile(  genericProjectileData, px + dirX*pr, py + dirY*pr, dirX*vel, dirY*vel);
        if (mouseState.isRDown && getModelTick()%20 == 5) getModel()->spawnProjectile(explosiveProjectileData, px + dirX*pr, py + dirY*pr, dirX*vel, dirY*vel);
    }

    // Update like normal
    Scene::updateFromMouse(screenRect, mouseState);
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
