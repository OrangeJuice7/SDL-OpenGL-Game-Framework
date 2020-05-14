#ifndef SHADER_PROGRAM_HPP
#define SHADER_PROGRAM_HPP

#include <GL/glew.h>

class ShaderProgram {
    protected:
        GLuint id; // Program ID

        /* Can define some shader uniforms here, in derived classes */
    public:
        ShaderProgram();
        virtual ~ShaderProgram();

        // Requires a valid OpenGL context
        virtual bool load(
                const char* vertexShaderFilepath,
                const char* fragmentShaderFilepath);
        virtual void free();

        // Sets this program as the current shader program
        // Requires a loaded program
        bool bind();
        void unbind();

        GLuint getID();
};

#endif // SHADER_PROGRAM_HPP
