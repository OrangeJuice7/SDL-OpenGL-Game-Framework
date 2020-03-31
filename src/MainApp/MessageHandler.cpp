#include "MessageHandler.hpp"

#include "MainApp.hpp"
#include "../Message/Message.hpp"

MessageHandler* MessageHandler::instance = new MessageHandler;

MessageHandler::MessageHandler() {}
MessageHandler::~MessageHandler() {
    clearMessages();
}

MessageHandler* MessageHandler::getInstance() {
    /*if (!instance)
        instance = new MessageHandler;*/

    return instance;
}

void MessageHandler::clearMessages() {
    MessageHandler* mh = getInstance();

    for (Message* message : mh->messages) {
        delete message;
    }
    mh->messages.clear();
}

void MessageHandler::postMessage(Message* message) {
    MessageHandler* mh = getInstance();

    mh->messages.push_back(message);
}

void MessageHandler::executeMessages(MainApp* mainApp) {
    MessageHandler* mh = getInstance();

    while (!mh->messages.empty()) {
        Message* message = mh->messages.front();
        mh->messages.pop_front();

        message->execute(mainApp);
        delete message;
    }
}
