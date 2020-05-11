#ifndef SHADER_PROGRAM_HPP
#define SHADER_PROGRAM_HPP

#include <GL/glew.h>
//#include <SDL2/SDL_opengl.h>

class ShaderProgram {
    protected:
        GLuint id; // Program ID

    public:
        ShaderProgram();
        virtual ~ShaderProgram();

        // Requires a valid OpenGL context
        virtual bool load(); // Expand this later to be able to accept source file names
        virtual void free();

        // Sets this program as the current shader program
        // Requires a loaded program
        bool bind();
        void unbind();

        GLuint getID();
};

#endif // SHADER_PROGRAM_HPP
