#ifndef WIDGET_HPP
#define WIDGET_HPP

#include <functional>
#include <forward_list>
#include "GuiRegion.hpp"
class UiManager;

/**
 *  A Widget is fundamentally a specified section of the screen that (optionally) detects mouse clicks.
 *  Can also be used to align text and such.
 */

class Widget : public GuiRegion {
	protected:
		bool clickable;
		// The function that this widget executes on click.
		// Set to nullptr if this widget does nothing when clicked
		std::function<void()> funcOnClick;
		// The function that this widget executes on mouse button release.
		// Set to nullptr if this widget does nothing when clicked
		std::function<void()> funcOnRelease;

		// Whether this widget can be dragged around on mouse hold
		// bool draggable;

		// Whether this Widget is selected (e.g. if the mouse is over it)
		bool active;

		// Child widgets
		// Note: Child widgets should lie fully within the bounds of their parents. Otherwise, they should be separate widgets.
		// Note: Children are only destroyed when the parents are; no way to delete them individually yet
		std::forward_list<Widget*> children;

		// The function that this widget executes on draw
		// If set to nullptr, doesn't draw anything
		std::function<void(const Widget&, UiManager&)> drawFunc;

    public:
        // Full constructor
        Widget(
			SDL_Rect rect,
			HorizontalAlignment horzAlign,
			VerticalAlignment vertAlign,
			bool clickable,
			std::function<void()> funcOnClick,
            std::function<void()> funcOnRelease,
			std::function<void(const Widget&, UiManager&)> drawFunc );

        // Unclickable Widget constructor
        Widget(
			SDL_Rect rect,
			HorizontalAlignment horzAlign,
			VerticalAlignment vertAlign,
			std::function<void(const Widget&, UiManager&)> drawFunc );

        // Click but no release constructor
        Widget(
			SDL_Rect rect,
			HorizontalAlignment horzAlign,
			VerticalAlignment vertAlign,
			std::function<void()> funcOnClick,
			std::function<void(const Widget&, UiManager&)> drawFunc );

        // Click and release constructor
        Widget(
			SDL_Rect rect,
			HorizontalAlignment horzAlign,
			VerticalAlignment vertAlign,
			std::function<void()> funcOnClick,
            std::function<void()> funcOnRelease,
			std::function<void(const Widget&, UiManager&)> drawFunc );

		virtual ~Widget();

        bool getActive() const;
        bool getClickable() const;

		void addChild(Widget* widget);

		/**  Mouse input  **/

		// Returns the widget that (x,y) lies on
		// = this if this widget, = one of the children if they are on top instead, = nullptr if (x,y) is outside of this widget
		// (x,y) is position from the bottom-left corner
        Widget* checkOn(float x, float y); // Can't be const unfortunately, because it returns this

        void activate();
        void deactivate();
        void click();
        void releaseMouse();

		/**  Update  **/
		// psRect: Parent screen rect, also taken from the bottom-left corner
		void update(const SDL_Rect &psRect);

		/**  Draw  **/
		void renderText(UiManager &uiManager, const char *text) const;

        void draw(UiManager &uiManager) const;
};

#endif // WIDGET_HPP
