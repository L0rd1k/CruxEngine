#pragma once

#include "../Window.h"
#include "../../Events/KeyEvent.h"
#include "../../Events/MouseEvent.h"
#include "../../Events/ApplicationEvent.h"

namespace Flow {

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
};

    
} // namespace Flow  
