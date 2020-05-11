#ifndef TEXTURE_HPP_INCLUDED
#define TEXTURE_HPP_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h> // http://www.sdltutorials.com/sdl-ttf

class Texture {
	protected:
		static SDL_Renderer* renderer;

		SDL_Texture* texture;

		int width;
		int height;

    public:
		Texture();
		~Texture();

		bool create(Uint32 format, int access, int vwidth, int vheight);
		bool loadFromSurface(SDL_Surface* surface);
		bool loadFromFile(const char* path);
		bool loadFromText(TTF_Font* font, const char* text, SDL_Color textColor);

		void free();

		int getWidth();
		int getHeight();

		static void setRenderer(SDL_Renderer* renderer);

		void setColor(Uint8 red, Uint8 green, Uint8 blue);
		void setColor(SDL_Color color);
		void setAlpha(Uint8 alpha);
		void setBlendMode(SDL_BlendMode blending);

		void updateRow(int rowIndex, const void* pixels, int bytesperpixel);

		void render(
                int x,
                int y,
                SDL_Rect* clip = NULL,
                double angle = 0.0,
                SDL_Point* center = NULL,
                SDL_RendererFlip flip = SDL_FLIP_NONE);
		void renderStretched(
                SDL_Rect* dst,
                SDL_Rect* clip = NULL,
                double angle = 0.0,
                SDL_Point* center = NULL,
                SDL_RendererFlip flip = SDL_FLIP_NONE);
};

#endif // TEXTURE_HPP_INCLUDED
