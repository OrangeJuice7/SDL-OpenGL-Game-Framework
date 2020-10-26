#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include "MessageBroker.hpp"
class Scene;

struct QuitMessage {};
struct SceneTransitMessage {
    Scene *scene;
};

#endif // MESSAGE_HPP
