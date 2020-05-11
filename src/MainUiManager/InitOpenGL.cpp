#include "MainUiManager.hpp"

#include <cstdio>

#define VERTEX_SHADER_FILEPATH "default.vert"
#define FRAGMENT_SHADER_FILEPATH "default.frag"

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
        return false;
    }
    if (!GLEW_VERSION_3_1) {
        printf("OpenGL 3.1 not supported!\n");
        return false;
    }

    //Use Vsync
    if(SDL_GL_SetSwapInterval(1) < 0) {
        printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
    }

    //Set the viewport
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    //Initialize Projection Matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 1, -1);

    //Initialize Modelview Matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //Initialize clear color
    glClearColor(0.05f, 0.1f, 0.2f, 1); // Some dark blue, just to check if graphics are working

    //Enable texturing
    glEnable(GL_TEXTURE_2D);

    //Set blending
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //Check for errors
    GLenum error = glGetError();
    if(error != GL_NO_ERROR) {
        printf("Error initializing OpenGL: %x\n", error);
        return false;
    }

    // generate shader program
    if(!shaderProgram.load(VERTEX_SHADER_FILEPATH, FRAGMENT_SHADER_FILEPATH)) {
        printf("Could not load shader program!\n");
        return false;
    }
    if(!shaderProgram.bind()) {
        printf("Could not bind shader program!\n");
        return false;
    }

    //Get vertex attribute location
    /*glVertexPos2DLocation = glGetAttribLocation(glProgramID, "LVertexPos2D");
    if(glVertexPos2DLocation == -1) {
        printf("LVertexPos2D is not a valid GLSL program variable!\n");
        return false;
    }*/

    //VBO data
    /*GLfloat vertexData[] = {
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
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4*sizeof(GLuint), indexData, GL_STATIC_DRAW);*/

    return true;
}

void MainUiManager::deinitOpenGL() {
    //Deallocate shader program
	shaderProgram.free();
}
