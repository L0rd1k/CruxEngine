#pragma once

#include <memory>

#include "src/crux/core.h"

#include "src/crux/window/window.h"
#include "src/crux/events/key_event.h"
#include "src/crux/events/mouse_event.h"
#include "src/crux/events/application_event.h"

#include "src/crux/render/opengl/opengl_renderer_context.h"

namespace crux {

class LinuxWindow : public Window {
public:
    LinuxWindow(const WindowConf& conf);
    virtual ~LinuxWindow();

    void onUpdate() override;

    inline unsigned int getWidth() const override {
        return _data.width;
    };
    inline unsigned int getHeight() const override {
        return _data.height;
    };
    inline void setEventCallback(const EventCallbackFunction& callback) override {
        _data.eventCallback = callback;
    };
    void setVSync(bool enabled);
    bool isVSunc() const;

    inline virtual void* getOriginalWindow() const { return _window; };
private:
    virtual void init(const WindowConf& conf);
    virtual void close();
private:
    GLFWwindow* _window;

    struct WindowData {
        std::string title;
        unsigned int width, height;
        bool isVSync;
        EventCallbackFunction eventCallback;
    };

    WindowData _data;

    crux_unique<RendererContext> _context;

};

    
} // namespace crux  
