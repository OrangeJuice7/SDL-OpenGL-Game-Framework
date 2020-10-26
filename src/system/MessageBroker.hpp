#ifndef MESSAGE_BROKER_HPP
#define MESSAGE_BROKER_HPP

/** Usage:
 *	- #include Message.hpp.
 *	- Use subscribe<MsgType>(callbackId, callback) and publish<MsgType>(msg) directly.
 *  - e.g.  subscribe<QuitMessage>("closeApp", [&](const QuitMessage& msg) {
                quitFlag = true;
            });
 *  - e.g.  publish<QuitMessage>({});
 */

#include <string>
#include <functional>
#include <map>

typedef std::string CallbackId;

template <class MsgType>
using CallbackFunc = std::function<void(const MsgType&)>;

template <class MsgType>
class MessageBroker {
    public:
        // Tell the MessageBroker to call the callback function whenever a message (of this type) is published
        // Will overwrite an existing callback with the same ID if one exists
        static void subscribe(CallbackId callbackId, CallbackFunc<MsgType> callback) {
            callbacks[callbackId] = callback;
        }

        // Tell the MessageBroker to stop calling the specified callback
        static void unsubscribe(CallbackId callbackId) {
            callbacks.erase(callbackId);
        }

        static void publish(const MsgType& msg) {
            for (auto& callback : callbacks) {
                callback.second(msg);
            }
        }

    protected:
        static std::map<CallbackId, CallbackFunc<MsgType>> callbacks;
};

template <class MsgType>
std::map<CallbackId, CallbackFunc<MsgType>> MessageBroker<MsgType>::callbacks;



/***  Convenience functions  ***/

template <class MsgType>
void subscribe(CallbackId callbackId, CallbackFunc<MsgType> callback) {
    MessageBroker<MsgType>::subscribe(callbackId, callback);
}
template <class MsgType>
void unsubscribe(CallbackId callbackId) {
    MessageBroker<MsgType>::unsubscribe(callbackId);
}

template <class MsgType>
void publish(const MsgType& msg) {
    MessageBroker<MsgType>::publish(msg);
}

#endif // MESSAGE_BROKER_HPP
