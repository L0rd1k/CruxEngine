#pragma once

#include "Event.h"

namespace Flow {

class MouseMovedEvent : public Event {
public:
    MouseMovedEvent(float x, float y) : _msX(x), _msY(y) {
    }
    inline float GetX() const {return _msX; }
    inline float GetY() const {return _msY; }

    std::string ToString() const override {
        std::stringstream ss;
        ss << GetName() << " " << _msX << " x " << _msY;
        return ss.str();
    }
    EVENT_CLASS_TYPE(MouseMoved)
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);
private:
    float _msX, _msY;
};

class MouseScrolledEvent : public Event {
public:
    MouseScrolledEvent(float xOffset, float yOffset) : _msXOffset(xOffset), _msYOffset(yOffset) {
    }
    inline float GetXOffset() const {return _msXOffset; }
    inline float GetYOffset() const {return _msYOffset; }

    std::string ToString() const override {
        std::stringstream ss;
        ss << GetName() << " " << _msXOffset << " x " << _msYOffset;
        return ss.str();
    }
    EVENT_CLASS_TYPE(MouseScrolled)
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);
private:
    float _msXOffset, _msYOffset;
};


class MouseButtonEvent : public Event {
public:
    inline float GetMouseButton() const {return _msBtn; }
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);
protected:
    MouseButtonEvent(int msBtn) : _msBtn(msBtn) {
    }
    int _msBtn;
};

class MouseButtonPressedEvent : public MouseButtonEvent {
public:
    MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {
    }
    std::string ToString() const override {
        std::stringstream ss;
        ss << GetName() << " " << _msBtn;
        return ss.str();
    }
    EVENT_CLASS_TYPE(MouseButtonPressed)
};

class MouseButtonReleasedEvent : public MouseButtonEvent {
public:
    MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {
    }
    std::string ToString() const override {
        std::stringstream ss;
        ss << GetName() << " " << _msBtn;
        return ss.str();
    }
    EVENT_CLASS_TYPE(MouseButtonReleased)
};


}  // namespace Flow