#ifndef TERMINAL_H
#define TERMINAL_H

#include <functional>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>

namespace terwinal {
    struct Style;

    class Event;
    class ControlHandler;

    class Body;
    class TextBody;
    class Window;

    class Element;
    class TextElement;
    class LineElement;

    typedef std::function<bool(Event)> event_callback;

    class Event {
        private:
            std::string _keySent;
            Body* _body;
        public:
            std::string getKeySent();
            Body* getBodyPtr();
            Event(std::string keySent, Body* bodyptr);
    };

    class ControlHandler {
        private:
            std::string _key;
            event_callback _callback;
        public:
            std::string getKey();
            event_callback getCallback();
            ControlHandler();
            ControlHandler(std::string key, event_callback callback);
            void setKey(std::string key);
            void setCallback(event_callback callback);
    };

    class Body {
        private:
            int _width;
            std::vector<ControlHandler> _controllers;
        public:
            int getWidth();
            std::vector<ControlHandler> getControllers();
            void setWidth(int width);

            void addKeyController(std::string key, event_callback callback);
            virtual void render(bool clear);
            void listen();
    };

    class TextBody : public Body {
        public:
            std::stringstream content;
            void render(bool clear) override;
    };

}

#endif
