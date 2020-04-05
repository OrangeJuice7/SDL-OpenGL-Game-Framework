#ifndef MESSAGE_HANDLER_HPP_INCLUDED
#define MESSAGE_HANDLER_HPP_INCLUDED

#include <list>
class Message;
class MainApp;

class MessageHandler {
    private:
        // Singleton. Memory should be freed when the app closes
        static MessageHandler* instance;

        std::list<Message*> messages;

        MessageHandler();
        ~MessageHandler();

    public:
        static MessageHandler* getInstance();

        static void clearMessages();

        // Adds a message to the queue
        static void postMessage(Message* message);

        // Executes the messages on mainApp
        static void executeMessages(MainApp* mainApp);
};

#endif // MESSAGE_HANDLER_HPP_INCLUDED
