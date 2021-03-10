#include "terwinal.h"

namespace terwinal {
    
    class Event;

    std::string Event::getKeySent() { return _keySent; }
    Body* Event::getBodyPtr() { return _body; }
    Event::Event(std::string keySet, Body* bodyptr)
        : _keySent{ keySet }, _body{ bodyptr } {}
    
    
    class ControlHandler;

    std::string ControlHandler::getKey() { return _key; }
    terwinal::event_callback ControlHandler::getCallback() { return _callback; }
    ControlHandler::ControlHandler(std::string key, terwinal::event_callback callback)
        : _key{ key }, _callback{ callback } {}
    void ControlHandler::setKey(std::string key) { _key = key; }
    void ControlHandler::setCallback(terwinal::event_callback callback) { _callback = callback; }

    
    class Body;

    int Body::getWidth() { return _width; }
    std::vector<ControlHandler> Body::getControllers() { return _controllers; }
    void Body::setWidth(int width) { _width = width; }

    void Body::addKeyController(std::string key, terwinal::event_callback callback) {
        _controllers.push_back(ControlHandler(key, callback));
    }
    void Body::render(bool clear) {
        if (clear && std::system("CLS"))
            std::system("clear");
        std::cout << "Error: Body is an abstract object and cannot have an interface." << std::endl;
    }
    void Body::listen() {
        std::string input;
        std::cin >> input;
        std::cin.clear();
        std::cin.ignore(input.length(), '\n');

        bool close;
        std::vector<ControlHandler>::iterator it;
        for (it = _controllers.begin(); it != _controllers.end(); ++it) {
            ControlHandler __handler { (*it) };
            if (input.compare(__handler.getKey()) == 0) {
                close = __handler.getCallback()(Event(__handler.getKey(), this));
            }
        }
        if (! close) {
            listen();
        }
    }

    
    class TextBody;

    

}