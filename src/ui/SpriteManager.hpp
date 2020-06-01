#ifndef SPRITE_MANAGER_HPP
#define SPRITE_MANAGER_HPP

#include <GL/glew.h>
#include "Sprite.hpp"
#include "SpriteId.hpp"

class SpriteManager {
    protected:
        Sprite* sprites[SPRITE_ID_COUNT];

        // Defines and loads sprite and texture data on the spot
        // Defined in SpriteData.cpp
        // Called within init()
        bool loadData();

        // Helper functions for loadData()
        bool loadTexturedSprite(
                SpriteId id,
                const char* filename);
        bool loadAtlasSprite(
                SpriteId id,
                const char* filename,
                unsigned short numOfSpritesX,
                unsigned short numOfSpritesY);
        bool loadGeometricSprite(
                SpriteId id,
                std::function<void()> drawfunc,
                GLuint numOfVertices,
                const GLvertex2* vertices,
                const GLcolorRGBA* colors);

    public:
        SpriteManager();
        ~SpriteManager();

        // Called only after OpenGL has been initialized
        // Loads and generates all the textures and sprites
        bool init();
        void deinit();

        // Gets the sprite specified by the id.
        // Returns nullptr if id is out of range.
        Sprite* getSprite(SpriteId id) const;
};

#endif // SPRITE_MANAGER_HPP
