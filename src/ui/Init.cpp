#include "UiManager.hpp"

#include <cstdio>

bool UiManager::init() {
    if(!initSDL()) {
        printf("Could not initialize SDL! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    if(!initWindow()) {
        printf("Could not initialize window! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    if(!initOpenGL()) {
        printf("Could not initialize OpenGL!\n");
        return false;
    }

    if(!spriteManager.init()) {
        printf("Could not initialize textures and sprites!\n");
        return false;
    }

    if(!textManager.init()) {
        printf("Could not initialize text manager!\n");
        return false;
    }

    return true;
}

void UiManager::deinit() {
    textManager.deinit();
    spriteManager.deinit();
    deinitOpenGL();
    deinitWindow();
    deinitSDL();
}
