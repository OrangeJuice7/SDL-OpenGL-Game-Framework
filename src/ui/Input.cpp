#include "UiManager.hpp"

#include <cstdio>
#include "../Scene/Scene.hpp"
#include "../system/MessageHandler.hpp"
#include "../system/Message.hpp"

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

            case SDL_WINDOWEVENT:
                if (event.window.windowID == SDL_GetWindowID(mainWindow)) {
                    switch (event.window.event) {
                        default: break; // Ignore other window event types

                        case SDL_WINDOWEVENT_SIZE_CHANGED:
                            updateWindowSize(event.window.data1, event.window.data2);
                            break;
                    }
                }
                break;

            case SDL_KEYDOWN:
                {   SDL_Keycode key = event.key.keysym.sym;
                    keyboardState.keys[key] = true;
                    scene->handleKeyDownEvent(key);

                    // Toggle fullscreen
                    if (key == SDLK_F1) toggleFullscreen();

                    // Print screen
                    if (key == SDLK_F2) {
                        char filename[32];
                        sprintf(filename, "screen%d", uiTick);
                        saveScreenshot(filename);
                    }
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
                mouseState.y = getScreenHeight() - mouseState.y; // Flip y-direction to be consistent with OpenGL
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
    // Todo: Let the Scene remember its own state, which is triggered based on the input presses?
    screenToGameCoords(mouseState.gameX, mouseState.gameY, mouseState.x, mouseState.y);
    scene->updateFromMouse(getScreenRect(), mouseState);
    scene->updateFromKeys(keyboardState);
}
