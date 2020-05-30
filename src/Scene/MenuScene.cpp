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

	Widget *newWidget;

    // "Go to game" button
    newWidget = new Widget({40, 20, 240, 20}, GuiRegion::HORZALIGN_LEFT, GuiRegion::VERTALIGN_TOP);
	newWidget->setClickFunction( []() {
        MessageHandler::postMessage( new SceneTransitMessage( new GameScene() ) );
    } );
	newWidget->setDrawFunction( [](const Widget& widget, UiManager& uiManager) {
        uiManager.setFont(FONT_ID_STANDARD, FONTSIZE_ID_NORMAL);
        if (widget.getActive()) uiManager.setColorMask(white);
        else                    uiManager.setColorMask(textColor);
        widget.renderText(uiManager, "Click here to go to game");
    } );
    widgetManager.loadWidget(newWidget);

    // "Quit" button
	newWidget = new Widget({40, 60, 60, 40}, GuiRegion::HORZALIGN_LEFT, GuiRegion::VERTALIGN_BOTTOM);
    newWidget->setClickFunction( []() {
        MessageHandler::postMessage( new QuitMessage() );
    } );
    newWidget->setDrawFunction( [](const Widget& widget, UiManager& uiManager) {
        uiManager.setFont(FONT_ID_STANDARD, FONTSIZE_ID_NORMAL);
        if (widget.getActive()) uiManager.setColorMask(white);
        else                    uiManager.setColorMask(textColor);
        widget.renderText(uiManager, "Quit");
    } );
    widgetManager.loadWidget(newWidget);

    // Menu Scene title
    newWidget = new Widget({0, 20, 160, 20}, GuiRegion::HORZALIGN_CENTER, GuiRegion::VERTALIGN_TOP);
    newWidget->setDrawFunction( [](const Widget& widget, UiManager& uiManager) {
        uiManager.setFont(FONT_ID_STANDARD, FONTSIZE_ID_SUBHEADING);
        uiManager.setColorMask(textColor);
        widget.renderText(uiManager, "MENU SCENE");
    } );
    widgetManager.loadWidget(newWidget);

    // Pause display
    pauseDisplayWidget = new Widget({20, 80, 160, 20}, GuiRegion::HORZALIGN_RIGHT, GuiRegion::VERTALIGN_BOTTOM);
    if (!paused) pauseDisplayWidget->deactivate();
    pauseDisplayWidget->setDrawFunction( [](const Widget& widget, UiManager& uiManager) {
        uiManager.setFont(FONT_ID_STANDARD, FONTSIZE_ID_NORMAL);
        uiManager.setColorMask(white);
        widget.renderText(uiManager, "-- PAUSED --");
    } );
    widgetManager.loadWidget(pauseDisplayWidget);

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
    newWidget->setDrawFunction( [&](const Widget& widget, UiManager& uiManager) {
        char msg[256];
        sprintf(msg, "ModelTick: %u", modelManager->getModelTick());
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

void MenuScene::pause() {
    Scene::pause();
    pauseDisplayWidget->activate();
}
void MenuScene::unpause() {
    Scene::unpause();
    pauseDisplayWidget->deactivate();
}
