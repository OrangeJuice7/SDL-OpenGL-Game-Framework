#include "SpriteManager.hpp"

#include "../basicmath.hpp"

GLvertex2 quadVertices[] = { {-1,-1}, {1,-1}, {-1,1}, {1,1} };
void quadDrawfunc() {
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

bool SpriteManager::loadData() {
    {   GLcolorRGBA colors[] = { {0,0,1,.5f}, {0,1,0,1}, {1,0,1,1}, {1,1,0,1} };
        if (!loadGeometricSprite(SPRITE_ID_GEOM,
                                 quadDrawfunc,
                                 4, quadVertices, colors)) return false;
    }
    if (!loadTexturedSprite(SPRITE_ID_TEX1, "data/textures/crate.jpg")) return false;
    if (!loadTexturedSprite(SPRITE_ID_TEX2, "data/textures/colours.bmp")) return false;
    if (!loadTexturedSprite(SPRITE_ID_TEX3, "data/textures/bit.tga")) return false;
    if (!loadTexturedSprite(SPRITE_ID_TEX4, "data/textures/awesomeface.png")) return false;

    {   GLcolorRGBA colors[] = { {1,1,1,.2f}, {1,1,1,.2f}, {1,1,1,.2f}, {1,1,1,.2f} };
        if (!loadGeometricSprite(SPRITE_ID_WIDGET_BG_DEBUG,
                                 quadDrawfunc,
                                 4, quadVertices, colors)) return false;
    }

    {   const int NUM_OF_VERTICES = 60;
        GLvertex2 vertices[NUM_OF_VERTICES];
        GLcolorRGBA colors[NUM_OF_VERTICES];

        for (int i = 0; i < NUM_OF_VERTICES; ++i) {
            float angle = ((float) i / NUM_OF_VERTICES) * TWO_PI;
            vertices[i].x = cos(angle);
            vertices[i].y = sin(angle);
            colors[i] = {1,1,1,1};
        }

        if (!loadGeometricSprite(SPRITE_ID_CIRCLE,
                                 [](){ glDrawArrays(GL_LINE_LOOP, 0, NUM_OF_VERTICES); },
                                 NUM_OF_VERTICES, vertices, colors)) return false;
    }

    return true;
}
