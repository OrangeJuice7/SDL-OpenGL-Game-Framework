/*#include "GameScene.hpp"

#include <cstdio>
#include "../MainUiManager/MainUiManager.hpp"

void GameScene::draw(MainUiManager *uiManager) {
    SDL_Color white = {255, 255, 255, 255};
    SDL_Color textColor = {200, 255, 200, 255};
    char msg[256];

    sprintf(msg, "UiTick: %u", uiManager->getUiTick());
    uiManager->renderTextToScreen(msg, textColor, 900, 620);

    sprintf(msg, "ModelTick: %u", modelTick);
    uiManager->renderTextToScreen(msg, textColor, 900, 640);

    sprintf(msg, "FPS: %.2f", uiManager->fps);
    uiManager->renderTextToScreen(msg, textColor, 900, 660);

    if (paused) {
        uiManager->renderTextToScreen("-- PAUSED --", white, 900, 680);
    }
}*/
