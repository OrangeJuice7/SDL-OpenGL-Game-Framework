#include "UiManager.hpp"

#include "../basicmath.hpp"

void UiManager::resetTransform() {
    shaderProgram.resetTransform();
}
void UiManager::setTranslate(GLfloat x, GLfloat y) {
    shaderProgram.setTranslate(x, y);
}
void UiManager::setMapScale(GLfloat scale) {
    shaderProgram.setMapScale(scale);
}
void UiManager::setObjectScale(GLfloat scale) {
    shaderProgram.setObjectScale(scale);
}

void UiManager::setDrawToGameSpace() {
    shaderProgram.removeFlags(SHADER_FLAG_ORTHO_MODE);
}
void UiManager::setDrawToScreenSpace() {
    shaderProgram.addFlags(SHADER_FLAG_ORTHO_MODE);
}

void UiManager::setFont(FontId fontId, FontsizeId fontsizeId) {
    textManager.setActiveFont(fontId, fontsizeId);
}

void UiManager::drawSprite(float x, float y, SpriteId id) {
    setTranslate(x, y);
    getSprite(id)->draw();
}
void UiManager::drawText(float x, float y, const char* text) {
    shaderProgram.addFlags(SHADER_FLAG_RENDER_TEXT);
    for (int i = 0; text[i] != '\0'; ++i) {
        setTranslate(x, y);
        x += textManager.drawChar(text[i]);
    }
    shaderProgram.removeFlags(SHADER_FLAG_RENDER_TEXT);
}



void UiManager::setDrawColor(Uint8 r, Uint8 g, Uint8 b) {
    setDrawColor(r, g, b, 0xff);
}
void UiManager::setDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
}
void UiManager::setDrawColor(const SDL_Color& color) {
    setDrawColor(color.r, color.g, color.b, color.a);
}

void UiManager::drawPixel(int x, int y) {
    SDL_RenderDrawPoint(renderer, x, y);
}

void UiManager::drawLine(int x1, int y1, int x2, int y2) {
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void UiManager::drawFillRect(const SDL_Rect& rect) {
    SDL_RenderFillRect( renderer, &rect );
}

void UiManager::drawLineRect(const SDL_Rect& rect) {
    SDL_RenderDrawRect( renderer, &rect );
}

void UiManager::drawLineCircle(float x, float y, float r) {
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

void UiManager::renderTextToScreen(const char *text, const SDL_Color& fg, int x, int y) {
    /*Texture texture;
    texture.loadFromText(mainFont, text, fg);
    texture.render(x, y);*/
}

void UiManager::renderImageToScreen(SDL_Surface* image, int x, int y) {
    /*Texture texture;
    texture.loadFromSurface(image);
    texture.render(x, y);*/
}
