#include "Widget.hpp"

#include "../../ui/UiManager.hpp"

Widget::Widget(
		const SDL_Rect& rect,
		HorizontalAlignment horzAlign,
		VerticalAlignment vertAlign)

		: GuiRegion(rect, horzAlign, vertAlign) {

    active = true;

    clickable = false;
    funcOnClick = funcOnRelease = EMPTY_WIDGET_CLICK_FUNC;
    selected = false;

    updateFunc = EMPTY_WIDGET_UPDATE_FUNC;

    visible = false;
    drawFunc = EMPTY_WIDGET_DRAW_FUNC;
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
bool Widget::getSelected() const {
    return selected;
}

void Widget::setClickFunction(WidgetClickFunc funcOnClick) {
    setClickFunction(funcOnClick, [](){});
}
void Widget::setClickFunction(WidgetClickFunc funcOnClick, WidgetClickFunc funcOnRelease) {
    this->funcOnClick = funcOnClick;
    this->funcOnRelease = funcOnRelease;
    enableClick();
}
void Widget::setDrawFunction(WidgetDrawFunc drawFunc) {
    this->drawFunc = drawFunc;
    enableDraw();
}
void Widget::setUpdateFunction(WidgetUpdateFunc updateFunc) {
    this->updateFunc = updateFunc;
}
void Widget::addChild(Widget* widget) {
    children.push_front(widget);
}

void Widget::activate() {
	active = true;
}
void Widget::deactivate() {
	active = false;
}
void Widget::enableClick() {
    clickable = true;
}
void Widget::disableClick() {
    clickable = false;
}
void Widget::enableDraw() {
    visible = true;
}
void Widget::disableDraw() {
    visible = false;
}
void Widget::select() {
    selected = true;
}
void Widget::deselect() {
    selected = false;
}

Widget* Widget::checkOn(float x, float y) {
    if (!active) return nullptr;

	if (!withinScreenRect(x, y)) return nullptr;
	// (Future: do further checks in the case where this widget is not rectangular)

	// Check children
	for (Widget* child : children) {
		Widget* childCheck = child->checkOn(x, y);
		if (childCheck != nullptr) return childCheck;
	}

	return clickable ? this : nullptr; // ignore non-clickable widgets
}

void Widget::click() {
	funcOnClick();
}
void Widget::releaseMouse() {
	funcOnRelease();
}

void Widget::update(const SDL_Rect &psRect, const UiManager &uiManager) {
    if (!active) return;

    updateFunc(this, uiManager);

    calcScreenRect(psRect);

	// Update all the children
	for (Widget* child : children) {
		child->update(screenRect, uiManager);
	}
}

void Widget::drawBgSprite(UiManager &uiManager, SpriteId spriteId) const {
    uiManager.drawSpriteStretched(screenRect.x, screenRect.y, screenRect.w, screenRect.h, spriteId);
}
void Widget::renderText(UiManager &uiManager, float x, float y, const char *text) const {
    uiManager.drawText(screenRect.x + x, screenRect.y + y, text);
}

void Widget::draw(UiManager &uiManager) const {
    if (!active) return;

    // Debug display (still shows if Widget is invisible)
	if (clickable) {
        if (selected) uiManager.setColorMask({.4f, .4f, .0f});
        else          uiManager.setColorMask({.0f, .3f, .4f});
        drawBgSprite(uiManager, SPRITE_ID_WIDGET_BG_DEBUG);
    }

	if (visible) drawFunc(*this, uiManager);

	// Call draw for all the children
	for (Widget* child : children) {
		child->draw(uiManager);
	}
}
