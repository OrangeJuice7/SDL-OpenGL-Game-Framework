#ifndef UI_MANAGER_HPP
#define UI_MANAGER_HPP

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h> // Needs to come after glew.h
#include "ShaderProgram.hpp"
#include "SpriteManager.hpp"
#include "TextManager.hpp"
#include "InputState.hpp"
class Scene;

class UiManager {
    protected:
        // SDL
        SDL_Window* mainWindow;
        SDL_Renderer* renderer;

        // OpenGL
        SDL_GLContext glContext; // Rendering context
        ShaderProgram shaderProgram;
        SpriteManager spriteManager;
        TextManager textManager;

        // Hardware input states
        MouseState mouseState;
        KeyboardState keyboardState;

        // Utility
        Uint32 uiTick;

        bool initSDL();
        bool initOpenGL();
        bool initWindow(); // requires initSDL()
        bool initRenderer();

        void deinitSDL();
        void deinitOpenGL();
        void deinitWindow();
        void deinitRenderer();

        Sprite* getSprite(SpriteId id);

    public:
        const char *WINDOW_TITLE;
        const int SCREEN_WIDTH;
        const int SCREEN_HEIGHT; // Won't be constant anymore in the future for arbitrary window resizes
        const SDL_Rect SCREEN_RECT;

        float fps; // For display purposes only; is written to by MainApp.

        UiManager(const char *windowTitle, int screenWidth, int screenHeight);
        ~UiManager();
        bool init();
        void deinit();

        Uint32 getUiTick();
        void sleep(float duration); // in seconds, capped at millisecond precision

        // Collect hardware inputs and pass them to scene for interpretation
        void getInputs(Scene* scene);

        // Draws the scene to screen
        void draw(Scene* scene);

        // Set draw parameters, defined in Render.cpp
        // (mainly just passes the info to this object's underlying ShaderProgram)
        void resetTransform(); // Sets some values for the transformation that are guaranteed to be valid, though may not make objects visible
        void setTranslate(GLfloat x, GLfloat y);
        void setMapScale(GLfloat scale);
        void setObjectScale(GLfloat scale);
        void setObjectScale(GLfloat xscale, GLfloat yscale);
        void setDrawToGameSpace(); // Prepare to draw to the game scene: use game coords
        void setDrawToScreenSpace(); // Prepare to draw to the screen: use screen coords (i.e. pixels), following OpenGL coord specs (i.e. +x/+y = right/up)
        void setFont(FontId fontId, FontsizeId fontsizeId);

        void setDrawColor(Uint8 r, Uint8 g, Uint8 b);
        void setDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
        void setDrawColor(const SDL_Color& color);

        // Draw functions, defined in Render.cpp
        void drawSprite(float x, float y, SpriteId id);
        void drawSpriteStretched(float x, float y, float width, float height, SpriteId id);
        void drawText(float x, float y, const char* text); // Draws a single unwrapped line, implement wrap later

        void drawPixel(int x, int y);
        void drawLine(int x1, int y1, int x2, int y2);
        void drawFillRect(const SDL_Rect& rect);
        void drawLineRect(const SDL_Rect& rect);
        void drawLineCircle(float x, float y, float r);
        void renderTextToScreen(const char *text, const SDL_Color& fg, int x, int y);
        void renderImageToScreen(SDL_Surface* image, int x, int y);
};

#endif // UI_MANAGER_HPP
