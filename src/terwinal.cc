#include "terwinal.h"

#include <codecvt>
#include <string>
#include <locale>

typedef std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> u8_to_u32;
typedef std::wstring_convert<std::codecvt_utf8_utf16<char32_t>, char32_t> u32_to_u8;

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

    std::u32string to_u32(std::string str) {
        std::u32string u32_str;
        u8_to_u32 convert; // WHY IS THIS SO LONG
        return convert.from_bytes(str);
    }

    std::string to_u8(std::u32string u32_str) {
        u32_to_u8 convert;
        return convert.to_bytes(u32_str);
    }

    void TextBody::render(bool clear) {
        if (clear && std::system("CLS"))
            std::system("clear");

        std::string line;
        while (std::getline(content, line)) {
            std::u32string __u32_line { to_u32(line) }; // todo do styling stuff with this (text wrapping, whatever)
            std::cout << to_u8(__u32_line) << std::endl;
        }
    }

}