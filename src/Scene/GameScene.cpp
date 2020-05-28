#include "GameScene.hpp"

#include <cstdio>
#include <SDL2/SDL.h>
#include "Model/GameModelManager.hpp"
#include "Widget/Widget.hpp"
#include "../system/MessageHandler.hpp"
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

	Widget* newWidget;
	const static GLcolorRGB     white = {1.f, 1.f, 1.f};
	const static GLcolorRGB textColor = {.8f, 1.f, .8f};

    newWidget = new Widget(
		{40, 20, 240, 20},
		Widget::HORZALIGN_LEFT,
		Widget::VERTALIGN_TOP,
		true,
		/*funcOnClick*/ []() {
			MessageHandler::postMessage( new SceneTransitMessage( new MenuScene() ) );
		},
		/*drawFunc*/ [](const Widget& widget, UiManager& uiManager) {
			if (widget.getActive()) uiManager.setColorMask(white);
			else                    uiManager.setColorMask(textColor);
			widget.renderText(uiManager, "Click here to go to main menu");
		} );
	widgetManager.loadWidget(newWidget);

    newWidget = new Widget(
		{0, 20, 160, 20},
		Widget::HORZALIGN_CENTER,
		Widget::VERTALIGN_TOP,
		true,
		/*drawFunc*/ [&](const Widget& widget, UiManager& uiManager) {
			uiManager.setColorMask(textColor);
			widget.renderText(uiManager, "GAME SCENE");
		} );
	widgetManager.loadWidget(newWidget);

    newWidget = new Widget(
		{10,-40, 240, 180},
		Widget::HORZALIGN_LEFT,
		Widget::VERTALIGN_CENTER,
		true,
		/*funcOnClick*/ [model]() {
			model->spawnParticleExplosion(100, 4, 1, .1f, .2f);
		},
		/*drawFunc*/ [](const Widget& widget, UiManager& uiManager) {
			uiManager.setColorMask(textColor);
			widget.renderText(uiManager, "test");
		} );
    newWidget->addChild( new Widget(
		{0,-40, 120, 60},
		Widget::HORZALIGN_CENTER,
		Widget::VERTALIGN_CENTER,
		true,
		/*funcOnClick*/ [](){},
		/*funcOnRelease*/ [model]() {
			model->spawnParticleExplosion(100, 4, -1, .1f, .2f);
		},
		/*drawFunc*/ [](const Widget& widget, UiManager& uiManager) {
			uiManager.setColorMask(textColor);
			widget.renderText(uiManager, "test2");
		} ) );
	widgetManager.loadWidget(newWidget);

    newWidget = new Widget(
		{0, 20, 360, 60},
		Widget::HORZALIGN_CENTER,
		Widget::VERTALIGN_BOTTOM,
		true,
		/*drawFunc*/ [model](const Widget& widget, UiManager& uiManager) {
			Mob *pMob = model->getActiveMob();
			if (!pMob) return;

			char msg[256];
			sprintf(msg, "Position: (%.3f, %.3f), Life: %.3f", pMob->x, pMob->y, pMob->life);
			uiManager.setColorMask(textColor);
			widget.renderText(uiManager, msg);
		} );
	widgetManager.loadWidget(newWidget);

    pauseDisplayWidget = new Widget(
		{20, 80, 160, 20},
		Widget::HORZALIGN_RIGHT,
		Widget::VERTALIGN_BOTTOM,
		paused,
		/*drawFunc*/ [this](const Widget& widget, UiManager& uiManager) {
			uiManager.setColorMask(white);
			widget.renderText(uiManager, "-- PAUSED --");
		} );
	widgetManager.loadWidget(pauseDisplayWidget);

    newWidget = new Widget(
		{20, 60, 160, 20},
		Widget::HORZALIGN_RIGHT,
		Widget::VERTALIGN_BOTTOM,
		true,
		/*drawFunc*/ [](const Widget& widget, UiManager& uiManager) {
			char msg[256];
			sprintf(msg, "UiTick: %u", uiManager.getUiTick());
			uiManager.setColorMask(textColor);
			widget.renderText(uiManager, msg);
		} );
	widgetManager.loadWidget(newWidget);

    newWidget = new Widget(
		{20, 40, 160, 20},
		Widget::HORZALIGN_RIGHT,
		Widget::VERTALIGN_BOTTOM,
		true,
		/*drawFunc*/ [model](const Widget& widget, UiManager& uiManager) {
			char msg[256];
			sprintf(msg, "ModelTick: %u", model->getModelTick());
			uiManager.setColorMask(textColor);
			widget.renderText(uiManager, msg);
		} );
	widgetManager.loadWidget(newWidget);

    newWidget = new Widget(
		{20, 20, 160, 20},
		Widget::HORZALIGN_RIGHT,
		Widget::VERTALIGN_BOTTOM,
		true,
		/*drawFunc*/ [](const Widget& widget, UiManager& uiManager) {
			char msg[256];
			sprintf(msg, "FPS: %.2f", uiManager.fps);
			uiManager.setColorMask(textColor);
			widget.renderText(uiManager, msg);
		} );
	widgetManager.loadWidget(newWidget);
}

void GameScene::pause() {
    Scene::pause();
    pauseDisplayWidget->show();
}
void GameScene::unpause() {
    Scene::unpause();
    pauseDisplayWidget->hide();
}
