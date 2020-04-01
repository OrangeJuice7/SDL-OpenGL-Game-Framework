#include "Widget.hpp"

#include "../../MainUiManager/MainUiManager.hpp"

Widget::Widget(
		SDL_Rect rect,
		HorizontalAlignment horzAlign,
		VerticalAlignment vertAlign,
		std::function<void()> funcOnClick,
		std::function<void(const Widget*, MainUiManager*)> drawFunc ) {

    this->rect = rect;
    this->horzAlign = horzAlign;
    this->vertAlign = vertAlign;
    this->funcOnClick = funcOnClick;
    this->drawFunc = drawFunc;
    this->active = false;
}
Widget::~Widget() {
    //clear children
}

bool Widget::getActive() const {
	return active;
}
bool Widget::getClickable() const {
    return (drawFunc != nullptr);
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
		case HORZALIGN_CENTER: screenRect.x += psRect.w/2 - rect.x - rect.w/2; break;
		case HORZALIGN_RIGHT : screenRect.x += psRect.w   - rect.x - rect.w  ; break;
	}
	switch (vertAlign) {
		case VERTALIGN_TOP   : screenRect.y += rect.y; break;
		case VERTALIGN_CENTER: screenRect.y += psRect.h/2 - rect.y - rect.h/2; break;
		case VERTALIGN_BOTTOM: screenRect.y += psRect.h   - rect.y - rect.h  ; break;
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
	/*for (Widget child : children) {
		Widget* childCheck = child.checkOn(screenRect, x, y);
		if (childCheck != nullptr) return childCheck;
	}*/

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

void Widget::update(const SDL_Rect &psRect) {
    calcScreenRect(psRect);

	// update all the children
	/*for (Widget child : children) {
		child.update(screenRect);
	}*/
}

void Widget::renderText(MainUiManager *uiManager, const char *text, SDL_Color color) const {
    // Implement text wrap later

    uiManager->renderTextToScreen(text, color, screenRect.x, screenRect.y);
}

void Widget::draw(MainUiManager *uiManager) const {
	if (drawFunc) drawFunc(this, uiManager);

	// call draw for all the children
	/*for (Widget child : children) {
		child.draw(uiManager);
	}*/
}
