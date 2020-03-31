#include "Message.hpp"

#include "../MainApp/MainApp.hpp"

Message::~Message() {}

void QuitMessage::execute(MainApp *mainApp) {
    mainApp->quit();
}
