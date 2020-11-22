#ifndef LABEL_WIDGET_HPP
#define LABEL_WIDGET_HPP

#include <string>
#include <list>
#include "Widget.hpp"
#include "../../ui/FontId.hpp"
#include "../../ui/GLUtil.hpp"

/** A class specifically to render properly aligned and wrapped text.
 *  The text is rendered on top of the regular draw function.
 */
class LabelWidget : public Widget {
    public:
        LabelWidget(
            const SDL_Rect& rect,
			HorizontalAlignment horzAlign,
			VerticalAlignment vertAlign);
        virtual ~LabelWidget();

        void setText(std::string rawText);
        void setFont(FontId fontId, FontsizeId fontsizeId);
        void setTextAlignment(HorizontalAlignment textHorzAlign, VerticalAlignment textVertAlign);
        void setTextColor(const GLcolorRGB& color);

        void update(const SDL_Rect &psRect, const UiManager &uiManager);

        void draw(UiManager &uiManager) const;

    protected:
        std::string rawText;
        std::list<std::string> textLines; // cached list of lines to print, updated on draw()
        bool isTextProcessed;

        FontId fontId;
        FontsizeId fontsizeId;
        HorizontalAlignment textHorzAlign;
        VerticalAlignment textVertAlign;
        GLcolorRGB textColor; // Some time in the future: rich text will let this colour change dynamically...?

        void splitRawTextIntoTextLines(const UiManager &uiManager);
        void renderTextLines(UiManager &uiManager) const;
};

#endif // LABEL_WIDGET_HPP
