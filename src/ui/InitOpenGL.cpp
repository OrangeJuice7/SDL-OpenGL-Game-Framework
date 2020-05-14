#include "MainUiManager.hpp"

#include <cstdio>
#include "GLUtil.hpp"

#define VERTEX_SHADER_FILEPATH "src/ui/default.vert"
#define FRAGMENT_SHADER_FILEPATH "src/ui/default.frag"

bool MainUiManager::initOpenGL() {
    // Use OpenGL 3.3 core
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // Create context
    glContext = SDL_GL_CreateContext(mainWindow);
    if (glContext == NULL) {
        printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    // Initialize GLEW
    glewExperimental = GL_TRUE; // Enable experimental features (actually needed for compatibility)
    GLenum glewError = glewInit();
    if (glewError != GLEW_OK) {
        printf("Error initializing GLEW! %s\n", glewGetErrorString(glewError));
        return false;
    }
    if (!GLEW_VERSION_3_3) {
        printf("OpenGL 3.3 not supported!\n");
        return false;
    }

    // Use Vsync
    if(SDL_GL_SetSwapInterval(1) < 0) {
        printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
    }

    // Set the viewport
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    // Initialize clear color
    // Some dark blue, just to check if graphics are working, and if there's any coloured object hidden by the bg
    glClearColor(0.0282f, 0.062f, 0.121f, 1);

    // Enable depth (won't be needing this in a 2D app)
    //glEnable(GL_DEPTH_TEST);

    // Enable backface culling
    glEnable(GL_CULL_FACE);

    // Wireframe mode
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // normal mode
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // Set blending
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Set point size
    glPointSize(2.0f);

    // Set line width
    glLineWidth(2.0f);
    // Enable line antialiasing
    glEnable(GL_LINE_SMOOTH);

    // Check for errors
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        printf("Error initializing OpenGL: %s\n", glErrorToString(error));
        return false;
    }

    if (!TexturedSprite::initClass()) {
        printf("Could not initialize textured sprites!\n");
        return false;
    }

    // generate shader program
    if (!shaderProgram.load(VERTEX_SHADER_FILEPATH, FRAGMENT_SHADER_FILEPATH)) {
        printf("Could not load shader program!\n");
        return false;
    }
    if (!shaderProgram.bind()) {
        printf("Could not bind shader program!\n");
        return false;
    }

    return true;
}

void MainUiManager::deinitOpenGL() {
    // Deallocate shader program
	shaderProgram.free();
}
