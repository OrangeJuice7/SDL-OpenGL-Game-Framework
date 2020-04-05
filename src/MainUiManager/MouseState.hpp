#ifndef MOUSE_STATE_HPP
#define MOUSE_STATE_HPP

struct MouseState {
    int x, y;
    bool isLDown,
         isRDown,
         isMDown;

    MouseState();
};

#endif // MOUSE_STATE_HPP
