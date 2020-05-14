#ifndef GL_UTIL_HPP
#define GL_UTIL_HPP

#include <GL/glew.h>

// Useful structs to define vertex data.
// Do NOT re-order the struct variables.
struct GLvertex2 {
    GLfloat x;
    GLfloat y;
};
struct GLvertex3 {
    GLfloat x;
    GLfloat y;
    GLfloat z;
};

struct GLtexcoord {
    GLfloat u;
    GLfloat v;
};

struct GLcolorRGB {
    GLfloat r;
    GLfloat g;
    GLfloat b;
};
struct GLcolorRGBA {
    GLfloat r;
    GLfloat g;
    GLfloat b;
    GLfloat a;
};

const char* glErrorToString(GLenum error);

#endif // GL_UTIL_HPP
