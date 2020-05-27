#ifndef SCENE_TRANSIT_MESSAGE_HPP
#define SCENE_TRANSIT_MESSAGE_HPP

#include "Message.hpp"
#include "../Scene/Scene.hpp"

class SceneTransitMessage : public Message {
    protected:
        Scene *scene;
    public:
        SceneTransitMessage(Scene *scene);

        void execute(MainApp *mainApp);
};

#endif // SCENE_TRANSIT_MESSAGE_HPP
