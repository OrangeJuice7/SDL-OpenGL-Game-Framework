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
void UiManager::setObjectScale(GLfloat xscale, GLfloat yscale) {
    shaderProgram.setObjectScale(xscale, yscale);
}

void UiManager::setDrawToGameSpace() {
    shaderProgram.removeFlags(SHADER_FLAG_ORTHO_MODE);
}
void UiManager::setDrawToScreenSpace() {
    shaderProgram.addFlags(SHADER_FLAG_ORTHO_MODE);
}

void UiManager::setColorMask(GLcolorRGB color) {
    shaderProgram.setColorMask(color);
}
void UiManager::resetColorMask() {
    shaderProgram.resetColorMask();
}

void UiManager::setFont(FontId fontId, FontsizeId fontsizeId) {
    textManager.setActiveFont(fontId, fontsizeId);
}

void UiManager::drawSprite(float x, float y, SpriteId id) {
    setTranslate(x, y);
    getSprite(id)->draw();
}
void UiManager::drawSpriteStretched(float x, float y, float width, float height, SpriteId id) {
    float halfwidth = width*.5f,
          halfheight = height*.5f;
    setTranslate(x + halfwidth, y + halfheight);
    setObjectScale(halfwidth, halfheight);
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
