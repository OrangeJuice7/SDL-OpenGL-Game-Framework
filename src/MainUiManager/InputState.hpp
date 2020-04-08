#ifndef INPUT_STATE_HPP
#define INPUT_STATE_HPP

#include <SDL.h>
#include <unordered_map>

struct MouseState {
    int x, y;
    bool isLDown,
         isRDown,
         isMDown;

    MouseState();
};

struct KeyboardState {
    std::unordered_map<SDL_Keycode, bool> keys;

    KeyboardState();

    bool isKeyDown(SDL_Keycode key) const;
};

#endif // INPUT_STATE_HPP
