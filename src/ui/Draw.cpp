#include "UiManager.hpp"

#include "../util/math.hpp"

void UiManager::setCamera(const ModelCamera &camera) {
    this->camera = &camera;
}
void UiManager::setObjectTranslate(GLfloat x, GLfloat y) {
    if (orthoMode) {
        // Translate origin to lower left of screen
        x -= screenHalfWidth;
        y -= screenHalfHeight;
    } else {
        x -= camera->getX();
        y -= camera->getY();
    }
    shaderProgram.setObjectTranslate(x, y);
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
    orthoMode = false;

    // Load camera settings
    shaderProgram.setCoordToScreenScale(
        camera->getScale() / screenHalfWidth,
        camera->getScale() / screenHalfHeight);
}
void UiManager::setDrawToScreenSpace() {
    orthoMode = true;

    shaderProgram.setCoordToScreenScale(
        1.f / screenHalfWidth,
        1.f / screenHalfHeight);
}

void UiManager::setColorMask(const GLcolorRGB& color) {
    shaderProgram.setColorMask(color);
}
void UiManager::resetColorMask() {
    shaderProgram.resetColorMask();
}

void UiManager::setAtlasPhase(bool isLooped, float xPhase, float yPhase) {
    AtlasSprite::setPhase(isLooped, xPhase, yPhase);
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
        setObjectTranslate((int)x, (int)y); // Align text to pixels so the glyphs are crisp
        x += textManager.drawChar(text[i]);
    }
    shaderProgram.removeFlags(SHADER_FLAG_RENDER_TEXT);
}
