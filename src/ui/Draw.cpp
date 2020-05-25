#include "UiManager.hpp"

#include "../basicmath.hpp"

void UiManager::setCamera(const ModelCamera &camera) {
    this->camera = &camera;
}
void UiManager::setObjectTranslate(GLfloat x, GLfloat y) {
    if (shaderProgram.hasFlag(SHADER_FLAG_ORTHO_MODE)) {
        // Translate origin to lower left of screen
        x -= SCREEN_WIDTH / 2.f;
        y -= SCREEN_HEIGHT / 2.f;
    } else {
        x -= camera->getX();
        y -= camera->getY();
    }
    shaderProgram.setTranslate(x, y);
}
void UiManager::setObjectScale(GLfloat scale) {
    shaderProgram.setObjectScale(scale);
}
void UiManager::setObjectScale(GLfloat xscale, GLfloat yscale) {
    shaderProgram.setObjectScale(xscale, yscale);
}
void UiManager::resetTransform() {
    shaderProgram.resetTransform();
}

void UiManager::setDrawToGameSpace() {
    shaderProgram.removeFlags(SHADER_FLAG_ORTHO_MODE);

    // Load camera settings
    shaderProgram.setMapScale(camera->getScale());
}
void UiManager::setDrawToScreenSpace() {
    shaderProgram.addFlags(SHADER_FLAG_ORTHO_MODE);
}

void UiManager::setColorMask(const GLcolorRGB& color) {
    shaderProgram.setColorMask(color);
}
void UiManager::resetColorMask() {
    shaderProgram.resetColorMask();
}

void UiManager::setFont(FontId fontId, FontsizeId fontsizeId) {
    textManager.setActiveFont(fontId, fontsizeId);
}

void UiManager::drawSprite(float x, float y, SpriteId id) {
    setObjectTranslate(x, y);
    getSprite(id)->draw();
}
void UiManager::drawSpriteStretched(float x, float y, float width, float height, SpriteId id) {
    float halfwidth = width*.5f,
          halfheight = height*.5f;
    setObjectTranslate(x + halfwidth, y + halfheight);
    setObjectScale(halfwidth, halfheight);
    getSprite(id)->draw();
}
void UiManager::drawText(float x, float y, const char* text) {
    shaderProgram.addFlags(SHADER_FLAG_RENDER_TEXT);
    for (int i = 0; text[i] != '\0'; ++i) {
        setObjectTranslate(x, y);
        x += textManager.drawChar(text[i]);
    }
    shaderProgram.removeFlags(SHADER_FLAG_RENDER_TEXT);
}
