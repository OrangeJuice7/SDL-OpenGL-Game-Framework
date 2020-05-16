#include "MainUiManager.hpp"

#include "../basicmath.hpp"

void MainUiManager::resetTransform() {
    shaderProgram.resetTransform();
}
void MainUiManager::setTranslate(GLfloat x, GLfloat y) {
    shaderProgram.setTranslate(x, y);
}
void MainUiManager::setScale(GLfloat x, GLfloat y) {
    shaderProgram.setScale(x, y);
}
void MainUiManager::setScale(GLfloat scale) {
    shaderProgram.setScale(scale);
}

void MainUiManager::setDrawColor(Uint8 r, Uint8 g, Uint8 b) {
    setDrawColor(r, g, b, 0xff);
}
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
}

void MainUiManager::drawFillRect(const SDL_Rect& rect) {
    SDL_RenderFillRect( renderer, &rect );
}

void MainUiManager::drawLineRect(const SDL_Rect& rect) {
    SDL_RenderDrawRect( renderer, &rect );
}

void MainUiManager::drawLineCircle(float x, float y, float r) {
    int numOfPoints = (int)(TWO_PI * sqrt(r)) +1;

    SDL_Point *points = new SDL_Point[numOfPoints];
    for (int i = 0; i < numOfPoints-1; ++i) {
        float angle = TWO_PI * i / (numOfPoints-1);
        points[i].x = (int)(x + sin(angle)*r);
        points[i].y = (int)(y + cos(angle)*r);
    }
    points[numOfPoints-1] = points[0]; // somehow the last point is anomalous

    SDL_RenderDrawLines(renderer, points, numOfPoints);

    delete[] points;
}

void MainUiManager::renderTextToScreen(const char *text, const SDL_Color& fg, int x, int y) {
    /*Texture texture;
    texture.loadFromText(mainFont, text, fg);
    texture.render(x, y);*/
}

void MainUiManager::renderImageToScreen(SDL_Surface* image, int x, int y) {
    /*Texture texture;
    texture.loadFromSurface(image);
    texture.render(x, y);*/
}
