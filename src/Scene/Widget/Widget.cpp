#include "Widget.hpp"

#include "../../ui/UiManager.hpp"

Widget::Widget(
        SDL_Rect rect,
        HorizontalAlignment horzAlign,
        VerticalAlignment vertAlign,
        bool visible,
        std::function<void(const Widget&, UiManager&)> drawFunc )

        : Widget(rect, horzAlign, vertAlign, false, visible, nullptr, nullptr, drawFunc) {}

Widget::Widget(
        SDL_Rect rect,
        HorizontalAlignment horzAlign,
        VerticalAlignment vertAlign,
        bool visible,
        std::function<void()> funcOnClick,
        std::function<void(const Widget&, UiManager&)> drawFunc )

        : Widget(rect, horzAlign, vertAlign, true, visible, funcOnClick, nullptr, drawFunc) {}

Widget::Widget(
        SDL_Rect rect,
        HorizontalAlignment horzAlign,
        VerticalAlignment vertAlign,
        bool visible,
        std::function<void()> funcOnClick,
        std::function<void()> funcOnRelease,
        std::function<void(const Widget&, UiManager&)> drawFunc )

        : Widget(rect, horzAlign, vertAlign, true, visible, funcOnClick, funcOnRelease, drawFunc) {}

Widget::Widget(
		SDL_Rect rect,
		HorizontalAlignment horzAlign,
		VerticalAlignment vertAlign,
		bool clickable,
        bool visible,
		std::function<void()> funcOnClick,
		std::function<void()> funcOnRelease,
		std::function<void(const Widget&, UiManager&)> drawFunc )

		: GuiRegion(rect, horzAlign, vertAlign) {

    this->clickable = clickable;
    this->visible = visible;
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

bool Widget::getActive() const {
	return active;
}
bool Widget::getClickable() const {
    return clickable;
}
bool Widget::getVisible() const {
    return visible;
}
void Widget::addChild(Widget* widget) {
    children.push_front(widget);
}

Widget* Widget::checkOn(float x, float y) {
	if (!withinScreenRect(x, y)) return nullptr;
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
void Widget::show() {
    visible = true;
}
void Widget::hide() {
    visible = false;
}

void Widget::update(const SDL_Rect &psRect) {
    if (!visible) return;

    calcScreenRect(psRect);

	// Update all the children
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
    if (!visible) return;

	if (getClickable()) {
        if (getActive()) uiManager.setColorMask({.4f, .4f, .0f});
        else             uiManager.setColorMask({.0f, .3f, .4f});
        uiManager.drawSpriteStretched(screenRect.x, screenRect.y, screenRect.w, screenRect.h, SPRITE_ID_WIDGET_BG_DEBUG);
    }

	if (drawFunc) drawFunc(*this, uiManager);

	// Call draw for all the children
	for (Widget* child : children) {
		child->draw(uiManager);
	}
}
