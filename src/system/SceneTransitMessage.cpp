#include "SceneTransitMessage.hpp"

#include "MainApp.hpp"

SceneTransitMessage::SceneTransitMessage(Scene *scene) {
    this->scene = scene;
}
void SceneTransitMessage::execute(MainApp *mainApp) {
    mainApp->transitScene(scene);
}
