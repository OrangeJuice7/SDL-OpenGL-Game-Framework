#ifndef MAIN_UI_MANAGER_HPP
#define MAIN_UI_MANAGER_HPP

#include <SDL.h>
#include <SDL_ttf.h> // http://www.sdltutorials.com/sdl-ttf
#include "Texture.hpp"
#include "InputState.hpp"
class Scene;

class MainUiManager {
    protected:
        // The main window
        SDL_Window* mainWindow;
        SDL_Renderer* renderer;

        TTF_Font* mainFont;

        Uint32 uiTick;

        MouseState mouseState;
        KeyboardState keyboardState;

        bool initSDL();
        bool initWindow(); // requires initSDL()
        bool initRenderer();
        bool initFont();
        bool initTextures(); // requires initWindow()

        void deinitSDL();
        void deinitWindow();
        void deinitRenderer();
        void deinitFont();
        void deinitTextures();

    public:
        const char *WINDOW_TITLE;
        const int SCREEN_WIDTH;
        const int SCREEN_HEIGHT;
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

        // Draws the scene to screen
        void draw(Scene* scene);

        void setDrawColor(Uint8 r, Uint8 g, Uint8 b);
        void setDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
        void setDrawColor(const SDL_Color& color);
        void drawPixel(int x, int y);
        void drawLine(int x1, int y1, int x2, int y2);
        void drawFillRect(const SDL_Rect& rect);
        void drawLineRect(const SDL_Rect& rect);
        void drawLineCircle(float x, float y, float r);
        void renderTextToScreen(const char *text, const SDL_Color& fg, int x, int y);
        void renderImageToScreen(SDL_Surface* image, int x, int y);
};

#endif // MAIN_UI_MANAGER_HPP
