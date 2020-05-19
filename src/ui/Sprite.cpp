#include "Sprite.hpp"

#include <cstdio>

Sprite::Sprite(std::function<void()> drawfunc) {
    this->drawfunc = drawfunc;
}
Sprite::~Sprite() {}

void Sprite::deinit() {}

void Sprite::draw() {
    glBindVertexArray( getVAO() );
    drawfunc();
}



constexpr GLvertex2 TexturedSprite::vertices[];
constexpr GLtexcoord TexturedSprite::texcoords[];
GLuint TexturedSprite::vao = 0;
GLuint TexturedSprite::vbo = 0;
GLuint TexturedSprite::tvbo = 0;

void texturedSpriteDrawfunc() {
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    //glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, (void*)0); // Alternative using IBO
}
TexturedSprite::TexturedSprite()
        : Sprite(texturedSpriteDrawfunc)
        , texture() {}
TexturedSprite::~TexturedSprite() {}

bool TexturedSprite::initClass() {
    // Generate buffer objects
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &tvbo);

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
    glVertexAttribPointer(VERTEX_ATTRIB_POSITION_LOCATION, 2, GL_FLOAT, GL_FALSE, sizeof(GLvertex2), (void*)0);
    glEnableVertexAttribArray(VERTEX_ATTRIB_POSITION_LOCATION);

    // Load texture vertices
    glBindBuffer(GL_ARRAY_BUFFER, tvbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texcoords), texcoords, GL_STATIC_DRAW);
    glVertexAttribPointer(VERTEX_ATTRIB_TEXCOORDS_LOCATION, 2, GL_FLOAT, GL_FALSE, sizeof(GLvertex2), (void*)0);
    glEnableVertexAttribArray(VERTEX_ATTRIB_TEXCOORDS_LOCATION);

    glDisableVertexAttribArray(VERTEX_ATTRIB_COLOUR_LOCATION);
    glVertexAttrib3f(VERTEX_ATTRIB_COLOUR_LOCATION, 1, 1, 1);

    //Check for errors
    error = glGetError();
    if (error != GL_NO_ERROR) {
        printf("Error binding TexturedSprite data to buffers: %s\n", glErrorToString(error));
        return false;
    }

    return true;
}
bool TexturedSprite::init(const char* filename) {
    if (!texture.init(filename)) {
        return false;
    }
    return true;
}

GLuint TexturedSprite::getVAO() {
    return vao;
}

void TexturedSprite::draw() {
    texture.bind();
    Sprite::draw();
}



GeometricSprite::GeometricSprite(std::function<void()> drawfunc)
        : Sprite (drawfunc) {}
GeometricSprite::~GeometricSprite() {}

bool GeometricSprite::init(
        GLuint numOfVertices,
        const GLvertex2* vertices,
        const GLcolorRGBA* colors) {

    // Generate buffer objects
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &cvbo);
    //glGenBuffers(1, &ibo);

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
    glBufferData(GL_ARRAY_BUFFER, numOfVertices*sizeof(GLvertex2), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(VERTEX_ATTRIB_POSITION_LOCATION, 2, GL_FLOAT, GL_FALSE, sizeof(GLvertex2), (void*)0);
    glEnableVertexAttribArray(VERTEX_ATTRIB_POSITION_LOCATION);

    glDisableVertexAttribArray(VERTEX_ATTRIB_TEXCOORDS_LOCATION);

    glBindBuffer(GL_ARRAY_BUFFER, cvbo);
    glBufferData(GL_ARRAY_BUFFER, numOfVertices*sizeof(GLcolorRGBA), colors, GL_STATIC_DRAW);
    glVertexAttribPointer(VERTEX_ATTRIB_COLOUR_LOCATION, 4, GL_FLOAT, GL_FALSE, sizeof(GLcolorRGBA), (void*)0);
    glEnableVertexAttribArray(VERTEX_ATTRIB_COLOUR_LOCATION);

    // Load indices
    /*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

    //Check for errors
    error = glGetError();
    if (error != GL_NO_ERROR) {
        printf("Error binding GeometricSprite data to buffers: %s\n", glErrorToString(error));
        return false;
    }

    return true;
}
void GeometricSprite::deinit() {
    // Delete buffer objects
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &cvbo);
    //glDeleteBuffers(1, &ibo);
}

GLuint GeometricSprite::getVAO() {
    return vao;
}

void GeometricSprite::draw() {
    Texture::unbind();
    Sprite::draw();
}
