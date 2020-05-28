#ifndef UI_MANAGER_HPP
#define UI_MANAGER_HPP

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h> // Needs to come after glew.h
#include "ShaderProgram.hpp"
#include "SpriteManager.hpp"
#include "TextManager.hpp"
#include "InputState.hpp"
#include "ModelCamera.hpp"
class Scene;

class UiManager {
    protected:
        // SDL
        SDL_Window* mainWindow;
        bool isFullscreen;
        SDL_Rect screenRect; // Screen dimensions
        float screenHalfWidth; // Half-sizes to save some runtime computations
        float screenHalfHeight;

        // OpenGL
        SDL_GLContext glContext; // Rendering context
        ShaderProgram shaderProgram;
        SpriteManager spriteManager;
        TextManager textManager;

        // Hardware input states
        MouseState mouseState;
        KeyboardState keyboardState;

        // Utility
        const ModelCamera *camera; // Reference to a ModelCamera in a Scene
        ModelCamera _dummy_camera; // Exists only to make sure camera is not nullptr
        bool orthoMode; // ortho = drawing to screen coords instead of game coords

        Uint32 uiTick;

        bool initSDL();
        bool initOpenGL();
        bool initWindow(); // requires initSDL()

        void deinitSDL();
        void deinitOpenGL();
        void deinitWindow();

        Sprite* getSprite(SpriteId id) const;

        void setScreenRect(int width, int height);

    public:
        const char *WINDOW_TITLE;

        float fps; // For display purposes only; is written to by MainApp.

        UiManager(const char *windowTitle);
        ~UiManager();
        bool init();
        void deinit();

        Uint32 getUiTick() const;
        bool getIsFullscreen() const;
        int getScreenWidth() const;
        int getScreenHeight() const;
        const SDL_Rect& getScreenRect() const;

        void sleep(float duration); // in seconds, capped at millisecond precision

        // Collect hardware inputs and pass them to scene for interpretation
        void getInputs(Scene* scene);

        // Converts screen coords to game coords. Primarily used to convert mouse input.
        // Screen coords are in the way OpenGL is specified to draw them (i.e. +x/+y = right/up, origin at lower left corner)
        void screenToGameCoords(float& gameX, float& gameY, float screenX, float screenY);
        // Converts game coords to screen coords. Primarily used to check if something is visible, and thus whether drawing can be skipped.
        void gameToScreenCoords(float& screenX, float& screenY, float gameX, float gameY);

        // Window manipulation
        void setFullscreen();
        void setWindowed();
        void toggleFullscreen();

        void updateWindowSize(int width, int height);

        // Draws the scene to screen
        void draw(Scene* scene);

        void saveScreenshot(const char* filename);

        // Set draw parameters, defined in Render.cpp
        // (mainly just passes the info to this object's underlying ShaderProgram)
        void setCamera(const ModelCamera &camera);
        void setObjectTranslate(GLfloat x, GLfloat y);
        void setObjectScale(GLfloat scale);
        void setObjectScale(GLfloat xscale, GLfloat yscale);
        void resetTransform(); // Sets some values for the transformation that are guaranteed to be valid, though may not make objects visible

        void setDrawToGameSpace(); // Prepare to draw to the game scene: use game coords
        void setDrawToScreenSpace(); // Prepare to draw to the screen: use screen coords (i.e. pixels), following OpenGL coord specs (i.e. +x/+y = right/up)

        void setColorMask(const GLcolorRGB& color);
        void resetColorMask();

        void setFont(FontId fontId, FontsizeId fontsizeId);

        // Draw functions, defined in Render.cpp
        void drawSprite(float x, float y, SpriteId id);
        void drawSpriteStretched(float x, float y, float width, float height, SpriteId id);
        void drawText(float x, float y, const char* text); // Draws a single unwrapped line, implement wrap later
};

#endif // UI_MANAGER_HPP
