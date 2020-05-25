#ifndef GL_UTIL_HPP
#define GL_UTIL_HPP

#include <GL/glew.h>

// Preset location of vertex attributes in the vertex shaders
// Should align with the specs in the vertex shaders
// Also recall that there can be at most 16 vertex attributes, for most GPUs
#define VERTEX_ATTRIB_POSITION_LOCATION     0
#define VERTEX_ATTRIB_TEXCOORDS_LOCATION    1
#define VERTEX_ATTRIB_COLOUR_LOCATION       2

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
