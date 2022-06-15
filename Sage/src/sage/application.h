#pragma once

#include "window/window.h"

#include "events/event.h"
#include "events/application_event.h"
#include "layer/layer_set.h"
#include "utils/logger/log.h"

#include <iostream>
#include <memory>

#include "dstructs/array/array.h"
#include "opengl/shader/shader_utils.h"
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