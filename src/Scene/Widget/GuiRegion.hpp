#ifndef GUIREGION_HPP
#define GUIREGION_HPP

#include <SDL2/SDL.h> // for SDL_Rect

class GuiRegion {
    public:
		// Alignment: what does the (x,y) position actually refer to
		// e.g. top-left alignment means (x,y) is the position of the top-left corner of the widget from the top-left corner of the screen
		// (For Center alignment, +x/+y is right/up, to be consistent with OpenGL's coordinate system.)
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

        GuiRegion(
            const SDL_Rect& rect,
			HorizontalAlignment horzAlign,
			VerticalAlignment vertAlign);
        virtual ~GuiRegion();

        const SDL_Rect& getScreenRect() const;

        void calcScreenRect(const SDL_Rect &parentScreenRect);
        bool withinScreenRect(float x, float y) const;

    protected:
		SDL_Rect rect; // Rect as using the alignment system
		HorizontalAlignment horzAlign;
		VerticalAlignment vertAlign;

		SDL_Rect screenRect; // (cached) Rect in actual screen coords (with bottom-left alignment)
};

#endif // GUIREGION_HPP
