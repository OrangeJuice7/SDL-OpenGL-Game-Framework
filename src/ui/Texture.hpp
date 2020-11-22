#ifndef TEXTURE_HPP_INCLUDED
#define TEXTURE_HPP_INCLUDED

#include <GL/glew.h>

class Texture {
    public:
		static Texture blankTexture;

		Texture();
		virtual ~Texture();

        // Called only after OpenGL has been initialized
        static bool initBlankTexture();
        // Note that the dimensions (width only?) of the specified image must be a multiple of 4, or the texture will be slanted (or even segfault?)
        // (Can be corrected by setting glPixelStorei(GL_UNPACK_ALIGNMENT, 1)?)
		bool init(const char* filename);

        void bind();
        static void unbind();

	protected:
		int width,
		    height;
		int numOfChannels;
		GLenum pixelFormat;

		GLuint id;

		bool initBlank();
};

#endif // TEXTURE_HPP_INCLUDED
