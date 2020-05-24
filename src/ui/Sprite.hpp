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
         * - Texture bindings and parameters?
         * (Future: function accepts a MainUiManager and is allowed to pass arguments to it? Watch for cyclic/recursive definitions)
         */
        std::function<void()> drawfunc;

    public:
        Sprite(std::function<void()> drawfunc);
        virtual ~Sprite();

        virtual void deinit();

        virtual GLuint getVAO()=0;

        // Transformations should be set before calling this function
        virtual void draw();
};

class TexturedSprite : public Sprite {
    protected:
        constexpr static GLvertex2 vertices[] = { {-1,-1}, {1,-1}, {-1,1}, {1,1} };
        constexpr static GLtexcoord texcoords[] = { {0,1}, {1,1}, {0,0}, {1,0} }; // Note: loaded textures are y-inverted

        static GLuint vao; // vertex array
        static GLuint vbo; // vertices
        static GLuint tvbo; // textures

        Texture texture;

    public:
        //TexturedSprite(Texture texture);
        TexturedSprite();
        ~TexturedSprite();

        // Called only after OpenGL has been initialized
        static bool initClass();
        bool init(const char* filename);

        GLuint getVAO();

        void draw();
};

class GeometricSprite : public Sprite {
    protected:
        GLuint vao;
        GLuint vbo;
        GLuint cvbo; // colours
        //GLuint ibo;

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
};

#endif // SPRITE_HPP
