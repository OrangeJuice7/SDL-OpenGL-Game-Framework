#ifndef WIDGET_HPP
#define WIDGET_HPP

#include <functional>
#include <forward_list>
#include "../../ui/SpriteId.hpp"
#include "GuiRegion.hpp"
class UiManager;

/**
 *  A Widget is fundamentally a specified section of the screen that (optionally) detects mouse clicks.
 *  Can also be used to align text and such.
 */

class Widget : public GuiRegion {
	protected:
		// If a Widget is inactive, then it's neither drawn nor clickable, nor are any of its children active
		bool active;

		bool clickable;
		// The function that this widget executes on click.
		std::function<void()> funcOnClick;
		// The function that this widget executes on mouse button release.
		std::function<void()> funcOnRelease;

		// Whether this widget can be dragged around on mouse hold
		// bool draggable;

		// Whether this Widget is drawn
		bool visible;
		// The function that this widget executes on draw
		std::function<void(const Widget&, UiManager&)> drawFunc;

		// Whether this Widget is selected (e.g. if the mouse is over it) (just to help cosmetic purposes)
		bool selected;

		// Child widgets
		// Note: Child widgets should lie fully within the bounds of their parents. Otherwise, they should be separate widgets.
		// Note: Children are only destroyed when the parents are; no way to delete them individually yet
		std::forward_list<Widget*> children;

    public:
        Widget(
			SDL_Rect rect,
			HorizontalAlignment horzAlign,
			VerticalAlignment vertAlign);
		virtual ~Widget();

        bool getActive() const;
        bool getClickable() const;
        bool getVisible() const;
        bool getSelected() const;

		void setClickFunction(std::function<void()> funcOnClick); // Setting the click function also enables clicking
		void setClickFunction(std::function<void()> funcOnClick, std::function<void()> funcOnRelease);
		void setDrawFunction(std::function<void(const Widget&, UiManager&)> drawFunc); // Also enables drawing
		void addChild(Widget* widget);

        void activate();
        void deactivate();
		void enableClick();
		void disableClick();
		void enableDraw();
		void disableDraw();
        void select();
        void deselect();

		/**  Mouse input  **/

		// Returns the widget that (x,y) lies on
		// = this if this widget, = one of the children if they are on top instead, = nullptr if (x,y) is outside of this widget
		// (x,y) is position from the bottom-left corner
        Widget* checkOn(float x, float y); // Can't be const unfortunately, because it returns this

        void click();
        void releaseMouse();

		/**  Update  **/
		// psRect: Parent screen rect, also taken from the bottom-left corner
		void update(const SDL_Rect &psRect);

		/**  Draw  **/
		void drawBgSprite(UiManager &uiManager, SpriteId spriteId) const; // Maybe augment this with a border thickness parameter (for sprites slightly larger than the Widget) in the future
		void renderText(UiManager &uiManager, const char *text) const;

        void draw(UiManager &uiManager) const;
};

#endif // WIDGET_HPP
