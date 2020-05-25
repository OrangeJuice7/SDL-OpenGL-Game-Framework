#include "SpriteManager.hpp"

#include <cstdio>

SpriteManager::SpriteManager() {}
SpriteManager::~SpriteManager() {}

bool SpriteManager::loadTexturedSprite(
        SpriteId id,
        const char* filename) {

    TexturedSprite *sprite = new TexturedSprite();
    if (!sprite->init(filename)) {
        printf("Could not load a TexturedSprite! ID: %d\n", id);
        return false;
    }
    sprites[id] = sprite;
    return true;
}
bool SpriteManager::loadGeometricSprite(
        SpriteId id,
        std::function<void()> drawfunc,
        GLuint numOfVertices,
        const GLvertex2* vertices,
        const GLcolorRGBA* colors) {

    GeometricSprite *sprite = new GeometricSprite(drawfunc);
    if (!sprite->init(numOfVertices, vertices, colors)) {
        printf("Could not load a GeometricSprite! ID: %d\n", id);
        return false;
    }
    sprites[id] = sprite;
    return true;
}

bool SpriteManager::init() {
    if (!Texture::initBlankTexture()) {
        printf("Could not initialize blank texture!\n");
        return false;
    }
    if (!TexturedSprite::initClass()) {
        printf("Could not initialize textured sprites!\n");
        return false;
    }

    // Init textures
    if (!loadData()) {
        printf("Unable to load sprite data!\n");
        return false;
    }

    return true;
}
void SpriteManager::deinit() {
    for (Sprite* sprite : sprites) {
        sprite->deinit();
        delete sprite;
    }
}

Sprite* SpriteManager::getSprite(SpriteId id) const {
    if (id == SPRITE_ID_COUNT) return nullptr;
    return sprites[id];
}
