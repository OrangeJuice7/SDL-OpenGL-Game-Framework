#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <GL/glew.h>
#include <functional>
#include "GLUtil.hpp"
#include "Texture.hpp"

class Sprite {
    public:
        Sprite(std::function<void()> drawfunc);
        virtual ~Sprite();

        virtual void deinit();

        virtual GLuint getVAO()=0;

        // Transformations should be set before calling this function
        virtual void draw();

    protected:
        /**
         * Allowed to call:
         * - glDrawArrays, glDrawElements
         * - Texture bindings and parameters?
         * (Future: function accepts a UiManager and is allowed to pass arguments to it? Watch for cyclic/recursive definitions)
         */
        std::function<void()> drawfunc;
};

class TexturedSprite : public Sprite {
    public:
        TexturedSprite();
        virtual ~TexturedSprite();

        // Called only after OpenGL has been initialized
        static bool initClass();
        virtual bool init(const char* filename);

        virtual GLuint getVAO();

        void draw();

    protected:
        constexpr static GLvertex2 classVertices[] = { {-1,-1}, {1,-1}, {-1,1}, {1,1} };
        constexpr static GLtexcoord classTexcoords[] = { {0,0}, {1,0}, {0,1}, {1,1} };

        static GLuint classVao; // vertex array
        static GLuint classVbo; // vertices
        static GLuint classTvbo; // textures

        Texture texture;
};

class AtlasSprite : public TexturedSprite { // draws one part of a texture atlas
    public:
        AtlasSprite();
        ~AtlasSprite();

        // Doesn't actually override the old init() from TexturedSprite :S (Don't call that!)
        bool init(const char* filename, unsigned short numOfSpritesX, unsigned short numOfSpritesY);

        GLuint getVAO();

        static void setPhase(bool isLooped, float xPhase, float yPhase);

    protected:
         // Arrays now. Convention: y is the big step, x is the small step.
        GLuint *vaos;
        GLuint *tvbos;

        // How many sprites fit in each column/row of the texture
        // Should be >= 1 each
        unsigned short numOfSpritesX;
        unsigned short numOfSpritesY;

        // Which sprite in the atlas to draw.
        // Ranges from 0 to 1, wrapped around.
        // Defined this way for independence from the actual number of frames in the sprite, and also save some admin calculations from the calling side.
        // Sadly, have to define the phase out here instead of passing directly to draw(), in order to keep draw() polymorphic
        static bool isLooped;
        static float xPhase;
        static float yPhase;
};

class GeometricSprite : public Sprite {
    public:
        // vertices and colors should be arrays
        GeometricSprite(std::function<void()> drawfunc);
        ~GeometricSprite();

        // Called only after OpenGL has been initialized
        bool init(
                GLuint numOfVertices,
                const GLvertex2* vertices,
                const GLcolorRGBA* colors);
        void deinit();

        // function to update and reload vertices?

        GLuint getVAO();

        void draw();

    protected:
        GLuint vao;
        GLuint vbo;
        GLuint cvbo; // colours
        //GLuint ibo;
};

#endif // SPRITE_HPP
