#include "Message.hpp"

#include "MainApp.hpp"

Message::~Message() {}

void QuitMessage::execute(MainApp *mainApp) {
    mainApp->quit();
}
