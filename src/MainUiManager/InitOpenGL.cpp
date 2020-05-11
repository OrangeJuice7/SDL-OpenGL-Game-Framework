#include "MainUiManager.hpp"

#include <cstdio>

// OpenGL shader error reporting
void printProgramLog(GLuint program) {
    // Make sure name is shader
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
    // Make sure name is shader
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
    /*const GLchar* shaderSource[] = {
        "#version 140\nin vec2 LVertexPos2D; void main() { gl_Position = vec4( LVertexPos2D.x, LVertexPos2D.y, 0, 1 ); }"
    };*/

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

bool MainUiManager::initOpenGL() {
    //Use OpenGL 3.1 core
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    //Create context
    glContext = SDL_GL_CreateContext(mainWindow);
    if(glContext == NULL) {
        printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    //Initialize GLEW
    glewExperimental = GL_TRUE; // Enable experimental features (actually needed for compatibility)
    GLenum glewError = glewInit();
    if(glewError != GLEW_OK) {
        printf("Error initializing GLEW! %s\n", glewGetErrorString(glewError));
    }

    //Use Vsync
    if(SDL_GL_SetSwapInterval(1) < 0) {
        printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
    }

    //Generate shader program
	glProgramID = glCreateProgram();

    // Load vertex shader
    const GLchar* vertexShaderSource[] = {
        "#version 140\n \
        in vec2 LVertexPos2D; \
        void main() { \
            gl_Position = vec4( LVertexPos2D.x, LVertexPos2D.y, 0, 1 ); \
        }"
    };
    if (!loadShader(glProgramID, GL_VERTEX_SHADER, vertexShaderSource) ) {
        printf("Could not load vertex shader!\n");
        return false;
    }

    // Load fragment shader
    const GLchar* fragmentShaderSource[] = {
        "#version 140\n \
        out vec4 LFragment; \
        void main() { \
            LFragment = vec4( 1.0, 1.0, 1.0, 1.0 ); \
        }"
    };
	if (!loadShader(glProgramID, GL_FRAGMENT_SHADER, fragmentShaderSource) ) {
        printf("Could not load fragment shader!\n");
        return false;
    }

	//Link shader program
    glLinkProgram(glProgramID);

    //Check for errors
    {   GLint programSuccess = GL_TRUE;
        glGetProgramiv(glProgramID, GL_LINK_STATUS, &programSuccess);
        if(programSuccess != GL_TRUE) {
            printf("Error linking program %d!\n", glProgramID);
            printProgramLog(glProgramID);
            return false;
        }
    }

    //Get vertex attribute location
    glVertexPos2DLocation = glGetAttribLocation(glProgramID, "LVertexPos2D");
    if(glVertexPos2DLocation == -1) {
        printf("LVertexPos2D is not a valid GLSL program variable!\n");
        return false;
    }

    //Initialize clear color
    glClearColor( 0.f, 0.f, 0.f, 1.f );

    //VBO data
    GLfloat vertexData[] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f
    };

    //Create VBO
    glGenBuffers(1, &glVBO);
    glBindBuffer(GL_ARRAY_BUFFER, glVBO);
    glBufferData(GL_ARRAY_BUFFER, 2*4*sizeof(GLfloat), vertexData, GL_STATIC_DRAW);

    //IBO data
    GLuint indexData[] = { 0, 1, 2, 3 };

    //Create IBO
    glGenBuffers(1, &glIBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4*sizeof(GLuint), indexData, GL_STATIC_DRAW);

    return true;
}

void MainUiManager::deinitOpenGL() {
    //Deallocate shader program
	glDeleteProgram(glProgramID);
}
