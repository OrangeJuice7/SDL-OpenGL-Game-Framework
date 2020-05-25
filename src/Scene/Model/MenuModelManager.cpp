#include "MenuModelManager.hpp"

#include <cmath>
#include "../../ui/UiManager.hpp"

MenuModelManager::MenuModelManager()
        : ModelManager(64) {

    //
}

void MenuModelManager::updateOneTick() {
    //
}

void MenuModelManager::draw(UiManager &uiManager) {
    uiManager.setColorMask({1,1,1});

    uiManager.setObjectScale(1 + .8f*sin(modelTick*.01618f +.8f));
    uiManager.drawSprite(-3 + sin(modelTick*.01f +.8f), .5f*cos(modelTick*.01f +.8f), SPRITE_ID_TEX1);

    uiManager.setObjectScale(1 + .2f*sin(modelTick*.01618f));
    uiManager.drawSprite(.5f*cos(modelTick*.01f +.4f), 1 - sin(modelTick*.01f +.4f), SPRITE_ID_GEOM);

    uiManager.setObjectScale(1);
    uiManager.drawSprite(3 + sin(modelTick*.01f), .5f*cos(modelTick*.01f), SPRITE_ID_TEX1);

    uiManager.setObjectScale(3, 1);
    uiManager.drawSprite(3 + sin(modelTick*.01f +.3f), 3 + .5f*cos(modelTick*.01f +.3f), SPRITE_ID_TEX2);

    uiManager.setObjectScale(1);
    uiManager.drawSprite(-3 + sin(modelTick*.01f), 1 + .5f*cos(modelTick*.01f), SPRITE_ID_TEX3);

    uiManager.setObjectScale(1);
    uiManager.drawSprite(-3 + sin(modelTick*.015f), -2 + cos(modelTick*.015f), SPRITE_ID_TEX4);
}
