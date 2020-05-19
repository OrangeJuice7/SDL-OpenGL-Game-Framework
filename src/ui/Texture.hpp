#ifndef TEXTURE_HPP_INCLUDED
#define TEXTURE_HPP_INCLUDED

#include <GL/glew.h>

class Texture {
	protected:
		int width,
		    height;
		int numOfChannels;
		GLenum pixelFormat;

		GLuint id;

		bool initBlank();

    public:
		static Texture blankTexture;

		Texture();
		~Texture();

        // Called only after OpenGL has been initialized
        static bool initBlankTexture();
		bool init(const char* filename);

        void bind();
        static void unbind();
};

#endif // TEXTURE_HPP_INCLUDED
