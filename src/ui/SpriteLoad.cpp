#include "SpriteManager.hpp"

#include "../util/math.hpp"

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

    {   GLvertex2 vertices[] = {
            {-1,-1}, {1,-1}, {-1,1}, {1,1} , // bg quad
            {-1,-1}, {1,-1}, {1,1}, {-1,1} }; // outline
        GLcolorRGBA colors[] = {
            {.1f,.1f,.1f,.6f}, {.1f,.1f,.1f,.6f}, {.1f,.2f,.4f,.6f}, {.1f,.2f,.4f,.6f} ,
            {.8f,1.f,.8f,.8f}, {.8f,1.f,1.f,.8f}, {.8f,1.f,.8f,.8f}, {.8f,1.f,1.f,.8f} };
        if (!loadGeometricSprite(
            SPRITE_ID_WIDGET_BG,
            []() {
                glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
                glDrawArrays(GL_LINE_LOOP     , 4, 4);
            },
            8, vertices, colors)) return false;
    }

    if (!loadTexturedSprite(SPRITE_ID_CURSOR, "data/textures/cursor.tga")) return false;

    {   const int NUM_OF_VERTICES = 8;
        GLvertex2 vertices[NUM_OF_VERTICES+2]; // +1 vertex for the center, +1 vertex to repeat a vertex to close the circle
        GLcolorRGBA colors[NUM_OF_VERTICES+2];

        vertices[0] = {0,0};
        colors[0] = {1,1,1,1};

        for (int i = 1; i <= NUM_OF_VERTICES+1; ++i) {
            float angle = ((float) i / NUM_OF_VERTICES) * TWO_PI;
            vertices[i].x = cos(angle);
            vertices[i].y = sin(angle);
            colors[i] = {1,1,1,0};
        }

        if (!loadGeometricSprite(SPRITE_ID_PARTICLE,
                                 [](){ glDrawArrays(GL_TRIANGLE_FAN, 0, NUM_OF_VERTICES+2); },
                                 NUM_OF_VERTICES+2, vertices, colors)) return false;
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
