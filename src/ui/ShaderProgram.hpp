#ifndef SHADER_PROGRAM_HPP
#define SHADER_PROGRAM_HPP

#include <GL/glew.h>
#include "GLUtil.hpp"

template <class T>
class ShaderUniform {
    protected:
        int loc; // Location in the shader program

    public:
        // Freely viewable and modifiable value
        T value;

        ShaderUniform() {}
        virtual ~ShaderUniform() {}

        int getLoc() {
            return loc;
        }

        // Returns loc
        // Will set loc to -1 if params are invalid
        int setLoc(
                GLuint programId,
                const char* name) { // Variable name in the shader program

            return loc = glGetUniformLocation(programId, name);
        }

        // Load uniform into shader
        // Essentially calls the appropriate glUniform function based on T
        virtual void load()=0;
};
class ShaderUniform2f : public ShaderUniform<GLvertex2> {
    public:
        ShaderUniform2f();
        ~ShaderUniform2f();

        void load();
};



class ShaderProgram {
    protected:
        GLuint id; // Program ID

        // Shader uniforms
        ShaderUniform2f translateVector;
        ShaderUniform2f scaleVector;

        // Cached screen dimensions to help with transformations
        int screenWidth;
        int screenHeight;

        // Retrieves uniform info (just location for now) from the shader
        // Returns true on success
        template <class T>
        bool loadUniform(
                ShaderUniform<T>& uniform,
                const char* name); // Variable name in the shader program

    public:
        ShaderProgram();
        virtual ~ShaderProgram();

        // Compiles and links the given shaders to this program
        // Requires a valid OpenGL context
        virtual bool load(
                const char* vertexShaderFilepath,
                const char* fragmentShaderFilepath);
        virtual void free();

        // Sets screenWidth/screenHeight to 1 if given width/height is less than 1
        void setScreenDimensions(int width, int height);

        // Sets this program as the current shader program
        // Requires a loaded program
        bool bind();
        void unbind();

        GLuint getID();

        // Push default values for uniforms to the shader program
        // Assumes this shader is already bound
        void resetTransform(); // Reset vertex transformations only
        void resetUniforms(); // Reset everything

        // Update the uniforms into the shaders
        // Assumes this shader is already bound
        void setTranslate(GLfloat x, GLfloat y); // In coords (+x/+y direction is right/up)
        void setScale(GLfloat x, GLfloat y); // Length of one coord in pixels
        void setScale(GLfloat scale);
};

#endif // SHADER_PROGRAM_HPP
