#include "MainUiManager.hpp"

#include <cstdio>
#include <SDL_image.h>

bool MainUiManager::initTextures() {
    //if (!bgTexture.loadFromFile("data/textures/bg.tga")) return false;

    return true;
}

void MainUiManager::deinitTextures() {
    IMG_Quit();
}
