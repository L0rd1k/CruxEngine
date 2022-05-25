#pragma once

#include <functional>
#include <iostream>
#include <string>
#include <sstream>

// #include "Flow/Core.h"

#define BIT(x) (1 << x)

namespace Flow {

/** @brief Existing event's types **/
enum class EventTypes {
    Undefined = 0,
    MouseButtonPressed,
    MouseButtonReleased,
    MouseMoved,
    MouseScrolled,
    WindowClose,
    WindowResize,
    WindowFocus,
    WindowMoved,
    WindowLostFocus,
    Apptick,
    AppUpdate,
    AppRender,
    KeyPressed,
    KeyReleased,
};

/** @brief Event's categories sublist **/
enum EventCategory {
    Undefined = 0,
    EventCategoryApplication = BIT(0),
    EventCategoryInput = BIT(1),
    EventCategoryKeyboard = BIT(2),
    EventCategoryMouse = BIT(3),
    EventCategoryMouseButton = BIT(4)
};

#define EVENT_CLASS_TYPE(type) static EventTypes GetStaticType() { return EventTypes::type; } \
    virtual EventTypes GetEventType() const override { return GetStaticType(); } \
    virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) \
    virtual int GetCategoryFlags() const override { return category; }


#define GetClassName(className) std::string classname() { return #className; }

class Event {
    friend class EventDispatcher;

public:
    virtual EventTypes GetEventType() const = 0;
    virtual const char* GetName() const = 0;
    virtual int GetCategoryFlags() const = 0;
    virtual std::string ToString() const {
        return GetName();
    }
    inline bool IsInCategory(EventCategory category) {
        return GetCategoryFlags() & category;
    }

protected:
    bool isHandled = false;
};

class EventDispatcher {
    template <class T>
    using EventFn = std::function<bool(T&)>;

public:
    EventDispatcher(Event& event) : _event(event) {
    }
    template<typename T>
    bool Dispatch(EventFn<T> func) {
        if(_event.GetEventType() == T::GetStaticType()) {
            _event.isHandled = func(*(T*)&_event);
            return  true;
        }
        return false;
    }
private:
    Event& _event;
};

inline std::ostream& operator<<(std::ostream& os, const Event& e) {
    return os << e.ToString(); 
}


}  // namespace Flow  