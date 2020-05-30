#include "GameScene.hpp"

#include <cstdio>
#include <SDL2/SDL.h>
#include "Model/GameModelManager.hpp"
#include "Widget/Widget.hpp"
#include "../system/MessageHandler.hpp"
#include "../system/Message.hpp"
#include "../system/SceneTransitMessage.hpp"
#include "../ui/UiManager.hpp"
#include "MenuScene.hpp"

GameScene::GameScene()
        : Scene(new GameModelManager()) {

    cameraScaleFactor = 1.2f;
    cameraMoveRate = 20;
    moveCameraScreenBorder = 5;

    loadWidgets();

    getModel()->spawnPlayerMob(genericMobData, 0, 0);
    getModel()->spawnMob(genericMobData, 8, 0);
    getModel()->spawnMob(heavyMobData,-8, 0);
}
GameScene::~GameScene() {}

GameModelManager* GameScene::getModel() {
    return dynamic_cast<GameModelManager*>(modelManager);
}

void GameScene::loadWidgets() {
	GameModelManager* model = getModel();

	const static GLcolorRGB     white = {1.f, 1.f, 1.f};
	const static GLcolorRGB textColor = {.8f, 1.f, .8f};

	Widget *newWidget, *newWidget2;

    // ESC to pause notice
    newWidget = new Widget({40, 20, 240, 20}, GuiRegion::HORZALIGN_LEFT, GuiRegion::VERTALIGN_TOP);
	newWidget->setDrawFunction( [this](const Widget& widget, UiManager& uiManager) {
        uiManager.setFont(FONT_ID_STANDARD, FONTSIZE_ID_NORMAL);
        uiManager.setColorMask(textColor);
        if (paused) widget.renderText(uiManager, "Press ESC to resume");
        else        widget.renderText(uiManager, "Press ESC to pause");
    } );
	widgetManager.loadWidget(newWidget);

    // Game Scene title
    newWidget = new Widget({0, 20, 160, 20}, GuiRegion::HORZALIGN_CENTER, GuiRegion::VERTALIGN_TOP);
	newWidget->setDrawFunction( [](const Widget& widget, UiManager& uiManager) {
        uiManager.setFont(FONT_ID_STANDARD, FONTSIZE_ID_SUBHEADING);
        uiManager.setColorMask(textColor);
        widget.renderText(uiManager, "GAME SCENE");
    } );
	widgetManager.loadWidget(newWidget);

    // Clickable widgets test
    newWidget = new Widget({10,-40, 240, 180}, GuiRegion::HORZALIGN_LEFT, GuiRegion::VERTALIGN_CENTER);
	newWidget->setClickFunction( [model]() {
        model->spawnParticleExplosion(100, 4, 1, .1f, .2f);
    } );
	newWidget->setDrawFunction( [](const Widget& widget, UiManager& uiManager) {
        uiManager.setFont(FONT_ID_STANDARD, FONTSIZE_ID_NORMAL);
        uiManager.setColorMask(textColor);
        widget.renderText(uiManager, "test");
    } );

    newWidget2 = new Widget({0,-40, 120, 60}, GuiRegion::HORZALIGN_CENTER, GuiRegion::VERTALIGN_CENTER);
    newWidget2->setClickFunction( [](){}, [model]() {
        model->spawnParticleExplosion(100, 4, -1, .1f, .2f);
    } );
	newWidget2->setDrawFunction( [](const Widget& widget, UiManager& uiManager) {
        uiManager.setFont(FONT_ID_STANDARD, FONTSIZE_ID_NORMAL);
        uiManager.setColorMask(textColor);
        widget.renderText(uiManager, "test2");
    } );
	newWidget->addChild(newWidget2);
	widgetManager.loadWidget(newWidget);

    // Entity info
    newWidget = new Widget({0, 20, 360, 60}, GuiRegion::HORZALIGN_CENTER, GuiRegion::VERTALIGN_BOTTOM);
	newWidget->setDrawFunction( [model](const Widget& widget, UiManager& uiManager) {
        Mob *pMob = model->getActiveMob();
        if (!pMob) return;

        char msg[256];
        sprintf(msg, "Position: (%.3f, %.3f), Life: %.3f", pMob->x, pMob->y, pMob->life);
        uiManager.setFont(FONT_ID_STANDARD, FONTSIZE_ID_NORMAL);
        uiManager.setColorMask(textColor);
        widget.renderText(uiManager, msg);
    } );
	widgetManager.loadWidget(newWidget);

    // Pause menu
    pauseDisplayWidget = new Widget({0, 0, 200, 400}, GuiRegion::HORZALIGN_CENTER, GuiRegion::VERTALIGN_CENTER);
    if (!paused) pauseDisplayWidget->deactivate();
	pauseDisplayWidget->setDrawFunction( [](const Widget& widget, UiManager& uiManager){
        uiManager.setColorMask(white);
        widget.drawBgSprite(uiManager, SPRITE_ID_WIDGET_BG);
    } );
	widgetManager.loadWidget(pauseDisplayWidget);

    {   // "Paused" title
        newWidget = new Widget({0, 20, 160, 40}, GuiRegion::HORZALIGN_CENTER, GuiRegion::VERTALIGN_TOP);
        newWidget->setDrawFunction( [](const Widget& widget, UiManager& uiManager) {
            uiManager.setFont(FONT_ID_MONOSPACE, FONTSIZE_ID_SUBHEADING);
            uiManager.setColorMask(white);
            widget.renderText(uiManager, "--PAUSED--");
        } );
        pauseDisplayWidget->addChild(newWidget);

        // "Resume game" button
        newWidget = new Widget({0, 20, 160, 30}, GuiRegion::HORZALIGN_CENTER, GuiRegion::VERTALIGN_BOTTOM);
        newWidget->setClickFunction( [this]() {
            unpause();
        } );
        newWidget->setDrawFunction( [](const Widget& widget, UiManager& uiManager) {
            uiManager.setColorMask(white);
            widget.drawBgSprite(uiManager, SPRITE_ID_WIDGET_BG);

            uiManager.setFont(FONT_ID_STANDARD, FONTSIZE_ID_NORMAL);
            if (widget.getActive()) uiManager.setColorMask(white);
            else                    uiManager.setColorMask(textColor);
            widget.renderText(uiManager, "Resume game");
        } );
        pauseDisplayWidget->addChild(newWidget);

        // "Quit to Desktop" button
        newWidget = new Widget({0, 60, 160, 30}, GuiRegion::HORZALIGN_CENTER, GuiRegion::VERTALIGN_BOTTOM);
        newWidget->setClickFunction( []() {
            MessageHandler::postMessage( new QuitMessage() );
        } );
        newWidget->setDrawFunction( [](const Widget& widget, UiManager& uiManager) {
            uiManager.setColorMask(white);
            widget.drawBgSprite(uiManager, SPRITE_ID_WIDGET_BG);

            uiManager.setFont(FONT_ID_STANDARD, FONTSIZE_ID_NORMAL);
            if (widget.getActive()) uiManager.setColorMask(white);
            else                    uiManager.setColorMask(textColor);
            widget.renderText(uiManager, "Quit to Desktop");
        } );
        pauseDisplayWidget->addChild(newWidget);

        // "Quit to Menu" button
        newWidget = new Widget({0, 100, 160, 30}, GuiRegion::HORZALIGN_CENTER, GuiRegion::VERTALIGN_BOTTOM);
        newWidget->setClickFunction( []() {
            MessageHandler::postMessage( new SceneTransitMessage( new MenuScene() ) );
        } );
        newWidget->setDrawFunction( [](const Widget& widget, UiManager& uiManager) {
            uiManager.setColorMask(white);
            widget.drawBgSprite(uiManager, SPRITE_ID_WIDGET_BG);

            uiManager.setFont(FONT_ID_STANDARD, FONTSIZE_ID_NORMAL);
            if (widget.getActive()) uiManager.setColorMask(white);
            else                    uiManager.setColorMask(textColor);
            widget.renderText(uiManager, "Quit to Menu");
        } );
        pauseDisplayWidget->addChild(newWidget);
    }

    // UiTick display
    newWidget = new Widget({20, 60, 160, 20}, GuiRegion::HORZALIGN_RIGHT, GuiRegion::VERTALIGN_BOTTOM);
	newWidget->setDrawFunction( [](const Widget& widget, UiManager& uiManager) {
        char msg[256];
        sprintf(msg, "UiTick: %u", uiManager.getUiTick());
        uiManager.setFont(FONT_ID_STANDARD, FONTSIZE_ID_NORMAL);
        uiManager.setColorMask(textColor);
        widget.renderText(uiManager, msg);
    } );
	widgetManager.loadWidget(newWidget);

    // ModelTick display
    newWidget = new Widget({20, 40, 160, 20}, GuiRegion::HORZALIGN_RIGHT, GuiRegion::VERTALIGN_BOTTOM);
	newWidget->setDrawFunction( [model](const Widget& widget, UiManager& uiManager) {
        char msg[256];
        sprintf(msg, "ModelTick: %u", model->getModelTick());
        uiManager.setFont(FONT_ID_STANDARD, FONTSIZE_ID_NORMAL);
        uiManager.setColorMask(textColor);
        widget.renderText(uiManager, msg);
    } );
	widgetManager.loadWidget(newWidget);

    // FPS display
    newWidget = new Widget({20, 20, 160, 20}, GuiRegion::HORZALIGN_RIGHT, GuiRegion::VERTALIGN_BOTTOM);
	newWidget->setDrawFunction( [](const Widget& widget, UiManager& uiManager) {
        char msg[256];
        sprintf(msg, "FPS: %.2f", uiManager.fps);
        uiManager.setFont(FONT_ID_STANDARD, FONTSIZE_ID_NORMAL);
        uiManager.setColorMask(textColor);
        widget.renderText(uiManager, msg);
    } );
	widgetManager.loadWidget(newWidget);
}

void GameScene::pause() {
    Scene::pause();
    pauseDisplayWidget->activate();
}
void GameScene::unpause() {
    Scene::unpause();
    pauseDisplayWidget->deactivate();
}
