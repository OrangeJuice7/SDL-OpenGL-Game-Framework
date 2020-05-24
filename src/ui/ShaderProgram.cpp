#include "ShaderProgram.hpp"

#include <cstdio>
#include <string>
#include <fstream>
#include "GLUtil.hpp"

ShaderUniform1f::ShaderUniform1f()
        : ShaderUniform<GLfloat>() {}
ShaderUniform1f::~ShaderUniform1f() {}
void ShaderUniform1f::load() {
    glUniform1f(loc, value);
}

ShaderUniform2f::ShaderUniform2f()
        : ShaderUniform<GLvertex2>() {}
ShaderUniform2f::~ShaderUniform2f() {}
void ShaderUniform2f::load() {
    glUniform2f(loc, value.x, value.y);
}

ShaderUniform3f::ShaderUniform3f()
        : ShaderUniform<GLvertex3>() {}
ShaderUniform3f::~ShaderUniform3f() {}
void ShaderUniform3f::load() {
    glUniform3f(loc, value.x, value.y, value.z);
}

ShaderUniform1ui::ShaderUniform1ui()
        : ShaderUniform<GLuint>() {}
ShaderUniform1ui::~ShaderUniform1ui() {}
void ShaderUniform1ui::load() {
    glUniform1ui(loc, value);
}



// OpenGL shader error reporting
void printProgramLog(GLuint program) {
    if (!glIsProgram(program)) {
        printf("Name %d is not a program!\n", program);
        return;
    }

    // Program log length
    int infoLogLength = 0;
    int maxLength = infoLogLength;

    // Get info string length
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

    // Allocate string
    char* infoLog = new char[maxLength];

    // Get info log
    glGetProgramInfoLog(program, maxLength, &infoLogLength, infoLog);
    if (infoLogLength > 0) {
        // Print Log
        printf("%s\n", infoLog);
    }

    // Deallocate string
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

    // Get info string length
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

    // Allocate string
    char* infoLog = new char[maxLength];

    // Get info log
    glGetShaderInfoLog(shader, maxLength, &infoLogLength, infoLog);
    if (infoLogLength > 0) {
        // Print Log
        printf("%s\n", infoLog);
    }

    // Deallocate string
    delete[] infoLog;
}

bool loadShader(GLuint glProgramID, GLenum shaderType, const char* shaderSourcePath) {
    // Create shader
    GLuint shaderID = glCreateShader(shaderType);

    // Get shader source
    std::string shaderString;
    {   // Open file
        std::ifstream sourceFile(shaderSourcePath);
        if (!sourceFile) {
            printf("Unable to open shader source file: %s\n", shaderSourcePath);
            return false;
        }

        // Get shader source
        shaderString.assign(
            std::istreambuf_iterator<char>(sourceFile),
            std::istreambuf_iterator<char>() );
    }

    // Set source
    const GLchar* shaderSource = shaderString.c_str();
    glShaderSource(shaderID, 1, (const GLchar**)&shaderSource, NULL);

    // Compile source
    glCompileShader(shaderID);

    // Check shader for errors
    GLint shaderCompiled = GL_FALSE;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &shaderCompiled);
    if (shaderCompiled != GL_TRUE) {
        printf("Unable to compile shader %d!\n", shaderID);
        printShaderLog(shaderID);
        glDeleteShader(shaderID);
        return false;
    }

    // Attach shader to program
    glAttachShader(glProgramID, shaderID);

    // Clean up excess shader references
    glDeleteShader(shaderID);

    return true;
}



ShaderProgram::ShaderProgram()
        : screenDimensions()
        , translateVector()
        , mapScale()
        , objectScale()
        , colorMask()
        , flags() {

    id = 0;
}
ShaderProgram::~ShaderProgram() {
    // Free program if it exists
    free();
}

template <class T>
bool ShaderProgram::loadUniform(ShaderUniform<T>& uniform, const char* name) {
    if (uniform.setLoc(id, name) == -1) {
        printf("Unable to load shader uniform \"%s\"! Error: %s\n", name, glErrorToString(glGetError()) );
        return false;
    }
    return true;
}

bool ShaderProgram::load(
        const char* vertexShaderFilepath,
        const char* fragmentShaderFilepath) {

    // Generate shader program
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

	// Link shader program
    glLinkProgram(id);

    // Check for errors
    {   GLint programSuccess = GL_TRUE;
        glGetProgramiv(id, GL_LINK_STATUS, &programSuccess);
        if(programSuccess != GL_TRUE) {
            printf("Error linking program %d!\n", id);
            printProgramLog(id);
            return false;
        }
    }

    // Load uniforms
    if (!loadUniform(screenDimensions, "screenDimensions")) return false;
    if (!loadUniform(translateVector, "translate")) return false;
    if (!loadUniform(mapScale, "mapScale")) return false;
    if (!loadUniform(objectScale, "objectScale")) return false;
    if (!loadUniform(colorMask, "colorMask")) return false;
    if (!loadUniform(flags, "flags")) return false;

    return true;
}

void ShaderProgram::free() {
    // Delete program
    glDeleteProgram(id);
}

void ShaderProgram::setScreenDimensions(int width, int height) {
    screenDimensions.value.x = ( width >= 1) ?  width : 1;
    screenDimensions.value.y = (height >= 1) ? height : 1;
    screenDimensions.load();
}

bool ShaderProgram::bind() {
    // Use shader
    glUseProgram(id);

    // Check for errors
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        printf("Error binding shader program: %s\n", glErrorToString(error));
        printProgramLog(id);
        return false;
    }

    return true;
}

void ShaderProgram::unbind() {
    // Use default program
    glUseProgram(0);
}

GLuint ShaderProgram::getID() {
    return id;
}

void ShaderProgram::resetUniforms() {
    resetTransform();
    resetFlags();
}

void ShaderProgram::setTranslate(GLfloat x, GLfloat y) {
    // Note: better to expand the struct out to reduce ambiguity
    translateVector.value.x = x;
    translateVector.value.y = y;
    translateVector.load();
}
void ShaderProgram::setMapScale(GLfloat scale) {
    mapScale.value = scale;
    mapScale.load();
}
void ShaderProgram::setObjectScale(GLfloat scale) {
    setObjectScale(scale, scale);
}
void ShaderProgram::setObjectScale(GLfloat xscale, GLfloat yscale) {
    objectScale.value.x = xscale;
    objectScale.value.y = yscale;
    objectScale.load();
}
void ShaderProgram::resetTransform() {
    setTranslate(0, 0);
    setMapScale(16);
    setObjectScale(1);
}

void ShaderProgram::setColorMask(GLcolorRGB color) {
    colorMask.value.x = color.r;
    colorMask.value.y = color.g;
    colorMask.value.z = color.b;
    colorMask.load();
}
void ShaderProgram::resetColorMask() {
    setColorMask({1,1,1}); // Set all white
}

void ShaderProgram::setFlags(GLuint flags) {
    this->flags.value = flags;
    this->flags.load();
}
void ShaderProgram::addFlags(GLuint flags) {
    this->flags.value |= flags;
    this->flags.load();
}
void ShaderProgram::removeFlags(GLuint flags) {
    this->flags.value &= ~flags;
    this->flags.load();
}
void ShaderProgram::resetFlags() {
    setFlags(0);
}
