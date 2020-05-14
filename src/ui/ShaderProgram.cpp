#include "ShaderProgram.hpp"

#include <cstdio>
#include <string>
#include <fstream>
#include "GLUtil.hpp"

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

bool loadShader(GLuint glProgramID, GLenum shaderType, const char* shaderSourcePath) {
    //Create shader
    GLuint shaderID = glCreateShader(shaderType);

    //Get shader source
    std::string shaderString;
    {   //Open file
        std::ifstream sourceFile(shaderSourcePath);
        if (!sourceFile) {
            printf("Unable to open shader source file: %s\n", shaderSourcePath);
            return false;
        }

        //Get shader source
        shaderString.assign(
            std::istreambuf_iterator<char>(sourceFile),
            std::istreambuf_iterator<char>() );
    }

    //Set source
    const GLchar* shaderSource = shaderString.c_str();
    glShaderSource(shaderID, 1, (const GLchar**)&shaderSource, NULL);

    //Compile source
    glCompileShader(shaderID);

    //Check shader for errors
    GLint shaderCompiled = GL_FALSE;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &shaderCompiled);
    if (shaderCompiled != GL_TRUE) {
        printf("Unable to compile shader %d!\n", shaderID);
        printShaderLog(shaderID);
        glDeleteShader(shaderID);
        return false;
    }

    //Attach shader to program
    glAttachShader(glProgramID, shaderID);

    // Clean up excess shader references
    glDeleteShader(shaderID);

    return true;
}

ShaderProgram::ShaderProgram() {
    id = 0;
}

ShaderProgram::~ShaderProgram() {
    //Free program if it exists
    free();
}

bool ShaderProgram::load(
        const char* vertexShaderFilepath,
        const char* fragmentShaderFilepath) {

    //Generate shader program
	id = glCreateProgram();

    // Load vertex shader
    if (!loadShader(id, GL_VERTEX_SHADER, vertexShaderFilepath) ) {
        printf("Could not load vertex shader!\n");
        return false;
    }

    // Load fragment shader
	if (!loadShader(id, GL_FRAGMENT_SHADER, fragmentShaderFilepath) ) {
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
        printf("Error binding shader program: %s\n", glErrorToString(error));
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
