#include "MenuScene.hpp"

#include <cstdio>
#include <SDL2/SDL.h>
#include "Model/MenuModelManager.hpp"
#include "Widget/Widget.hpp"
#include "../system/MessageHandler.hpp"
#include "../system/Message.hpp"
#include "../system/SceneTransitMessage.hpp"
#include "../ui/UiManager.hpp"
#include "GameScene.hpp"

MenuScene::MenuScene()
        : Scene(new MenuModelManager()) {

    loadWidgets();
}
MenuScene::~MenuScene() {}

void MenuScene::loadWidgets() {
	const static GLcolorRGB     white = {1.f, 1.f, 1.f};
	const static GLcolorRGB textColor = {.8f, 1.f, .8f};

	widgetManager.loadWidget( new Widget(
		{40, 20, 240, 20},
		Widget::HORZALIGN_LEFT,
		Widget::VERTALIGN_TOP,
		true,
		/*funcOnClick*/ []() {
			MessageHandler::postMessage( new SceneTransitMessage( new GameScene() ) );
		},
		/*drawFunc*/ [](const Widget& widget, UiManager& uiManager) {
			if (widget.getActive()) uiManager.setColorMask(white);
			else                    uiManager.setColorMask(textColor);
			widget.renderText(uiManager, "Click here to go to game");
		} ) );

	widgetManager.loadWidget( new Widget(
		{40, 60, 60, 40},
		Widget::HORZALIGN_LEFT,
		Widget::VERTALIGN_BOTTOM,
		true,
		/*funcOnClick*/ []() {
			MessageHandler::postMessage( new QuitMessage() );
		},
		/*drawFunc*/ [](const Widget& widget, UiManager& uiManager) {
			if (widget.getActive()) uiManager.setColorMask(white);
			else                    uiManager.setColorMask(textColor);
			widget.renderText(uiManager, "Quit");
		} ) );

    widgetManager.loadWidget( new Widget(
		{0, 20, 160, 20},
		Widget::HORZALIGN_CENTER,
		Widget::VERTALIGN_TOP,
		true,
		/*drawFunc*/ [&](const Widget& widget, UiManager& uiManager) {
			uiManager.setColorMask(textColor);
			widget.renderText(uiManager, "MENU SCENE");
		} ) );

    pauseDisplayWidget = new Widget(
		{20, 80, 160, 20},
		Widget::HORZALIGN_RIGHT,
		Widget::VERTALIGN_BOTTOM,
		paused,
		/*drawFunc*/ [&](const Widget& widget, UiManager& uiManager) {
			uiManager.setColorMask(white);
			widget.renderText(uiManager, "-- PAUSED --");
		} );
    widgetManager.loadWidget(pauseDisplayWidget);

    widgetManager.loadWidget( new Widget(
		{20, 60, 160, 20},
		Widget::HORZALIGN_RIGHT,
		Widget::VERTALIGN_BOTTOM,
		true,
		/*drawFunc*/ [&](const Widget& widget, UiManager& uiManager) {
			char msg[256];
			sprintf(msg, "UiTick: %u", uiManager.getUiTick());
			uiManager.setColorMask(textColor);
			widget.renderText(uiManager, msg);
		} ) );

    widgetManager.loadWidget( new Widget(
		{20, 40, 160, 20},
		Widget::HORZALIGN_RIGHT,
		Widget::VERTALIGN_BOTTOM,
		true,
		/*drawFunc*/ [&](const Widget& widget, UiManager& uiManager) {
			char msg[256];
			sprintf(msg, "ModelTick: %u", modelManager->getModelTick());
			uiManager.setColorMask(textColor);
			widget.renderText(uiManager, msg);
		} ) );

    widgetManager.loadWidget( new Widget(
		{20, 20, 160, 20},
		Widget::HORZALIGN_RIGHT,
		Widget::VERTALIGN_BOTTOM,
		true,
		/*drawFunc*/ [&](const Widget& widget, UiManager& uiManager) {
			char msg[256];
			sprintf(msg, "FPS: %.2f", uiManager.fps);
			uiManager.setColorMask(textColor);
			widget.renderText(uiManager, msg);
		} ) );
}

void MenuScene::pause() {
    Scene::pause();
    pauseDisplayWidget->show();
}
void MenuScene::unpause() {
    Scene::unpause();
    pauseDisplayWidget->hide();
}
