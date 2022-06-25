#pragma once

#include "event.h"

namespace sage {

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

class KeyTypedEvent : public KeyEvent {
public:
    KeyTypedEvent(int keyCode) : KeyEvent(keyCode) {
    }
    std::string ToString() const override {
        std::stringstream ss;
        ss << GetName() << " " << _keyCode;
        return ss.str();
    }
    EVENT_CLASS_TYPE(KeyTyped)

private:
    int _repeatCount;
};


}  // namespace sage