#include "ShaderProgram.hpp"

#include <cstdio>

// OpenGL shader error reporting
void printProgramLog(GLuint program) {
    if (!glIsProgram(program)) {
        printf("Name %d is not a program!\n", program);
        return;
    }

    // Program log length
    int infoLogLength = 0;
    int maxLength = infoLogLength;

    //Get info string length
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

    //Allocate string
    char* infoLog = new char[maxLength];

    //Get info log
    glGetProgramInfoLog(program, maxLength, &infoLogLength, infoLog);
    if (infoLogLength > 0) {
        //Print Log
        printf("%s\n", infoLog);
    }

    //Deallocate string
    delete[] infoLog;
}
void printShaderLog(GLuint shader) {
    if (!glIsShader(shader)) {
        printf("Name %d is not a shader!\n", shader);
        return;
    }

    //Shader log length
    int infoLogLength = 0;
    int maxLength = infoLogLength;

    //Get info string length
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

    //Allocate string
    char* infoLog = new char[maxLength];

    //Get info log
    glGetShaderInfoLog(shader, maxLength, &infoLogLength, infoLog);
    if (infoLogLength > 0) {
        //Print Log
        printf("%s\n", infoLog);
    }

    //Deallocate string
    delete[] infoLog;
}

bool loadShader(GLuint glProgramID, GLenum shaderType, const GLchar* const* shaderSource) {
    //Create shader
    GLuint shader = glCreateShader(shaderType);

    //Get shader source
    //

    //Set source
    glShaderSource(shader, 1, shaderSource, NULL);

    //Compile source
    glCompileShader(shader);

    //Check shader for errors
    GLint shaderCompiled = GL_FALSE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &shaderCompiled);
    if (shaderCompiled != GL_TRUE) {
        printf("Unable to compile shader %d!\n", shader);
        printShaderLog(shader);
        return false;
    }

    //Attach shader to program
    glAttachShader(glProgramID, shader);

    return true;
}

ShaderProgram::ShaderProgram() {
    id = 0;
}

ShaderProgram::~ShaderProgram() {
    //Free program if it exists
    free();
}

bool ShaderProgram::load() {
    //Generate shader program
	id = glCreateProgram();

    // Load vertex shader
    const GLchar* vertexShaderSource[] = {
        "#version 140\n \
        in vec2 LVertexPos2D;\n \
        void main() {\n \
            gl_Position = vec4(LVertexPos2D.x, LVertexPos2D.y, 0, 1);\n \
        }\n"
    };
    if (!loadShader(id, GL_VERTEX_SHADER, vertexShaderSource) ) {
        printf("Could not load vertex shader!\n");
        return false;
    }

    // Load fragment shader
    const GLchar* fragmentShaderSource[] = {
        "#version 140\n \
        out vec4 LFragment; \
        void main() { \
            LFragment = vec4(1, .3, .7, 1); \
        }"
    };
	if (!loadShader(id, GL_FRAGMENT_SHADER, fragmentShaderSource) ) {
        printf("Could not load fragment shader!\n");
        return false;
    }

	//Link shader program
    glLinkProgram(id);

    //Check for errors
    {   GLint programSuccess = GL_TRUE;
        glGetProgramiv(id, GL_LINK_STATUS, &programSuccess);
        if(programSuccess != GL_TRUE) {
            printf("Error linking program %d!\n", id);
            printProgramLog(id);
            return false;
        }
    }

    return true;
}

void ShaderProgram::free() {
    //Delete program
    glDeleteProgram(id);
}

bool ShaderProgram::bind() {
    //Use shader
    glUseProgram(id);

    //Check for errors
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        printf("Error binding shader program: %x\n", error);
        printProgramLog(id);
        return false;
    }

    return true;
}

void ShaderProgram::unbind() {
    //Use default program
    glUseProgram(0);
}

GLuint ShaderProgram::getID() {
    return id;
}
