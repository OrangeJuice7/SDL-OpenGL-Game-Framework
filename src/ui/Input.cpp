#include "UiManager.hpp"

#include "../Scene/Scene.hpp"
#include "../MainApp/MessageHandler.hpp"
#include "../Message/Message.hpp"

void UiManager::getInputs(Scene* scene) {
    SDL_Event event;

    while (SDL_PollEvent(&event) != 0) {
        switch (event.type) {
            default:
                // Unhandled event - do nothing
                break;

            case SDL_QUIT:
                MessageHandler::postMessage( new QuitMessage() );
                break;

            case SDL_KEYDOWN:
                {   SDL_Keycode key = event.key.keysym.sym;
                    keyboardState.keys[key] = true;
                    scene->handleKeyDownEvent(key);
                }
                break;

            case SDL_KEYUP:
                {   SDL_Keycode key = event.key.keysym.sym;
                    keyboardState.keys[key] = false;
                    scene->handleKeyUpEvent(key);
                }
                break;

            case SDL_MOUSEMOTION:
                SDL_GetMouseState(&mouseState.x, &mouseState.y);
                break;

            case SDL_MOUSEBUTTONDOWN:
                switch (event.button.button) {
                    default: break; // Ignore other mouse buttons
                    case SDL_BUTTON_LEFT  : mouseState.isLDown = true; scene->handleMouseLDownEvent(); break;
                    case SDL_BUTTON_RIGHT : mouseState.isRDown = true; scene->handleMouseRDownEvent(); break;
                    case SDL_BUTTON_MIDDLE: mouseState.isMDown = true; scene->handleMouseMDownEvent(); break;
                }
                break;

            case SDL_MOUSEBUTTONUP:
                switch (event.button.button) {
                    default: break; // Ignore other mouse buttons
                    case SDL_BUTTON_LEFT  : mouseState.isLDown = false; scene->handleMouseLUpEvent(); break;
                    case SDL_BUTTON_RIGHT : mouseState.isRDown = false; scene->handleMouseRUpEvent(); break;
                    case SDL_BUTTON_MIDDLE: mouseState.isMDown = false; scene->handleMouseMUpEvent(); break;
                }
                break;

            case SDL_MOUSEWHEEL:
                scene->handleMouseWheelEvent(event.wheel.y);
                break;
        }
    }

    // Update the scene with the current input state (called every frame because even if the input state doesn't change, the scene may)
    scene->updateFromMouse(SCREEN_RECT, mouseState);
    scene->updateFromKeys(keyboardState);
}
