#include "MainUiManager.hpp"

/*void MainUiManager::setDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
}
void MainUiManager::drawPixel(int x, int y) {
    SDL_RenderDrawPoint(renderer, x, y);
}*/

void MainUiManager::renderTextToScreen(const char *text, SDL_Color fg, int x, int y) {
    Texture texture;
    texture.loadFromText(mainFont, text, fg);
    texture.render(x, y);
}

void MainUiManager::renderImageToScreen(SDL_Surface* image, int x, int y) {
    Texture texture;
    texture.loadFromSurface(image);
    texture.render(x, y);
}
