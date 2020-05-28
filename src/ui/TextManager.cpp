#include "TextManager.hpp"

#include <cstdio>

GlyphTexture::GlyphTexture() : Texture() {}
GlyphTexture::~GlyphTexture() {}
bool GlyphTexture::init(const FT_GlyphSlot &glyph) {
    // Store texture data
    width = glyph->bitmap.width;
    height = glyph->bitmap.rows;
    numOfChannels = 1;
    pixelFormat = GL_RED;

    // Generate texture
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D(GL_TEXTURE_2D, 0, pixelFormat, width, height, 0, pixelFormat, GL_UNSIGNED_BYTE, glyph->bitmap.buffer);
    //glGenerateMipmap(GL_TEXTURE_2D);

    // Set parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return true;
}

void glyphSpriteDrawfunc() {
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}
GlyphSprite::GlyphSprite()
    : Sprite(glyphSpriteDrawfunc)
    , texture() {}
GlyphSprite::~GlyphSprite() {}

bool GlyphSprite::init(const FT_GlyphSlot &glyph) {
    texture.init(glyph);

    float left = glyph->bitmap_left,
          right = left + glyph->bitmap.width,
          top = glyph->bitmap_top,
          bottom = top - glyph->bitmap.rows;
    GLvertex2 vertices[] = { {left,bottom}, {right,bottom}, {left,top}, {right,top} };
    GLtexcoord texcoords[] = { {0,1}, {1,1}, {0,0}, {1,0} }; // Note: loaded textures are y-inverted

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
void GlyphSprite::deinit() {
    // Delete buffer objects
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &tvbo);
    //glDeleteBuffers(1, &ibo);
}

GLuint GlyphSprite::getVAO() {
    return vao;
}

void GlyphSprite::draw() {
    texture.bind();
    Sprite::draw();
}



TextManager::TextManager() {
    fontsizes[FONTSIZE_ID_HEADING] = 40;
    fontsizes[FONTSIZE_ID_SUBHEADING] = 28;
    fontsizes[FONTSIZE_ID_NORMAL] = 18;
    fontsizes[FONTSIZE_ID_SMALL] = 12;

    activeFontId = FONT_ID_STANDARD;
    activeFontsizeId = FONTSIZE_ID_NORMAL;
}
TextManager::~TextManager() {}

bool TextManager::initFont(FT_Library ftlib, FontId fontId, const char *filepath) {
    Font *fontFamily = fonts[fontId];
    FT_Face face;

    // Load TTF font
    auto error = FT_New_Face(ftlib, filepath, 0, &face);
    if (error) {
        printf("Could not load font \"%s\": %s\n", filepath, FT_Error_String(error));
        return false;
    }

    // Generate a font for each size
    // Note: "/ 64.f" operations are to convert from font units (1/64th pixel) to pixels
    for (int fontsizeId = 0; fontsizeId < FONTSIZE_ID_COUNT; ++fontsizeId) {
        Font *font = &(fontFamily[fontsizeId]);

        // Set font height (width=0 is calculated automatically)
        FT_Set_Pixel_Sizes(face, 0, fontsizes[fontsizeId]);
        font->height = face->height / 64.f;

        // Load glyphs
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction, there is only 1 bpp now
        for (unsigned char c = 0; c < TEXT_NUM_OF_SUPPORTED_CHARS; ++c) {
            // Load character glyph
            error = FT_Load_Char(face, c, FT_LOAD_RENDER);
            if (error) {
                printf("Could not load glyph %d [%c]: %s\n", c, c, FT_Error_String(error));
                continue;
            }

            // Store glyph data
            Glyph *glyph = &(font->glyphs[c]);
            glyph->sprite.init(face->glyph);
            glyph->left = face->glyph->bitmap_left;
            glyph->top = face->glyph->bitmap_top;
            glyph->advance = face->glyph->advance.x / 64.f;
        }
    }

    // Free data
    FT_Done_Face(face);

    return true;
}
bool TextManager::init() {
    // Initialize FreeType
    FT_Library ftlib;
    auto error = FT_Init_FreeType(&ftlib); // Apparently an int
    if (error) {
        printf("Could not initialize FreeType: %s\n", FT_Error_String(error));
        return false;
    }

    if (!initFont(ftlib, FONT_ID_MONOSPACE, "data/fonts/PT Mono_Regular.ttf")) return false;
    if (!initFont(ftlib, FONT_ID_STANDARD, "data/fonts/CommissionerFlair-Medium.ttf")) return false;

    FT_Done_FreeType(ftlib);

    return true;
}
void TextManager::deinit() {}

GLfloat TextManager::getTextLength(FontId fontId, FontsizeId fontsizeId, const char* text) const {
    const Font *font = &(fonts[fontId][fontsizeId]);
    float length = 0;

    // Loop through the whole text
    for (int i = 0; text[i] != '\0'; ++i) {
        length += font->glyphs[(short)text[i]].advance;
    }
    return length;
}
GLfloat TextManager::getTextLength(const char* text) const {
    return getTextLength(activeFontId, activeFontsizeId, text);
}
GLfloat TextManager::getFontHeight(FontId fontId, FontsizeId fontsizeId) const {
    return fonts[fontId][fontsizeId].height;
}
GLfloat TextManager::getFontHeight() const {
    return getFontHeight(activeFontId, activeFontsizeId);
}

void TextManager::setActiveFont(FontId fontId, FontsizeId fontsizeId) {
    // Refuse to set invalid ID values
    if (fontId == FONT_ID_COUNT ||
        fontsizeId == FONTSIZE_ID_COUNT) return;

    activeFontId = fontId;
    activeFontsizeId = fontsizeId;
}

GLfloat TextManager::drawChar(char c) {
    Glyph *glyph = &( fonts[activeFontId][activeFontsizeId].glyphs[(short)c] );
    glyph->sprite.draw();
    return glyph->advance;
}
