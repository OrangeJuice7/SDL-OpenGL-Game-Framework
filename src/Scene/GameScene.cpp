#include "GameScene.hpp"

#include <cstdio>
#include <SDL2/SDL.h>
#include "Model/GameModelManager.hpp"
#include "Widget/Widget.hpp"
#include "Widget/LabelWidget.hpp"
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

	//Widget *newWidget;
	LabelWidget *newLabelWidget, *newLabelWidget2;

    // ESC to pause notice
    pauseInstructionWidget = new LabelWidget({40, 20, 240, 20}, GuiRegion::HORZALIGN_LEFT, GuiRegion::VERTALIGN_TOP);
	pauseInstructionWidget->setFont(FONT_ID_STANDARD, FONTSIZE_ID_NORMAL);
    pauseInstructionWidget->setTextAlignment(GuiRegion::HORZALIGN_LEFT, GuiRegion::VERTALIGN_CENTER);
    pauseInstructionWidget->setTextColor(textColor);
	widgetManager.loadWidget(pauseInstructionWidget);

    // Game Scene title
    newLabelWidget = new LabelWidget({0, 20, 240, 20}, GuiRegion::HORZALIGN_CENTER, GuiRegion::VERTALIGN_TOP);
	newLabelWidget->setFont(FONT_ID_STANDARD, FONTSIZE_ID_SUBHEADING);
    newLabelWidget->setTextAlignment(GuiRegion::HORZALIGN_CENTER, GuiRegion::VERTALIGN_CENTER);
    newLabelWidget->setTextColor(textColor);
    newLabelWidget->setText("GAME SCENE");
	widgetManager.loadWidget(newLabelWidget);

    // Clickable widgets test
    newLabelWidget = new LabelWidget({10,-40, 240, 180}, GuiRegion::HORZALIGN_LEFT, GuiRegion::VERTALIGN_CENTER);
	newLabelWidget->setClickFunction( [model]() {
        model->spawnParticleExplosion(100, 4, 1, .1f, .2f);
    } );
    newLabelWidget->setFont(FONT_ID_STANDARD, FONTSIZE_ID_NORMAL);
    newLabelWidget->setTextAlignment(GuiRegion::HORZALIGN_LEFT, GuiRegion::VERTALIGN_TOP);
    newLabelWidget->setTextColor(textColor);
    newLabelWidget->setText("test");

    newLabelWidget2 = new LabelWidget({0,-40, 120, 60}, GuiRegion::HORZALIGN_CENTER, GuiRegion::VERTALIGN_CENTER);
    newLabelWidget2->setClickFunction( [](){}, [model]() {
        model->spawnParticleExplosion(100, 4, -1, .1f, .2f);
    } );
    newLabelWidget2->setFont(FONT_ID_STANDARD, FONTSIZE_ID_NORMAL);
    newLabelWidget2->setTextAlignment(GuiRegion::HORZALIGN_CENTER, GuiRegion::VERTALIGN_CENTER);
    newLabelWidget2->setTextColor(textColor);
    newLabelWidget2->setText("test2");
	newLabelWidget->addChild(newLabelWidget2);
	widgetManager.loadWidget(newLabelWidget);

    // Entity info
    newLabelWidget = new LabelWidget({0, 20, 360, 60}, GuiRegion::HORZALIGN_CENTER, GuiRegion::VERTALIGN_BOTTOM);
	newLabelWidget->setFont(FONT_ID_STANDARD, FONTSIZE_ID_NORMAL);
    newLabelWidget->setTextAlignment(GuiRegion::HORZALIGN_CENTER, GuiRegion::VERTALIGN_CENTER);
    newLabelWidget->setTextColor(textColor);
    newLabelWidget->setUpdateFunction( [model](Widget* widget, const UiManager& uiManager) {
        LabelWidget *lwidget = dynamic_cast<LabelWidget*>(widget);

        Mob *pMob = model->getActiveMob();
        if (!pMob) {
            lwidget->setText("");
            return;
        }

        char msg[256];
        sprintf(msg, "Position: (%.3f, %.3f), Life: %.3f", pMob->x, pMob->y, pMob->life);
        lwidget->setText(msg);
    } );
	widgetManager.loadWidget(newLabelWidget);

    // Pause menu
    pauseDisplayWidget = new Widget({0, 0, 200, 400}, GuiRegion::HORZALIGN_CENTER, GuiRegion::VERTALIGN_CENTER);
    if (!paused) pauseDisplayWidget->deactivate();
	pauseDisplayWidget->setDrawFunction( [](const Widget& widget, UiManager& uiManager){
        uiManager.setColorMask(white);
        widget.drawBgSprite(uiManager, SPRITE_ID_WIDGET_BG);
    } );
	widgetManager.loadWidget(pauseDisplayWidget);

    {   // "Paused" title
        newLabelWidget = new LabelWidget({0, 20, 160, 40}, GuiRegion::HORZALIGN_CENTER, GuiRegion::VERTALIGN_TOP);
        newLabelWidget->setFont(FONT_ID_MONOSPACE, FONTSIZE_ID_SUBHEADING);
        newLabelWidget->setTextAlignment(GuiRegion::HORZALIGN_CENTER, GuiRegion::VERTALIGN_CENTER);
        newLabelWidget->setTextColor(white);
        newLabelWidget->setText("-PAUSED-");
        pauseDisplayWidget->addChild(newLabelWidget);

        // "Resume game" button
        newLabelWidget = new LabelWidget({0, 20, 160, 30}, GuiRegion::HORZALIGN_CENTER, GuiRegion::VERTALIGN_BOTTOM);
        newLabelWidget->setClickFunction( [this]() {
            unpause();
        } );
        newLabelWidget->setDrawFunction( [](const Widget& widget, UiManager& uiManager) {
            uiManager.setColorMask(white);
            widget.drawBgSprite(uiManager, SPRITE_ID_WIDGET_BG);
        } );
        newLabelWidget->setUpdateFunction( [](Widget* widget, const UiManager& uiManager) {
            LabelWidget *lwidget = dynamic_cast<LabelWidget*>(widget);
            if (lwidget->getSelected()) lwidget->setTextColor(white);
            else                        lwidget->setTextColor(textColor);
        } );
        newLabelWidget->setFont(FONT_ID_STANDARD, FONTSIZE_ID_NORMAL);
        newLabelWidget->setTextAlignment(GuiRegion::HORZALIGN_CENTER, GuiRegion::VERTALIGN_CENTER);
        newLabelWidget->setText("Resume Game");
        pauseDisplayWidget->addChild(newLabelWidget);

        // "Quit to Desktop" button
        newLabelWidget = new LabelWidget({0, 60, 160, 30}, GuiRegion::HORZALIGN_CENTER, GuiRegion::VERTALIGN_BOTTOM);
        newLabelWidget->setClickFunction( []() {
            MessageHandler::postMessage( new QuitMessage() );
        } );
        newLabelWidget->setDrawFunction( [](const Widget& widget, UiManager& uiManager) {
            uiManager.setColorMask(white);
            widget.drawBgSprite(uiManager, SPRITE_ID_WIDGET_BG);
        } );
        newLabelWidget->setUpdateFunction( [](Widget* widget, const UiManager& uiManager) {
            LabelWidget *lwidget = dynamic_cast<LabelWidget*>(widget);
            if (lwidget->getSelected()) lwidget->setTextColor(white);
            else                        lwidget->setTextColor(textColor);
        } );
        newLabelWidget->setFont(FONT_ID_STANDARD, FONTSIZE_ID_NORMAL);
        newLabelWidget->setTextAlignment(GuiRegion::HORZALIGN_CENTER, GuiRegion::VERTALIGN_CENTER);
        newLabelWidget->setText("Quit to Desktop");
        pauseDisplayWidget->addChild(newLabelWidget);

        // "Quit to Menu" button
        newLabelWidget = new LabelWidget({0, 100, 160, 30}, GuiRegion::HORZALIGN_CENTER, GuiRegion::VERTALIGN_BOTTOM);
        newLabelWidget->setClickFunction( []() {
            MessageHandler::postMessage( new SceneTransitMessage( new MenuScene() ) );
        } );
        newLabelWidget->setDrawFunction( [](const Widget& widget, UiManager& uiManager) {
            uiManager.setColorMask(white);
            widget.drawBgSprite(uiManager, SPRITE_ID_WIDGET_BG);
        } );
        newLabelWidget->setUpdateFunction( [](Widget* widget, const UiManager& uiManager) {
            LabelWidget *lwidget = dynamic_cast<LabelWidget*>(widget);
            if (lwidget->getSelected()) lwidget->setTextColor(white);
            else                        lwidget->setTextColor(textColor);
        } );
        newLabelWidget->setFont(FONT_ID_STANDARD, FONTSIZE_ID_NORMAL);
        newLabelWidget->setTextAlignment(GuiRegion::HORZALIGN_CENTER, GuiRegion::VERTALIGN_CENTER);
        newLabelWidget->setText("Quit to Menu");
        pauseDisplayWidget->addChild(newLabelWidget);
    }

    // UiTick display
    newLabelWidget = new LabelWidget({20, 60, 160, 20}, GuiRegion::HORZALIGN_RIGHT, GuiRegion::VERTALIGN_BOTTOM);
    newLabelWidget->setFont(FONT_ID_MONOSPACE, FONTSIZE_ID_NORMAL);
    newLabelWidget->setTextAlignment(GuiRegion::HORZALIGN_RIGHT, GuiRegion::VERTALIGN_BOTTOM);
    newLabelWidget->setTextColor(textColor);
	newLabelWidget->setUpdateFunction( [](Widget* widget, const UiManager& uiManager) {
        LabelWidget *lwidget = dynamic_cast<LabelWidget*>(widget);
        char msg[256];
        sprintf(msg, "UiTick: %u", uiManager.getUiTick());
        lwidget->setText(msg);
    } );
    widgetManager.loadWidget(newLabelWidget);

    // ModelTick display
    newLabelWidget = new LabelWidget({20, 40, 160, 20}, GuiRegion::HORZALIGN_RIGHT, GuiRegion::VERTALIGN_BOTTOM);
    newLabelWidget->setFont(FONT_ID_MONOSPACE, FONTSIZE_ID_NORMAL);
    newLabelWidget->setTextAlignment(GuiRegion::HORZALIGN_RIGHT, GuiRegion::VERTALIGN_BOTTOM);
    newLabelWidget->setTextColor(textColor);
	newLabelWidget->setUpdateFunction( [&](Widget* widget, const UiManager& uiManager) {
        LabelWidget *lwidget = dynamic_cast<LabelWidget*>(widget);
        char msg[256];
        sprintf(msg, "ModelTick: %u", modelManager->getModelTick());
        lwidget->setText(msg);
    } );
    widgetManager.loadWidget(newLabelWidget);

    // FPS display
    newLabelWidget = new LabelWidget({20, 20, 160, 20}, GuiRegion::HORZALIGN_RIGHT, GuiRegion::VERTALIGN_BOTTOM);
    newLabelWidget->setFont(FONT_ID_MONOSPACE, FONTSIZE_ID_NORMAL);
    newLabelWidget->setTextAlignment(GuiRegion::HORZALIGN_RIGHT, GuiRegion::VERTALIGN_BOTTOM);
    newLabelWidget->setTextColor(textColor);
	newLabelWidget->setUpdateFunction( [](Widget* widget, const UiManager& uiManager) {
        LabelWidget *lwidget = dynamic_cast<LabelWidget*>(widget);
        char msg[256];
        sprintf(msg, "FPS: %.2f", uiManager.fps);
        lwidget->setText(msg);
    } );
    widgetManager.loadWidget(newLabelWidget);
}

void GameScene::pause() {
    Scene::pause();
    pauseDisplayWidget->activate();
    pauseInstructionWidget->setText("Press ESC to resume");
}
void GameScene::unpause() {
    Scene::unpause();
    pauseDisplayWidget->deactivate();
    pauseInstructionWidget->setText("Press ESC to pause");
}
