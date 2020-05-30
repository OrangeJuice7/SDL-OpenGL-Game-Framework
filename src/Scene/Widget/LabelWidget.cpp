#include "LabelWidget.hpp"

#include <cstring> // for strcpy() and strtok()
#include "../../ui/UiManager.hpp"

LabelWidget::LabelWidget(
        const SDL_Rect& rect,
        HorizontalAlignment horzAlign,
        VerticalAlignment vertAlign)

        : Widget(rect, horzAlign, vertAlign) {

    visible = true;

    rawText = "";
    fontId = FONT_ID_STANDARD;
    fontsizeId = FONTSIZE_ID_NORMAL;
    textHorzAlign = HORZALIGN_LEFT;
    textVertAlign = VERTALIGN_TOP;
    textColor = {1,1,1};
    isTextProcessed = true;
}
LabelWidget::~LabelWidget() {}

void LabelWidget::setText(std::string rawText) {
    this->rawText = rawText;
    isTextProcessed = false;
}
void LabelWidget::setFont(FontId fontId, FontsizeId fontsizeId) {
    this->fontId = fontId;
    this->fontsizeId = fontsizeId;
    isTextProcessed = false;
}
void LabelWidget::setTextAlignment(HorizontalAlignment textHorzAlign, VerticalAlignment textVertAlign) {
    this->textHorzAlign = textHorzAlign;
    this->textVertAlign = textVertAlign;
}
void LabelWidget::setTextColor(const GLcolorRGB& color) {
    textColor = color;
}

void LabelWidget::splitRawTextIntoTextLines(UiManager &uiManager) {
    textLines.clear();

    char *rawTextString = new char[rawText.size()+1]; // +1 for terminating null char
    strcpy(rawTextString, rawText.c_str()); // All this trouble just to prevent strtok() from modifying rawText.c_str() (which is not supposed to be modifiable)

    const float maxLength = rect.w;
    const float spaceLength = uiManager.getCharLength(fontId, fontsizeId, ' ');

    // Split to lines by newline
    std::list<char*> lines;
    {   char *tokenpos = strtok(rawTextString, "\n");
        while (tokenpos != NULL) {
            lines.push_back(tokenpos);
            tokenpos = strtok(NULL, "\n");
        }
    }

    for (char* line : lines) {
        // Split to words by whitespace
        std::list<char*> words;
        {   char *tokenpos = strtok(line, " \t\v\f\r"); // delimiters are the same as <cctype> isspace(), without '\n'
            while (tokenpos != NULL) {
                words.push_back(tokenpos);
                tokenpos = strtok(NULL, " \t\v\f\r");
            }
        }

        // Process the words until we run out of them
        while (!words.empty()) {
            // Start to construct the new textLine to add to the final textLines
            std::string textLine = "";
            float textLineLength = 0; // in pixels

            // Add words to the textLine until we run out of words or bust the maxLength
            while (!words.empty()) {
                char* word = words.front();
                float wordLength = uiManager.getTextLength(fontId, fontsizeId, word);

                if (textLineLength + wordLength <= maxLength) { // Adding the word still fits
                    // Add the word
                    textLine += word;
                    textLineLength += wordLength;
                    words.pop_front();

                    // Account for the space between words (we will pop the trailing space when we finalize the textLine)
                    textLine += ' ';
                    textLineLength += spaceLength;
                } else break; // Adding the word busts the maxLength, bail to finalize the textLine
            }

            if (textLine.size() > 0) { // We do actually have something to print
                // Load up the textLine
                textLine.pop_back(); // Remove the trailing space
                textLines.push_back(textLine);
            } else { // No words to print?
                if (words.empty()) break; // Yes, we ran out of words for this line

                // Otherwise, it means the next word doesn't fit in the maxLength.
                // We will have to fit as much of the word as we can onto this line, then leave the rest for the next line.
                char* word = words.front();
                while (word[0] != '\0') { // Condition shouldn't trigger since we've already confirmed that the word is longer than the maxLength
                    char c = word[0]; // Grab next char of the word
                    float cLength = uiManager.getCharLength(fontId, fontsizeId, c);

                    // Adding c still fits
                    // Or force an empty textLine to accept c anyway so we at least print something
                    // (and not infinite-loop if maxLength happens to be smaller than the width of c)
                    if (textLine.size() <= 0 || textLineLength + cLength <= maxLength) {
                        // Add c
                        textLine += c;
                        textLineLength += cLength;
                        ++word; // Move to point to the next char
                    } else { // Adding c busts the maxLength, bail to finalize the textLine
                        words.front() = word; // But first, behead this long word to help the next iteration
                        break;
                    }
                }

                // Just finalize the line and go
                textLines.push_back(textLine);
            }
        }
    }

    delete[] rawTextString;
    isTextProcessed = true;
}

void LabelWidget::renderTextLines(UiManager &uiManager) const {
    uiManager.setColorMask(textColor);
    uiManager.setFont(fontId, fontsizeId);
    const float fontHeight = uiManager.getFontHeight();

    float y = 0;
	{   float textHeight = textLines.size() * fontHeight;
	    switch (textVertAlign) {
            default:
            case VERTALIGN_TOP   : y = rect.h - fontHeight; break;
            case VERTALIGN_CENTER: y = (rect.h + textHeight)/2.f - fontHeight; break;
            case VERTALIGN_BOTTOM: y = textHeight - fontHeight; break;
        }
	}

    for (std::string str : textLines) {
        float x = 0;
        // Can pre-compute this in splitRawTextIntoTextLines() for optimization, but will have to augment textLines to store the extra data
        float lineLength = uiManager.getTextLength(str.c_str());
        switch (textHorzAlign) {
            default:
            case HORZALIGN_LEFT  : x = 0; break;
            case HORZALIGN_CENTER: x = (rect.w - lineLength)/2.f; break;
            case HORZALIGN_RIGHT : x = rect.w - lineLength; break;
        }

        renderText(uiManager, x, y, str.c_str());

        y -= fontHeight;
    }
}

void LabelWidget::draw(UiManager &uiManager) { // A modified copypasted version of Widget::draw()
    if (!active) return;

    // Debug display (still shows if Widget is invisible)
	if (clickable) {
        if (selected) uiManager.setColorMask({.4f, .4f, .0f});
        else          uiManager.setColorMask({.0f, .3f, .4f});
        drawBgSprite(uiManager, SPRITE_ID_WIDGET_BG_DEBUG);
    }

    if (visible) {
        drawFunc(*this, uiManager);

        // Draw text
        if (!isTextProcessed) splitRawTextIntoTextLines(uiManager);
        renderTextLines(uiManager);
    }

	// Call draw for all the children
	for (Widget* child : children) {
		child->draw(uiManager);
	}
}
