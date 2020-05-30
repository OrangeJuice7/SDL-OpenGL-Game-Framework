#include "MenuScene.hpp"

#include <cstdio>
#include <SDL2/SDL.h>
#include "Model/MenuModelManager.hpp"
#include "Widget/Widget.hpp"
#include "Widget/LabelWidget.hpp"
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
	LabelWidget *newLabelWidget;

    // "Go to game" button
    newWidget = new Widget({40, 20, 240, 20}, GuiRegion::HORZALIGN_LEFT, GuiRegion::VERTALIGN_TOP);
	newWidget->setClickFunction( []() {
        MessageHandler::postMessage( new SceneTransitMessage( new GameScene() ) );
    } );
	newWidget->setDrawFunction( [](const Widget& widget, UiManager& uiManager) {
        uiManager.setFont(FONT_ID_STANDARD, FONTSIZE_ID_NORMAL);
        if (widget.getSelected()) uiManager.setColorMask(white);
        else                      uiManager.setColorMask(textColor);
        widget.renderText(uiManager, 0, 0, "Click here to go to game");
    } );
    widgetManager.loadWidget(newWidget);

    // "Quit" button
	newWidget = new Widget({40, 60, 60, 40}, GuiRegion::HORZALIGN_LEFT, GuiRegion::VERTALIGN_BOTTOM);
    newWidget->setClickFunction( []() {
        MessageHandler::postMessage( new QuitMessage() );
    } );
    newWidget->setDrawFunction( [](const Widget& widget, UiManager& uiManager) {
        uiManager.setFont(FONT_ID_STANDARD, FONTSIZE_ID_NORMAL);
        if (widget.getSelected()) uiManager.setColorMask(white);
        else                      uiManager.setColorMask(textColor);
        widget.renderText(uiManager, 0, 0, "Quit");
    } );
    widgetManager.loadWidget(newWidget);

    // Menu Scene title
    newLabelWidget = new LabelWidget({0, 20, 240, 20}, GuiRegion::HORZALIGN_CENTER, GuiRegion::VERTALIGN_TOP);
    newLabelWidget->setFont(FONT_ID_STANDARD, FONTSIZE_ID_SUBHEADING);
    newLabelWidget->setTextAlignment(GuiRegion::HORZALIGN_CENTER, GuiRegion::VERTALIGN_CENTER);
    newLabelWidget->setTextColor(textColor);
    newLabelWidget->setText("MENU SCENE");
	widgetManager.loadWidget(newLabelWidget);

    // Lorem ipsum text tests
    newLabelWidget = new LabelWidget({-60, 60, 280, 240}, GuiRegion::HORZALIGN_CENTER, GuiRegion::VERTALIGN_CENTER);
    newLabelWidget->setClickFunction([](){});
    newLabelWidget->setFont(FONT_ID_STANDARD, FONTSIZE_ID_NORMAL);
    newLabelWidget->setTextAlignment(GuiRegion::HORZALIGN_CENTER, GuiRegion::VERTALIGN_CENTER);
    newLabelWidget->setTextColor(textColor);
    newLabelWidget->setText("Lorem ipsum dolor sit amet, consectetur adipiscing elit, \
sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. \
Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi \
ut aliquip ex ea commodo consequat.");
    widgetManager.loadWidget(newLabelWidget);

    newLabelWidget = new LabelWidget({240, 60, 120, 240}, GuiRegion::HORZALIGN_CENTER, GuiRegion::VERTALIGN_CENTER);
    newLabelWidget->setClickFunction([](){});
    newLabelWidget->setFont(FONT_ID_STANDARD, FONTSIZE_ID_NORMAL);
    newLabelWidget->setTextAlignment(GuiRegion::HORZALIGN_CENTER, GuiRegion::VERTALIGN_CENTER);
    newLabelWidget->setTextColor(textColor);
    newLabelWidget->setText("Lorem ipsum dolor sit amet, consectetur adipiscing elit, \
sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. \
Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi \
ut aliquip ex ea commodo consequat.");
    widgetManager.loadWidget(newLabelWidget);

    // Pause display
    newLabelWidget = new LabelWidget({20, 80, 160, 20}, GuiRegion::HORZALIGN_RIGHT, GuiRegion::VERTALIGN_BOTTOM);
    newLabelWidget->setFont(FONT_ID_STANDARD, FONTSIZE_ID_NORMAL);
    newLabelWidget->setTextAlignment(GuiRegion::HORZALIGN_CENTER, GuiRegion::VERTALIGN_CENTER);
    newLabelWidget->setTextColor(white);
    newLabelWidget->setText("-- PAUSED --");
	widgetManager.loadWidget(pauseDisplayWidget = newLabelWidget);
    if (!paused) pauseDisplayWidget->deactivate();

    // UiTick display
    newWidget = new Widget({20, 60, 160, 20}, GuiRegion::HORZALIGN_RIGHT, GuiRegion::VERTALIGN_BOTTOM);
    newWidget->setDrawFunction( [](const Widget& widget, UiManager& uiManager) {
        char msg[256];
        sprintf(msg, "UiTick: %u", uiManager.getUiTick());
        uiManager.setFont(FONT_ID_STANDARD, FONTSIZE_ID_NORMAL);
        uiManager.setColorMask(textColor);
        widget.renderText(uiManager, 0, 0, msg);
    } );
    widgetManager.loadWidget(newWidget);

    // ModelTick display
    newWidget = new Widget({20, 40, 160, 20}, GuiRegion::HORZALIGN_RIGHT, GuiRegion::VERTALIGN_BOTTOM);
    newWidget->setDrawFunction( [&](const Widget& widget, UiManager& uiManager) {
        char msg[256];
        sprintf(msg, "ModelTick: %u", modelManager->getModelTick());
        uiManager.setFont(FONT_ID_STANDARD, FONTSIZE_ID_NORMAL);
        uiManager.setColorMask(textColor);
        widget.renderText(uiManager, 0, 0, msg);
    } );
    widgetManager.loadWidget(newWidget);

    // FPS display
    newWidget = new Widget({20, 20, 160, 20}, GuiRegion::HORZALIGN_RIGHT, GuiRegion::VERTALIGN_BOTTOM);
    newWidget->setDrawFunction( [](const Widget& widget, UiManager& uiManager) {
        char msg[256];
        sprintf(msg, "FPS: %.2f", uiManager.fps);
        uiManager.setFont(FONT_ID_STANDARD, FONTSIZE_ID_NORMAL);
        uiManager.setColorMask(textColor);
        widget.renderText(uiManager, 0, 0, msg);
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
