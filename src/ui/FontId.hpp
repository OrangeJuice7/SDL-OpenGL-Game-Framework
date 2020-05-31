#ifndef FONT_ID_HPP
#define FONT_ID_HPP

// You may re-order and add new enum values,
// but do NOT assign artificial values to any of these enums!
// When defining new fonts/sizes, update TextManager::init() as well.

enum FontId {
    FONT_ID_MONOSPACE,
    FONT_ID_STANDARD,
    //FONT_ID_FANCY,

    FONT_ID_COUNT
};

enum FontsizeId { // size = height
    FONTSIZE_ID_HEADING,
    FONTSIZE_ID_SUBHEADING,
    FONTSIZE_ID_NORMAL,
    FONTSIZE_ID_SMALL,

    FONTSIZE_ID_COUNT
};

#endif // FONT_ID_HPP
