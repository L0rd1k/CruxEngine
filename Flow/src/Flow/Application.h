#pragma once

#include "Window/Window.h"

#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

#include <iostream>
#include <memory>

namespace Flow {

class Application {
   public:
    Application();
    virtual ~Application();
    void run();
    void onApplyEvent(Event& event);
private:
    bool onWindowClose(WindowCloseEvent& e);
    std::unique_ptr<Window> _window;
    bool _isRunning = true;
};

Application* CreateApplication();

}  // namespace Flow