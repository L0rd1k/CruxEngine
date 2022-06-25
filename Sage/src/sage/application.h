#pragma once

#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>


#include "events/application_event.h"
#include "events/event.h"
#include "layer/layer_set.h"
#include "opengl/shader/shader_utils.h"

#include "utils/logger/log.h"
#include "window/window.h"
#include "gui/gui_layer.h"

namespace sage {

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

private:
    static std::unique_ptr<Window> _window;
    std::unique_ptr<GuiLayer> _guiLayer;
    bool _isRunning = true;
    LayerSet _layerSet;
    static Application* _appInstance;
};

Application* CreateApplication();

}  // namespace sage