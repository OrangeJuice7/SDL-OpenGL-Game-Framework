#include "Sprite.hpp"

#include <cstdio>

Sprite::Sprite() {}
Sprite::~Sprite() {}
bool Sprite::init() {
    return true;
}
void Sprite::draw() {}

constexpr GLvertex2 TexturedSprite::vertices[];
constexpr GLtexcoord TexturedSprite::texcoords[];
constexpr GLcolorRGB TexturedSprite::colors[];
constexpr GLuint TexturedSprite::indices[];
GLuint TexturedSprite::vao = 0;
GLuint TexturedSprite::vbo = 0;
GLuint TexturedSprite::cvbo = 0;
GLuint TexturedSprite::ibo = 0;
TexturedSprite::TexturedSprite()
        : Sprite () {}
TexturedSprite::~TexturedSprite() {
    // Delete buffer objects (put in static destructor)
    //glDeleteBuffers(1, &vbo);
    //glDeleteBuffers(1, &ibo);
}

bool TexturedSprite::initClass() {
    // Generate buffer objects
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &cvbo);
    glGenBuffers(1, &ibo);

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
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, cvbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(2);

    // Load texture vertices
    //glBufferData(GL_TEXTURE_BUFFER, sizeof(texcoords), texcoords, GL_STATIC_DRAW);

    // Load indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //Check for errors
    error = glGetError();
    if (error != GL_NO_ERROR) {
        printf("Error binding TexturedSprite data to buffers: %s\n", glErrorToString(error));
        return false;
    }

    return true;
}

void TexturedSprite::draw() {
    /*//glTranslatef(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f, 0);
    glBegin(GL_QUADS);
        glColor3f(1.f, .3f, .7f);
        glVertex2f(-0.2f, -0.2f);
        glVertex2f( 0.2f, -0.2f);
        glVertex2f( 0.2f,  0.2f);
        glVertex2f(-0.2f,  0.2f);
    glEnd();*/

    // Bind VAO
    glBindVertexArray(vao);

    // glDrawArrays() if IBO is not used
    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, (void*)0);
}

GeometricSprite::GeometricSprite()
        : Sprite () {}
GeometricSprite::~GeometricSprite() {}
