#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <GL/glew.h>
#include "GLUtil.hpp"

class Sprite {
    protected:
        //

    public:
        Sprite();
        virtual ~Sprite();

        virtual bool init();

        // Set camera position etc.? Basically matrix operations
        virtual void draw()=0;
};

class TexturedSprite : public Sprite {
    protected:
        constexpr static GLvertex2 vertices[] = { {-1,-1}, {1,-1}, {-1,1}, {1,1} };
        constexpr static GLtexcoord texcoords[] = { {0,0}, {1,0}, {0,1}, {1,1} };
        constexpr static GLcolorRGB colors[] = { {0,0,1}, {0,1,0}, {1,0,1}, {1,1,0} };

        static GLuint vao; // vertex array
        static GLuint vbo; // vertices
        static GLuint cvbo; // colours
        //static GLuint tvbo; // textures

    public:
        TexturedSprite();
        virtual ~TexturedSprite();

        static bool initClass();
        virtual void draw();
};

class GeometricSprite : public Sprite {
    protected:
        // dynamic arrays
        GLvertex2 *vertices;
        GLcolorRGB *colors;
        GLuint *indices;

        GLuint vao;
        GLuint vbo;
        GLuint cvbo;
        GLuint ibo;

    public:
        GeometricSprite();
        virtual ~GeometricSprite();

        bool init();
        virtual void draw()=0;
};

#endif // SPRITE_HPP
