#pragma once

#include "Event.h"

namespace Flow {

class KeyEvent : public Event {
public:
    inline int GetKeyCode() const {
        return _keyCode;
    }
    EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput);

protected:
    KeyEvent(int keyCode) : _keyCode(keyCode) {}
    int _keyCode;
};

class KeyPressedEvent : public KeyEvent {
public:
    KeyPressedEvent(int keyCode, int repeatCount) : KeyEvent(keyCode), _repeatCount(repeatCount) {
    }
    inline int GetRepeatCount() const {
        return _repeatCount;
    }
    std::string ToString() const override {
        std::stringstream ss;
        ss << GetName() << " " << _keyCode << " (" << _repeatCount << " ) repeats";
        return ss.str();
    }
    EVENT_CLASS_TYPE(KeyPressed)

private:
    int _repeatCount;
};


class KeyReleasedEvent : public KeyEvent {
public:
    KeyReleasedEvent(int keyCode) : KeyEvent(keyCode) {
    }
    std::string ToString() const override {
        std::stringstream ss;
        ss << GetName() << " " << _keyCode;
        return ss.str();
    }
    EVENT_CLASS_TYPE(KeyReleased)
};

}  // namespace Flow