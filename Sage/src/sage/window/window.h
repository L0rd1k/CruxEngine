#pragma once


#include <functional>
#include <string>
#include <iostream>

#include "../events/event.h"
#include "../utils/logger/log.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace sage {

struct WindowConf {
    WindowConf(const std::string& title = "SageEngine",
               unsigned int w = 1280,
               unsigned int h = 720)
        : headerTitle(title), width(w), height(h) {
    }
    std::string headerTitle;
    unsigned int width;
    unsigned int height;
};

class Window {
public:
    using EventCallbackFunction = std::function<void(Event&)>;
    virtual ~Window() {}
    virtual void onUpdate() = 0;
    virtual unsigned int getWidth() const = 0;
    virtual unsigned int getHeight() const = 0;

    virtual void setEventCallback(const EventCallbackFunction& callback) = 0;
    virtual void setVSync(bool enabled) = 0;
    virtual bool isVSunc() const = 0;

    virtual void* getOriginalWindow() const = 0;

    static Window* create(const WindowConf& conf = WindowConf());
};

}  // namespace sage