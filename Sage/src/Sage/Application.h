#pragma once

#include "Window/Window.h"

#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Layer/LayerSet.h"

#include <iostream>
#include <memory>

namespace Sage {

class Application {
   public:
    Application();
    virtual ~Application();
    void run();
    void onApplyEvent(Event& event);
    void pushLayer(Layer* layer);
    void pushOverlay(Layer* layer);
private:
    bool onWindowClose(WindowCloseEvent& e);
private:
    std::unique_ptr<Window> _window;
    bool _isRunning = true;
    LayerSet _layerSet;
};

Application* CreateApplication();

}  // namespace Sage