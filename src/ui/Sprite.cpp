#include "Sprite.hpp"

#include <cstdio>
#include <cmath> // for floor() used in AtlasSprite

Sprite::Sprite(std::function<void()> drawfunc) {
    this->drawfunc = drawfunc;
}
Sprite::~Sprite() {}

void Sprite::deinit() {}

void Sprite::draw() {
    glBindVertexArray( getVAO() );
    drawfunc();
}



constexpr GLvertex2 TexturedSprite::classVertices[];
constexpr GLtexcoord TexturedSprite::classTexcoords[];
GLuint TexturedSprite::classVao = 0;
GLuint TexturedSprite::classVbo = 0;
GLuint TexturedSprite::classTvbo = 0;

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
    glGenVertexArrays(1, &classVao);
    glGenBuffers(1, &classVbo);
    glGenBuffers(1, &classTvbo);

    //Check for errors
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        printf("Error generating TexturedSprite buffers: %s\n", glErrorToString(error));
        return false;
    }

    // Load data into buffers
    glBindVertexArray(classVao);

    // Load vertex data
    glBindBuffer(GL_ARRAY_BUFFER, classVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(classVertices), classVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(VERTEX_ATTRIB_POSITION_LOCATION, 2, GL_FLOAT, GL_FALSE, sizeof(GLvertex2), (void*)0);
    glEnableVertexAttribArray(VERTEX_ATTRIB_POSITION_LOCATION);

    // Load texture vertices
    glBindBuffer(GL_ARRAY_BUFFER, classTvbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(classTexcoords), classTexcoords, GL_STATIC_DRAW);
    glVertexAttribPointer(VERTEX_ATTRIB_TEXCOORDS_LOCATION, 2, GL_FLOAT, GL_FALSE, sizeof(GLvertex2), (void*)0);
    glEnableVertexAttribArray(VERTEX_ATTRIB_TEXCOORDS_LOCATION);

    // Disable colour
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
    return classVao;
}

void TexturedSprite::draw() {
    texture.bind();
    Sprite::draw();
}



bool AtlasSprite::isLooped = true;
float AtlasSprite::xPhase = 0;
float AtlasSprite::yPhase = 0;
AtlasSprite::AtlasSprite()
        : TexturedSprite() {

    numOfSpritesX = numOfSpritesY = 1;
}
AtlasSprite::~AtlasSprite() {
    delete[] vaos;
    delete[] tvbos;
}

bool AtlasSprite::init(const char* filename, unsigned short numOfSpritesX, unsigned short numOfSpritesY) {
    if (numOfSpritesX < 1 || numOfSpritesY < 1) {
        return false;
    }
    this->numOfSpritesX = numOfSpritesX;
    this->numOfSpritesY = numOfSpritesY;
    unsigned short numOfSpritesTotal = numOfSpritesX * numOfSpritesY;
    GLfloat spriteSizeX = 1.f / numOfSpritesX,
            spriteSizeY = 1.f / numOfSpritesY;

    if (!TexturedSprite::init(filename)) { // Init the texture
        return false;
    }

    // Generate buffer objects
    vaos = new GLuint[numOfSpritesTotal];
    tvbos = new GLuint[numOfSpritesTotal];
    glGenVertexArrays(numOfSpritesTotal, vaos);
    glGenBuffers(numOfSpritesTotal, tvbos);

    //Check for errors
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        printf("Error generating TexturedSprite buffers: %s\n", glErrorToString(error));
        return false;
    }

    for (unsigned short n = 0; n < numOfSpritesTotal; ++n) {
        unsigned short x = n % numOfSpritesX,
                       y = n / numOfSpritesX;
        GLfloat tx =  x    * spriteSizeX,
                ty =  y    * spriteSizeY,
                tX = (x+1) * spriteSizeX,
                tY = (y+1) * spriteSizeY;
        // Recall TexturedSprite defines the coords in this order: {0,0}, {1,0}, {0,1}, {1,1}
        GLvertex2 texcoords[] = { {tx,ty}, {tX,ty}, {tx,tY}, {tX,tY} };

        // Load data into buffers
        glBindVertexArray(vaos[n]);

        // Load vertex data
        glBindBuffer(GL_ARRAY_BUFFER, classVbo); // reuse TexturedSprite's vertices
        glBufferData(GL_ARRAY_BUFFER, sizeof(classVertices), classVertices, GL_STATIC_DRAW);
        glVertexAttribPointer(VERTEX_ATTRIB_POSITION_LOCATION, 2, GL_FLOAT, GL_FALSE, sizeof(GLvertex2), (void*)0);
        glEnableVertexAttribArray(VERTEX_ATTRIB_POSITION_LOCATION);

        // Load texture vertices
        glBindBuffer(GL_ARRAY_BUFFER, tvbos[n]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(texcoords), texcoords, GL_STATIC_DRAW);
        glVertexAttribPointer(VERTEX_ATTRIB_TEXCOORDS_LOCATION, 2, GL_FLOAT, GL_FALSE, sizeof(GLvertex2), (void*)0);
        glEnableVertexAttribArray(VERTEX_ATTRIB_TEXCOORDS_LOCATION);

        // Disable colour
        glDisableVertexAttribArray(VERTEX_ATTRIB_COLOUR_LOCATION);
        glVertexAttrib3f(VERTEX_ATTRIB_COLOUR_LOCATION, 1, 1, 1);
    }

    //Check for errors
    error = glGetError();
    if (error != GL_NO_ERROR) {
        printf("Error binding TexturedSprite data to buffers: %s\n", glErrorToString(error));
        return false;
    }

    return true;
}

GLuint AtlasSprite::getVAO() {
    unsigned short x, y;
    if (isLooped) {
        x = (unsigned short)(xPhase * numOfSpritesX + .5f); if (x >= numOfSpritesX) x -= numOfSpritesX;
        y = (unsigned short)(yPhase * numOfSpritesY + .5f); if (y >= numOfSpritesY) y -= numOfSpritesY;
    } else {
        x = (unsigned short)(xPhase * numOfSpritesX);
        y = (unsigned short)(yPhase * numOfSpritesY);
    }

    return vaos[y*numOfSpritesX + x];
}

void AtlasSprite::setPhase(bool isLooped, float xPhase, float yPhase) {
    AtlasSprite::isLooped = isLooped;
    if (isLooped) {
        AtlasSprite::xPhase = xPhase - floor(xPhase);
        AtlasSprite::yPhase = yPhase - floor(yPhase);
    } else {
        if (xPhase > .9999f) xPhase = .9999f; else if (xPhase < .0001f) xPhase = .0001f; // Some tolerance to eliminate float rounding errors in getVAO()
        if (yPhase > .9999f) yPhase = .9999f; else if (yPhase < .0001f) yPhase = .0001f;
        AtlasSprite::xPhase = xPhase;
        AtlasSprite::yPhase = yPhase;
    }
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

    // Disable texcoords
    glDisableVertexAttribArray(VERTEX_ATTRIB_TEXCOORDS_LOCATION);

    // Load colours
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
