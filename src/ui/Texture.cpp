#include "Texture.hpp"

#include <cstdio>
#include <SOIL.h>

Texture Texture::blankTexture;
Texture::Texture() {
    width = height = 0;
    numOfChannels = 0;
    pixelFormat = GL_RGB;
	id = 0;
}
Texture::~Texture() {}

bool Texture::initBlank() {
    GLubyte data[] = {0xff, 0xff, 0xff};

    width = height = 1;
    numOfChannels = 3;
    pixelFormat = GL_RGB;

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D(GL_TEXTURE_2D, 0, pixelFormat, width, height, 0, pixelFormat, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	return true;
}
bool Texture::initBlankTexture() {
    return blankTexture.initBlank();
}
bool Texture::init(const char* filename) {
    // Load data from file
    GLubyte *data = SOIL_load_image(filename, &width, &height, &numOfChannels, SOIL_LOAD_AUTO);

    if (!data) {
        printf("Error: Failed to load texture \"%s\". Missing or corrupted file?\n", filename);
        return false;
    }
    switch (numOfChannels) {
        default:
            printf("Error: Invalid number of channels (%d) in loaded texture \"%s\"\n", numOfChannels, filename);
            return false;
        case 1: pixelFormat = GL_RED; break;
        case 2: pixelFormat = GL_RG; break;
        case 3: pixelFormat = GL_RGB; break;
        case 4: pixelFormat = GL_RGBA; break;
    }

    // Generate texture
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D(GL_TEXTURE_2D, 0, pixelFormat, width, height, 0, pixelFormat, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    // Set parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Horizontal mapping mode
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Vertical mapping mode
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // scale-down filter
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // scale-up filter

    // Free pixel data
    SOIL_free_image_data(data);

    return true;
}

void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, id);
}
void Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, blankTexture.id);
}
