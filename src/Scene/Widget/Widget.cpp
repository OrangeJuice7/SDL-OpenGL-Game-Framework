#include "Widget.hpp"

#include "../../ui/UiManager.hpp"

Widget::Widget(
        SDL_Rect rect,
        HorizontalAlignment horzAlign,
        VerticalAlignment vertAlign,
        std::function<void(const Widget&, UiManager&)> drawFunc )

        : Widget(rect, horzAlign, vertAlign, false, nullptr, nullptr, drawFunc) {}

Widget::Widget(
        SDL_Rect rect,
        HorizontalAlignment horzAlign,
        VerticalAlignment vertAlign,
        std::function<void()> funcOnClick,
        std::function<void(const Widget&, UiManager&)> drawFunc )

        : Widget(rect, horzAlign, vertAlign, true, funcOnClick, nullptr, drawFunc) {}

Widget::Widget(
        SDL_Rect rect,
        HorizontalAlignment horzAlign,
        VerticalAlignment vertAlign,
        std::function<void()> funcOnClick,
        std::function<void()> funcOnRelease,
        std::function<void(const Widget&, UiManager&)> drawFunc )

        : Widget(rect, horzAlign, vertAlign, true, funcOnClick, funcOnRelease, drawFunc) {}

Widget::Widget(
		SDL_Rect rect,
		HorizontalAlignment horzAlign,
		VerticalAlignment vertAlign,
		bool clickable,
		std::function<void()> funcOnClick,
		std::function<void()> funcOnRelease,
		std::function<void(const Widget&, UiManager&)> drawFunc ) {

    this->rect = rect;
    this->horzAlign = horzAlign;
    this->vertAlign = vertAlign;
    this->clickable = clickable;
    this->funcOnClick = funcOnClick;
    this->funcOnRelease = funcOnRelease;
    this->drawFunc = drawFunc;

    this->active = false;
}
Widget::~Widget() {
    for (Widget* child : children) {
		delete child;
	}
	children.clear();
}

const SDL_Rect& Widget::getScreenRect() const {
    return screenRect;
}
bool Widget::getActive() const {
	return active;
}
bool Widget::getClickable() const {
    return clickable;
}
void Widget::addChild(Widget* widget) {
    children.push_front(widget);
}

void Widget::calcScreenRect(const SDL_Rect &psRect) {
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

bool withinRect(const SDL_Rect &rect, int x, int y) {
	return (
		x >= rect.x &&
		y >= rect.y &&
		x <= rect.x + rect.w &&
		y <= rect.y + rect.h );
}
Widget* Widget::checkOn(int x, int y) {
	if (!withinRect(screenRect, x, y)) return nullptr;
	// (Future: do further checks in the case where this widget is not rectangular)

	// Check children
	for (Widget* child : children) {
		Widget* childCheck = child->checkOn(x, y);
		if (childCheck != nullptr) return childCheck;
	}

	return getClickable() ? this : nullptr; // ignore non-clickable widgets
}

void Widget::activate() {
	active = true;
}
void Widget::deactivate() {
	active = false;
}
void Widget::click() {
	if (funcOnClick) funcOnClick();
}
void Widget::releaseMouse() {
	if (funcOnRelease) funcOnRelease();
}

void Widget::update(const SDL_Rect &psRect) {
    calcScreenRect(psRect);

	// update all the children
	for (Widget* child : children) {
		child->update(screenRect);
	}
}

void Widget::renderText(UiManager &uiManager, const char *text) const {
    // Implement text wrap later

    uiManager.setFont(FONT_ID_STANDARD, FONTSIZE_ID_NORMAL);
    uiManager.drawText(screenRect.x, screenRect.y, text);
}

void Widget::draw(UiManager &uiManager) const {
	if (getClickable()) {
        if (getActive()) uiManager.setColorMask({.4f, .4f, .0f});
        else             uiManager.setColorMask({.0f, .3f, .4f});
        uiManager.drawSpriteStretched(screenRect.x, screenRect.y, screenRect.w, screenRect.h, SPRITE_ID_WIDGET_BG_DEBUG);
    }

	if (drawFunc) drawFunc(*this, uiManager);

	// call draw for all the children
	for (Widget* child : children) {
		child->draw(uiManager);
	}
}
