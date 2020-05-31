#ifndef WIDGET_HPP
#define WIDGET_HPP

#include <functional>
#include <forward_list>
#include "../../ui/SpriteId.hpp"
#include "GuiRegion.hpp"
class UiManager;

class Widget;
typedef std::function<void()> WidgetClickFunc;
typedef std::function<void(Widget*, const UiManager&)> WidgetUpdateFunc; // Pointer to let this function typecast to Widget dervatives and thus access their methods
typedef std::function<void(const Widget&, UiManager&)> WidgetDrawFunc;

const WidgetClickFunc EMPTY_WIDGET_CLICK_FUNC = [](){};
const WidgetUpdateFunc EMPTY_WIDGET_UPDATE_FUNC = [](Widget*, const UiManager&){};
const WidgetDrawFunc EMPTY_WIDGET_DRAW_FUNC = [](const Widget&, UiManager&){};

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
		WidgetClickFunc funcOnClick;
		// The function that this widget executes on mouse button release.
		WidgetClickFunc funcOnRelease;

		// Whether this widget can be dragged around on mouse hold
		// bool draggable;

		// Whether this Widget is drawn
		bool visible;
		// The function that this widget executes on draw
		WidgetDrawFunc drawFunc;

		WidgetUpdateFunc updateFunc;

		// Whether this Widget is selected (e.g. if the mouse is over it) (just to help cosmetic purposes)
		bool selected;

		// Child widgets
		// Note: Child widgets should lie fully within the bounds of their parents. Otherwise, they should be separate widgets.
		// Note: Children are only destroyed when the parents are; no way to delete them individually yet
		std::forward_list<Widget*> children;

    public:
        Widget(
			const SDL_Rect& rect,
			HorizontalAlignment horzAlign,
			VerticalAlignment vertAlign);
		virtual ~Widget();

        bool getActive() const;
        bool getClickable() const;
        bool getVisible() const;
        bool getSelected() const;

		void setClickFunction(WidgetClickFunc funcOnClick); // Setting the click function also enables clicking
		void setClickFunction(WidgetClickFunc funcOnClick, WidgetClickFunc funcOnRelease);
		void setDrawFunction(WidgetDrawFunc drawFunc); // Also enables drawing
		void setUpdateFunction(WidgetUpdateFunc updateFunc);
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
		// Mainly updating cached data
		// psRect: Parent screen rect, also taken from the bottom-left corner
		virtual void update(const SDL_Rect &psRect, const UiManager &uiManager);

		/**  Draw  **/
		// Maybe augment this with a border thickness parameter (for sprites slightly larger than the Widget) in the future
		void drawBgSprite(UiManager &uiManager, SpriteId spriteId) const;

		// Renders a single unbroken/unwrapped line of text
		// (x,y) denotes the offset from the lower left corner of the widget
		void renderText(UiManager &uiManager, float x, float y, const char *text) const;

        virtual void draw(UiManager &uiManager) const;
};

#endif // WIDGET_HPP
