#ifndef WIDGET_HPP
#define WIDGET_HPP

#include <functional>
#include <SDL.h> // for SDL_Rect
class MainUiManager;

/**
 *  A Widget is fundamentally a specified section of the screen that (optionally) detects mouse clicks.
 *  Can also be used to align text and such.
 */

class Widget {
    public:
		// Alignment: what does the (x,y) position actually refer to
		// e.g. top-left alignment means (x,y) is the position of the top-left corner of the widget from the top-left corner of the screen
		enum HorizontalAlignment {
			HORZALIGN_LEFT,
			HORZALIGN_CENTER,
			HORZALIGN_RIGHT
		};

		enum VerticalAlignment {
			VERTALIGN_TOP,
			VERTALIGN_CENTER,
			VERTALIGN_BOTTOM
		};

	protected:
        // x, y, w, h
		SDL_Rect rect; // Rect as using the alignment system
		SDL_Rect screenRect; // (cached) Rect in actual screen coords (with topleft alignment)

		HorizontalAlignment horzAlign;
		VerticalAlignment vertAlign;

		// The function that this widget executes on click.
		// Set to nullptr if this widget does nothing when clicked
		std::function<void()> funcOnClick;
		bool clickable;

		// Whether this widget can be dragged around on mouse hold
		// bool draggable;

		// Whether this Widget is selected (e.g. if the mouse is over it)
		bool active;

		// Child widgets
		// std::deque<Widget> children; // How to populate this list?

		// The function that this widget executes on draw
		// If set to nullptr, doesn't draw anything
		std::function<void(const Widget*, MainUiManager*)> drawFunc;

		// psRect: Parent screen rect, (i.e. also actual screen coords with topleft alignment)
		void calcScreenRect(const SDL_Rect &psRect);

    public:
        Widget(
			SDL_Rect rect,
			HorizontalAlignment horzAlign,
			VerticalAlignment vertAlign,
			bool clickable,
			std::function<void()> funcOnClick,
			std::function<void(const Widget*, MainUiManager*)> drawFunc );

		virtual ~Widget();

		bool getActive() const;
		bool getClickable() const;

		/**  Mouse input  **/

		// Returns the widget that (x,y) lies on
		// = this if this widget, = one of the children if they are on top instead, = nullptr if (x,y) is outside of this widget
		// (x,y) is position from the top-left corner
        Widget* checkOn(int x, int y); // Can't be const unfortunately, because it returns this

        void activate();
        void deactivate();
        void click();

		/**  Update  **/
		void update(const SDL_Rect &psRect);

		/**  Draw  **/
		void renderText(MainUiManager *uiManager, const char *text, SDL_Color color) const;

		// psRect: Parent screen rect, also taken from the top-left corner
        void draw(MainUiManager *uiManager) const;
};

#endif // WIDGET_HPP
