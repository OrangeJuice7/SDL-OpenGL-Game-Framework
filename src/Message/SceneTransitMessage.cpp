#include "SceneTransitMessage.hpp"

#include "../MainApp/MainApp.hpp"

SceneTransitMessage::SceneTransitMessage(Scene *scene) {
    this->scene = scene;
}
void SceneTransitMessage::execute(MainApp *mainApp) {
    mainApp->transitScene(scene);
}
