#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <GL/glew.h>
#include <functional>
#include "GLUtil.hpp"
#include "Texture.hpp"

class Sprite {
    protected:
        /**
         * Allowed to call:
         * - glDrawArrays, glDrawElements
         * - Texture bindings and parameters
         */
        std::function<void()> drawfunc;

    public:
        Sprite(std::function<void()> drawfunc);
        virtual ~Sprite();

        virtual GLuint getVAO()=0;

        // Transformations should be set before calling this function
        virtual void draw();
};

class TexturedSprite : public Sprite {
    protected:
        constexpr static GLvertex2 vertices[] = { {-1,-1}, {1,-1}, {-1,1}, {1,1} };
        constexpr static GLtexcoord texcoords[] = { {0,0}, {1,0}, {0,1}, {1,1} };

        static GLuint vao; // vertex array
        static GLuint vbo; // vertices
        static GLuint tvbo; // textures

        Texture texture;

    public:
        //TexturedSprite(Texture texture);
        TexturedSprite();
        ~TexturedSprite();

        static bool initClass();
        bool init(const char* filename);
        void deinit();

        GLuint getVAO();

        void draw();
};

class GeometricSprite : public Sprite {
    protected:
        GLuint numOfVertices;
        // pointers to arrays outside
        const GLvertex2 *vertices;
        const GLcolorRGBA *colors;
        //GLuint *indices;

        GLuint vao;
        GLuint vbo;
        GLuint cvbo; // colours
        //GLuint ibo;

    public:
        // vertices and colors should be arrays
        GeometricSprite(
                GLuint numOfVertices,
                const GLvertex2* vertices,
                const GLcolorRGBA* colors,
                std::function<void()> drawfunc);
        ~GeometricSprite();

        bool init();
        void deinit();

        // function to update and reload vertices?

        GLuint getVAO();

        void draw();
};

#endif // SPRITE_HPP
