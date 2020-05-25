#ifndef TEXT_MANAGER_HPP
#define TEXT_MANAGER_HPP

#include <ft2build.h>
#include FT_FREETYPE_H

#include "Texture.hpp"
#include "Sprite.hpp"

// You may re-order and add new enum values,
// but do NOT assign artificial values to any of these enums!
enum FontsizeId { // size = height
    FONTSIZE_ID_HEADING,
    FONTSIZE_ID_SUBHEADING,
    FONTSIZE_ID_NORMAL,
    FONTSIZE_ID_SMALL,

    FONTSIZE_ID_COUNT
};

class GlyphTexture : public Texture {
    public:
        GlyphTexture();
        ~GlyphTexture();

        bool init(const FT_GlyphSlot &glyph);
};
class GlyphSprite : public Sprite {
    protected:
        GLuint vao;
        GLuint vbo;
        GLuint tvbo;

        GlyphTexture texture; // Should convert this sometime to handle a texture atlas

    public:
        GlyphSprite();
        ~GlyphSprite();

        bool init(const FT_GlyphSlot &glyph);
        void deinit();

        GLuint getVAO();

        void draw();
};
struct Glyph { // Rasterized glyph
    GlyphSprite sprite;
    // Width and height data already captured in texture
    GLuint left; // distance between left of glyph and x=0
    GLuint top; // distance between top of glyph and y=0
    GLfloat advance; // x-distance between the origin points of this glyph and the next
};

#define TEXT_NUM_OF_SUPPORTED_CHARS 128 // first 128 ASCII chars
struct Font { // Rasterized, i.e. already has a fixed size
    // Note: for a greater alphabet in the future, this can be changed to std::map, the access will still have the same syntax
    Glyph glyphs[TEXT_NUM_OF_SUPPORTED_CHARS];
    GLfloat height; // Distance between one baseline and the next
};
enum FontId {
    FONT_ID_MONOSPACE,
    FONT_ID_STANDARD,
    //FONT_ID_FANCY,

    FONT_ID_COUNT
};



class TextManager {
    protected:
        Font fonts[FONT_ID_COUNT][FONTSIZE_ID_COUNT];
        FT_UInt fontsizes[FONTSIZE_ID_COUNT]; // Might possibly become different value sets for different fonts

        FontId activeFontId;
        FontsizeId activeFontsizeId;

        bool initFont(FT_Library ftlib, FontId fontId, const char *filepath);

    public:
        TextManager();
        ~TextManager();

        bool init();
        void deinit();

        // Getters of useful params
        // Versions with missing ID params means the function will return the value for the current active font
        GLfloat getTextLength(FontId fontId, FontsizeId fontsizeId, const char* text) const;
        GLfloat getTextLength(const char* text) const;
        GLfloat getFontHeight(FontId fontId, FontsizeId fontsizeId) const;
        GLfloat getFontHeight() const;

        void setActiveFont(FontId fontId, FontsizeId fontsizeId);
        // Later: load font texture atlas into GPU

        // Truncate the given text to be within the given maxWidth
        // (Rewrite: Should return an array of strings, which is the given string split into several substrings all within the given maxWidth, to be drawn consecutively)
        //const char* getTruncatedText(FontId fontId, const char* text, GLuint maxWidth);

        // Returns the amount to advance (in the +x direction) to the next position to print the next char
        GLfloat drawChar(char c);
        // Higher UiManager responsible for positioning each char, setting colour etc. (since the uniforms (particularly translations) are handled over there)
};

#endif // TEXT_MANAGER_HPP
