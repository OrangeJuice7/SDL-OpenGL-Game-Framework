#include "MenuScene.hpp"

#include "../MainApp/MessageHandler.hpp"
#include "../Message/Message.hpp"
#include "../Message/SceneTransitMessage.hpp"
#include "GameScene.hpp"

void MenuScene::handleKeyDownEvent(SDL_Keycode key) {
    switch (key) {
        default:
            // Unhandled event - do nothing
            break;

        case SDLK_SPACE:
            //
            break;

        case SDLK_LEFT:
            //
            break;

        case SDLK_RIGHT:
            //
            break;

        case SDLK_UP:
            //
            break;

        case SDLK_DOWN:
            //
            break;

        case SDLK_q:
            MessageHandler::postMessage( new SceneTransitMessage( new GameScene() ) );
            break;
    }
}

void MenuScene::handleKeyUpEvent(SDL_Keycode key) {
    switch (key) {
        default:
            // Unhandled event - do nothing
            break;

        //
    }
}
