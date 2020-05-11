#include "InputState.hpp"

MouseState::MouseState() {
    x = y = 0;
    isLDown = isRDown = isMDown = false;
}

KeyboardState::KeyboardState() {}
bool KeyboardState::isKeyDown(SDL_Keycode key) const {
    if (keys.count(key) > 0) return keys.at(key);
    else return false;
}
