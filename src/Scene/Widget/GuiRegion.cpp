#include "GuiRegion.hpp"

GuiRegion::GuiRegion(
        const SDL_Rect& rect,
        HorizontalAlignment horzAlign,
        VerticalAlignment vertAlign) {

    this->screenRect = this->rect = rect;
    this->horzAlign = horzAlign;
    this->vertAlign = vertAlign;
}
GuiRegion::~GuiRegion() {}

const SDL_Rect& GuiRegion::getScreenRect() const {
    return screenRect;
}

void GuiRegion::calcScreenRect(const SDL_Rect &parentScreenRect) {
    const SDL_Rect &psRect = parentScreenRect; // Just an alias

    screenRect = {
		psRect.x,
		psRect.y,
		rect.w,
		rect.h
	};
	switch (horzAlign) {
		case HORZALIGN_LEFT  : screenRect.x += rect.x; break;
		case HORZALIGN_CENTER: screenRect.x += psRect.w/2 + rect.x - rect.w/2; break;
		case HORZALIGN_RIGHT : screenRect.x += psRect.w   - rect.x - rect.w  ; break;
	}
	switch (vertAlign) {
		case VERTALIGN_BOTTOM: screenRect.y += rect.y; break;
		case VERTALIGN_CENTER: screenRect.y += psRect.h/2 + rect.y - rect.h/2; break;
		case VERTALIGN_TOP   : screenRect.y += psRect.h   - rect.y - rect.h  ; break;
	}
}

bool GuiRegion::withinScreenRect(float x, float y) const {
    return (
		x >= screenRect.x &&
		y >= screenRect.y &&
		x <= screenRect.x + screenRect.w &&
		y <= screenRect.y + screenRect.h );
}
