#include "MenuScene.hpp"

#include <cstdio>
#include <SDL2/SDL.h>
#include "Model/MenuModelManager.hpp"
#include "Widget/Widget.hpp"
#include "Widget/LabelWidget.hpp"
#include "../system/Message.hpp"
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

	//Widget *newWidget;
	LabelWidget *newLabelWidget;

    // "Go to game" button
    newLabelWidget = new LabelWidget({40, 20, 240, 20}, GuiRegion::HORZALIGN_LEFT, GuiRegion::VERTALIGN_TOP);
	newLabelWidget->setClickFunction( []() {
        publish<SceneTransitMessage>({ new GameScene() });
    } );
	newLabelWidget->setFont(FONT_ID_STANDARD, FONTSIZE_ID_NORMAL);
    newLabelWidget->setTextAlignment(GuiRegion::HORZALIGN_CENTER, GuiRegion::VERTALIGN_CENTER);
    newLabelWidget->setText("Click here to go to game");
	newLabelWidget->setUpdateFunction( [](Widget* widget, const UiManager& uiManager) {
        LabelWidget *lwidget = dynamic_cast<LabelWidget*>(widget);
        if (lwidget->getSelected()) lwidget->setTextColor(white);
        else                        lwidget->setTextColor(textColor);
    } );
    widgetManager.loadWidget(newLabelWidget);

    // "Quit" button
	newLabelWidget = new LabelWidget({40, 60, 60, 40}, GuiRegion::HORZALIGN_LEFT, GuiRegion::VERTALIGN_BOTTOM);
    newLabelWidget->setClickFunction( []() {
        publish<QuitMessage>({});
    } );
	newLabelWidget->setFont(FONT_ID_STANDARD, FONTSIZE_ID_NORMAL);
    newLabelWidget->setTextAlignment(GuiRegion::HORZALIGN_CENTER, GuiRegion::VERTALIGN_CENTER);
    newLabelWidget->setText("Quit");
	newLabelWidget->setUpdateFunction( [](Widget* widget, const UiManager& uiManager) {
        LabelWidget *lwidget = dynamic_cast<LabelWidget*>(widget);
        if (lwidget->getSelected()) lwidget->setTextColor(white);
        else                        lwidget->setTextColor(textColor);
    } );
    widgetManager.loadWidget(newLabelWidget);

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
    newLabelWidget->setFont(FONT_ID_MONOSPACE, FONTSIZE_ID_NORMAL);
    newLabelWidget->setTextAlignment(GuiRegion::HORZALIGN_CENTER, GuiRegion::VERTALIGN_CENTER);
    newLabelWidget->setTextColor(white);
    newLabelWidget->setText("-- PAUSED --");
	widgetManager.loadWidget(pauseDisplayWidget = newLabelWidget);
    if (!paused) pauseDisplayWidget->deactivate();

    // UiTick, ModelTick, FPS displays
    newLabelWidget = new LabelWidget({20, 20, 240, 60}, GuiRegion::HORZALIGN_RIGHT, GuiRegion::VERTALIGN_BOTTOM);
    newLabelWidget->setFont(FONT_ID_MONOSPACE, FONTSIZE_ID_NORMAL);
    newLabelWidget->setTextAlignment(GuiRegion::HORZALIGN_RIGHT, GuiRegion::VERTALIGN_BOTTOM);
    newLabelWidget->setTextColor(textColor);
	newLabelWidget->setUpdateFunction( [&](Widget* widget, const UiManager& uiManager) {
        LabelWidget *lwidget = dynamic_cast<LabelWidget*>(widget);
        char msg[256];
        sprintf(msg, "UiTick: %5u\nModelTick: %5u\nFPS: %.2f", uiManager.getUiTick(), modelManager->getModelTick(), uiManager.fps);
        lwidget->setText(msg); // Removes the extra whitespaces produced by %5u though
    } );
    widgetManager.loadWidget(newLabelWidget);
}

void MenuScene::pause() {
    Scene::pause();
    pauseDisplayWidget->activate();
}
void MenuScene::unpause() {
    Scene::unpause();
    pauseDisplayWidget->deactivate();
}
