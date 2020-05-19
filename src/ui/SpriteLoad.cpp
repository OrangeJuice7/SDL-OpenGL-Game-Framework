#include "SpriteManager.hpp"

GLvertex2 vertices[] = { {-1,-1}, {1,-1}, {-1,1}, {1,1} };
GLcolorRGBA colors[] = { {0,0,1,.5f}, {0,1,0,1}, {1,0,1,1}, {1,1,0,1} };
void drawfunc() {
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

bool SpriteManager::loadData() {
    if (!loadGeometricSprite(SPRITE_ID_GEOM, drawfunc, 4, vertices, colors)) return false;
    if (!loadTexturedSprite(SPRITE_ID_TEX1, "data/textures/crate.jpg")) return false;
    if (!loadTexturedSprite(SPRITE_ID_TEX2, "data/textures/colours.bmp")) return false;
    if (!loadTexturedSprite(SPRITE_ID_TEX3, "data/textures/bit.tga")) return false;
    if (!loadTexturedSprite(SPRITE_ID_TEX4, "data/textures/awesomeface.png")) return false;

    return true;
}
