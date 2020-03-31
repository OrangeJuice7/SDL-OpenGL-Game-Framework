#include "MainUiManager.hpp"

#include "../Scene/Scene.hpp"
#include "../MainApp/MessageHandler.hpp"
#include "../Message/Message.hpp"

void MainUiManager::getInputs(Scene* scene) {
    SDL_Event event;
    int mousePosX = 0, mousePosY = 0;

    while (SDL_PollEvent(&event) != 0) {
        switch (event.type) {
            default:
                // Unhandled event - do nothing
                break;

            case SDL_QUIT:
                MessageHandler::postMessage( new QuitMessage() );
                break;

            case SDL_KEYDOWN:
                scene->handleKeyDownEvent(event.key.keysym.sym);
                break;

            case SDL_KEYUP:
                scene->handleKeyUpEvent(event.key.keysym.sym);
                break;

            case SDL_MOUSEMOTION:
                SDL_GetMouseState(&mousePosX, &mousePosY);
                //
                break;

            case SDL_MOUSEBUTTONDOWN:
                SDL_GetMouseState(&mousePosX, &mousePosY);
                //
                break;

            case SDL_MOUSEBUTTONUP:
                //
                break;

            case SDL_MOUSEWHEEL:
                //
                break;
        }
    }
}
