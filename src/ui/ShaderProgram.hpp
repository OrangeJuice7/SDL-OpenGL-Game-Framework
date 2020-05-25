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
class ShaderUniform1f : public ShaderUniform<GLfloat> {
    public:
        ShaderUniform1f();
        ~ShaderUniform1f();

        void load();
};
class ShaderUniform2f : public ShaderUniform<GLvertex2> {
    public:
        ShaderUniform2f();
        ~ShaderUniform2f();

        void load();
};
class ShaderUniform3f : public ShaderUniform<GLvertex3> {
    public:
        ShaderUniform3f();
        ~ShaderUniform3f();

        void load();
};
class ShaderUniform1ui : public ShaderUniform<GLuint> {
    public:
        ShaderUniform1ui();
        ~ShaderUniform1ui();

        void load();
};



const GLuint SHADER_FLAG_ORTHO_MODE = 1 << 0;
const GLuint SHADER_FLAG_RENDER_TEXT = 1 << 1;

class ShaderProgram {
    protected:
        GLuint id; // Program ID

        // Shader uniforms
        ShaderUniform2f screenDimensions;
        ShaderUniform2f translateVector;
        ShaderUniform1f mapScale;
        ShaderUniform2f objectScale;
        ShaderUniform3f colorMask;
        ShaderUniform1ui flags; // smallest uniform size is uint, sadly

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

        GLuint getID() const;
        bool hasFlag(GLuint flag) const;

        // Reset all uniform values in the shader
        // Assumes this shader is already bound
        void resetUniforms();

        // Update the uniforms into the shaders
        // Assumes this shader is already bound
        void setTranslate(GLfloat x, GLfloat y); // In game coords (+x/+y direction is right/up)
        void setMapScale(GLfloat scale); // Length of one game coord in pixels
        void setObjectScale(GLfloat scale); // Scale of the object in game coords
        void setObjectScale(GLfloat xscale, GLfloat yscale); // scale per dimension
        void resetTransform();

        void setColorMask(const GLcolorRGB& color);
        void resetColorMask();

        void setFlags(GLuint flags); // Note: will reset previously set flags
        void addFlags(GLuint flags);
        void removeFlags(GLuint flags);
        void resetFlags();
};

#endif // SHADER_PROGRAM_HPP
