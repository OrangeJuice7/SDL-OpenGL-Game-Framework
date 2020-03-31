#include "Texture.hpp"

#include <cstdio>
#include <SDL_image.h>

SDL_Renderer* Texture::renderer = NULL;

Texture::Texture() {
	texture = NULL;
	width = 0;
	height = 0;
}

Texture::~Texture() {
	free();
}

bool Texture::create(Uint32 format, int access, int vwidth, int vheight) {
    //Get rid of preexisting texture
    free();

    width = vwidth;
    height = vheight;
    texture = SDL_CreateTexture(renderer, format, access, width, height);

    if (texture == NULL) {
        printf("Unable to create texture! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

bool Texture::loadFromSurface(SDL_Surface* surface) {
	//Get rid of preexisting texture
	free(); // also sets texture to NULL

    if (surface == NULL) {
        printf("No surface provided!\n");
        return false;
    }

    //Create texture from surface pixels
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL) {
        printf("Unable to create texture from surface! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    // Assign properties
    width = surface->w;
    height = surface->h;

	return true;
}

bool Texture::loadFromFile(const char* path) {
    SDL_Surface* surface = IMG_Load(path);
    if (surface == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
        return false;
    }

    bool isSuccessful = loadFromSurface(surface);

    SDL_FreeSurface(surface);

	return isSuccessful;
}

bool Texture::loadFromText(TTF_Font* font, const char* text, SDL_Color textColor) {
	SDL_Surface* surface = TTF_RenderUTF8_Blended(font, text, textColor);
    if (surface == NULL) {
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        return false;
    }

    bool isSuccessful = loadFromSurface(surface);

    SDL_FreeSurface(surface);

	return isSuccessful;
}

void Texture::free() {
	if (texture == NULL) return;

    SDL_DestroyTexture(texture);
    texture = NULL;
    width = 0;
    height = 0;
}

int Texture::getWidth() {
	return width;
}

int Texture::getHeight() {
	return height;
}

void Texture::setRenderer(SDL_Renderer* renderer) {
    Texture::renderer = renderer;
}

void Texture::setColor(Uint8 red, Uint8 green, Uint8 blue) {
	SDL_SetTextureColorMod(texture, red, green, blue);
}

void Texture::setColor(SDL_Color color) {
	setColor(color.r, color.g, color.b);
}

void Texture::setAlpha(Uint8 alpha) {
	SDL_SetTextureAlphaMod(texture, alpha);
}

void Texture::setBlendMode(SDL_BlendMode blending) {
	SDL_SetTextureBlendMode(texture, blending);
}

void Texture::updateRow(int rowIndex, const void* pixels, int bytesperpixel) {
    SDL_Rect rect = {0, rowIndex, width, 1};
    SDL_UpdateTexture(texture, &rect, pixels, width * bytesperpixel);
}

void Texture::render(
        int x,
        int y,
        SDL_Rect* clip,
        double angle,
        SDL_Point* center,
        SDL_RendererFlip flip) {

	SDL_Rect renderQuad = {x, y, width, height};

	if (clip != NULL) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	renderStretched(&renderQuad, clip, angle, center, flip);
}

void Texture::renderStretched(
        SDL_Rect* dst,
        SDL_Rect* clip,
        double angle,
        SDL_Point* center,
        SDL_RendererFlip flip) {

	SDL_RenderCopyEx(renderer, texture, clip, dst, angle, center, flip);
}
