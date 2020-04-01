#include "MainUiManager.hpp"

void MainUiManager::setDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
}
void MainUiManager::setDrawColor(const SDL_Color& color) {
    setDrawColor(color.r, color.g, color.b, color.a);
}

void MainUiManager::drawPixel(int x, int y) {
    SDL_RenderDrawPoint(renderer, x, y);
}

void MainUiManager::drawLine(int x1, int y1, int x2, int y2) {
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
    // Could also check out SDL_RenderDrawLines
}

void MainUiManager::drawFillRect(const SDL_Rect& rect) {
    SDL_RenderFillRect( renderer, &rect );
}

void MainUiManager::drawLineRect(const SDL_Rect& rect) {
    SDL_RenderDrawRect( renderer, &rect );
}

void MainUiManager::renderTextToScreen(const char *text, const SDL_Color& fg, int x, int y) {
    Texture texture;
    texture.loadFromText(mainFont, text, fg);
    texture.render(x, y);
}

void MainUiManager::renderImageToScreen(SDL_Surface* image, int x, int y) {
    Texture texture;
    texture.loadFromSurface(image);
    texture.render(x, y);
}
