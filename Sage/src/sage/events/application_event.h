#pragma once

#include "event.h"

namespace Sage {

class WindowResizeEvent : public Event {
public:
    WindowResizeEvent(unsigned int width, unsigned int height) :
        _winHeight(height), _winWidth(width) {
    }
    inline unsigned int GetWidth() const { return _winWidth; }
    inline unsigned int GetHeight() const { return _winHeight; }
    std::string ToString() const override {
        std::stringstream ss;
        ss << GetName() << " " << _winWidth << "x" << _winHeight;
        return ss.str();
    }
    EVENT_CLASS_TYPE(WindowResize);
    EVENT_CLASS_CATEGORY(EventCategoryApplication);
private:
    unsigned int _winHeight, _winWidth;
};

class WindowCloseEvent : public Event {
public:
    WindowCloseEvent() {}
    EVENT_CLASS_TYPE(WindowClose)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class ApptickEvent : public Event {
public:
    ApptickEvent() {}
    EVENT_CLASS_TYPE(Apptick)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class AppUpdateEvent : public Event {
public:
    AppUpdateEvent() {}
    EVENT_CLASS_TYPE(AppUpdate)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class AppRenderEvent : public Event {
public:
    AppRenderEvent() {}
    EVENT_CLASS_TYPE(AppRender)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

}