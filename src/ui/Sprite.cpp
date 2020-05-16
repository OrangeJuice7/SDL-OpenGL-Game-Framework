#include "Sprite.hpp"

#include <cstdio>

Sprite::Sprite() {}
Sprite::~Sprite() {}
bool Sprite::init() {
    return true;
}

constexpr GLvertex2 TexturedSprite::vertices[];
constexpr GLtexcoord TexturedSprite::texcoords[];
constexpr GLcolorRGB TexturedSprite::colors[];
GLuint TexturedSprite::vao = 0;
GLuint TexturedSprite::vbo = 0;
GLuint TexturedSprite::cvbo = 0;
TexturedSprite::TexturedSprite()
        : Sprite () {}
TexturedSprite::~TexturedSprite() {}

bool TexturedSprite::initClass() {
    // Generate buffer objects
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &cvbo);

    //Check for errors
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        printf("Error generating TexturedSprite buffers: %s\n", glErrorToString(error));
        return false;
    }

    // Load data into buffers
    glBindVertexArray(vao);

    // Load vertex data
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(VERTEX_ATTRIB_POSITION_LOCATION, 2, GL_FLOAT, GL_FALSE, 2*sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(VERTEX_ATTRIB_POSITION_LOCATION);

    glBindBuffer(GL_ARRAY_BUFFER, cvbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    glVertexAttribPointer(VERTEX_ATTRIB_COLOUR_LOCATION, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(VERTEX_ATTRIB_COLOUR_LOCATION);

    // Load texture vertices
    //glBufferData(GL_TEXTURE_BUFFER, sizeof(texcoords), texcoords, GL_STATIC_DRAW);

    //Check for errors
    error = glGetError();
    if (error != GL_NO_ERROR) {
        printf("Error binding TexturedSprite data to buffers: %s\n", glErrorToString(error));
        return false;
    }

    return true;
}

void TexturedSprite::draw() {
    // Bind VAO
    glBindVertexArray(vao);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    //glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, (void*)0); // Alternative using IBO
}

GeometricSprite::GeometricSprite()
        : Sprite () {}
GeometricSprite::~GeometricSprite() {
    // Delete buffer objects
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &cvbo);
    glDeleteBuffers(1, &ibo);
}

bool GeometricSprite::init() {
    // Generate buffer objects
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &cvbo);
    glGenBuffers(1, &ibo);

    //Check for errors
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        printf("Error generating GeometricSprite buffers: %s\n", glErrorToString(error));
        return false;
    }

    // Load data into buffers
    glBindVertexArray(vao);

    // Load vertex data
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(VERTEX_ATTRIB_POSITION_LOCATION, 2, GL_FLOAT, GL_FALSE, 2*sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(VERTEX_ATTRIB_POSITION_LOCATION);

    glBindBuffer(GL_ARRAY_BUFFER, cvbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    glVertexAttribPointer(VERTEX_ATTRIB_COLOUR_LOCATION, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(VERTEX_ATTRIB_COLOUR_LOCATION);

    // Load indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //Check for errors
    error = glGetError();
    if (error != GL_NO_ERROR) {
        printf("Error binding GeometricSprite data to buffers: %s\n", glErrorToString(error));
        return false;
    }

    return true;
}
