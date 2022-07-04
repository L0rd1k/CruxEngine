#pragma once

#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

#include "src/crux/core.h"

#include "core/timestep.h"
#include "events/application_event.h"

#include "events/event.h"
#include "gui/gui_layer.h"
#include "layer/layer_set.h"
#include "render/builder/buffer_builder.h"
#include "render/shader.h"
#include "utils/logger/log.h"
#include "utils/timer/elapsed_timer.h"
#include "window/window.h"

#include <GLFW/glfw3.h>

namespace crux {

class Application {
public:
    Application();
    virtual ~Application();
    void run();
    void onApplyEvent(Event& event);
    void pushLayer(Layer* layer);
    void pushOverlay(Layer* layer);

    inline static Window& getWindow() {
        return *_window;
    };

    inline static Application& getApplication() {
        return *_appInstance;
    }

private:
    bool onWindowClose(WindowCloseEvent& e);
    void fpsCounter();

private:
    static crux_unique<Window> _window;

    GuiLayer* _guiLayer;
    bool _isRunning = true;
    LayerSet _layerSet;
    static Application* _appInstance;

    
    float _last_time = 0.0f;
    double accumulator = 0.0;
    const double dt = 0.01; 

    ElapsedTimer _fpsTimer;
    uint16_t _fpsCounter = 0;
};

Application* CreateApplication();

}  // namespace crux