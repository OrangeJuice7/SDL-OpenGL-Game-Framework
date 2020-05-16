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
        virtual void draw();
};

class TexturedSprite : public Sprite {
    protected:
        constexpr static GLvertex2 vertices[] = { {-1,-1}, {1,-1}, {-1,1}, {1,1} };
        constexpr static GLtexcoord texcoords[] = { {0,0}, {1,0}, {0,1}, {1,1} };
        constexpr static GLcolorRGB colors[] = { {0,0,1}, {0,1,0}, {1,0,1}, {1,1,0} };
        constexpr static GLuint indices[] = { 0, 1, 2, 3 };

        static GLuint vao; // vertex array
        static GLuint vbo; // vertices
        static GLuint cvbo; // colours
        //static GLuint tvbo; // textures
        static GLuint ibo; // indices

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
        GLcolorRGB *colours;
        GLuint *indices;

        GLuint vbo;
        GLuint ibo;

    public:
        GeometricSprite();
        virtual ~GeometricSprite();
};

#endif // SPRITE_HPP
