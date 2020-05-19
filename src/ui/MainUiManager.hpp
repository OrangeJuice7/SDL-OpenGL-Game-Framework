#ifndef MAIN_UI_MANAGER_HPP
#define MAIN_UI_MANAGER_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h> // http://www.sdltutorials.com/sdl-ttf
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h> // Needs to come after glew.h
#include "ShaderProgram.hpp"
#include "SpriteManager.hpp"
#include "InputState.hpp"
class Scene;

class MainUiManager {
    protected:
        // SDL
        SDL_Window* mainWindow;
        SDL_Renderer* renderer;

        // OpenGL
        SDL_GLContext glContext; // Rendering context
        ShaderProgram shaderProgram;
        SpriteManager spriteManager;

        // Font
        TTF_Font* mainFont;

        // Hardware input states
        MouseState mouseState;
        KeyboardState keyboardState;

        // Utility
        Uint32 uiTick;

        bool initSDL();
        bool initOpenGL();
        bool initWindow(); // requires initSDL()
        bool initRenderer();
        bool initFont();

        void deinitSDL();
        void deinitOpenGL();
        void deinitWindow();
        void deinitRenderer();
        void deinitFont();

    public:
        const char *WINDOW_TITLE;
        const int SCREEN_WIDTH;
        const int SCREEN_HEIGHT; // Won't be constant anymore in the future for arbitrary window resizes
        const SDL_Rect SCREEN_RECT;

        float fps; // For display purposes only; is written to by MainApp.

        MainUiManager(const char *windowTitle, int screenWidth, int screenHeight);
        ~MainUiManager();
        bool init();
        void deinit();

        Uint32 getUiTick();
        void sleep(float duration); // in seconds, capped at millisecond precision

        // Collect hardware inputs and pass them to scene for interpretation
        void getInputs(Scene* scene);

        // Expose sprite access for other programs to use (particularly to invoke draw calls with)
        Sprite* getSprite(SpriteId id);

        // Draws the scene to screen
        void draw(Scene* scene);

        // Set draw parameters
        // (mainly just passes the info to this object's underlying ShaderProgram)
        void resetTransform();
        void setTranslate(GLfloat x, GLfloat y);
        void setMapScale(GLfloat scale);
        void setObjectScale(GLfloat scale);

        void setDrawColor(Uint8 r, Uint8 g, Uint8 b);
        void setDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
        void setDrawColor(const SDL_Color& color);

        // Draw functions
        void drawPixel(int x, int y);
        void drawLine(int x1, int y1, int x2, int y2);
        void drawFillRect(const SDL_Rect& rect);
        void drawLineRect(const SDL_Rect& rect);
        void drawLineCircle(float x, float y, float r);
        void renderTextToScreen(const char *text, const SDL_Color& fg, int x, int y);
        void renderImageToScreen(SDL_Surface* image, int x, int y);
};

#endif // MAIN_UI_MANAGER_HPP
