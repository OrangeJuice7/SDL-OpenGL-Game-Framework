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

    public:
		static Texture blankTexture;

		Texture();
		~Texture();

        static bool initBlankTexture();
		bool init(const char* filename);
        void deinit();

        void bind();
        static void unbind();
};

#endif // TEXTURE_HPP_INCLUDED
