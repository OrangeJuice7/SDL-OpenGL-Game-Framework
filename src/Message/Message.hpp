#ifndef MESSAGE_HPP
#define MESSAGE_HPP

class MainApp;

class Message {
    public:
        virtual ~Message();
        virtual void execute(MainApp *mainApp)=0;
};

class QuitMessage : public Message {
    public:
        void execute(MainApp *mainApp);
};

#endif // MESSAGE_HPP
