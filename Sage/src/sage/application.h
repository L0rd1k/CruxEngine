#pragma once

#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

#include "core/timestep.h"
#include "events/application_event.h"
#include "events/event.h"
#include "gui/gui_layer.h"
#include "layer/layer_set.h"
#include "opengl/shader/shader_utils.h"
#include "render/buffer_layout.h"
#include "render/builder/buffer_builder.h"
#include "render/cameras/ortho_camera.h"
#include "render/index_buffer.h"
#include "render/renderer.h"
#include "render/renderer_api.h"
#include "render/shader.h"
#include "render/vertex_array.h"
#include "render/vertex_buffer.h"
#include "utils/logger/log.h"
#include "utils/timer/elapsed_timer.h"
#include "window/window.h"

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
    void fpsCounter();

private:
    static std::unique_ptr<Window> _window;

    GuiLayer* _guiLayer;
    bool _isRunning = true;
    LayerSet _layerSet;
    static Application* _appInstance;

    
    float _last_time = 0.0f;

    ElapsedTimer _fpsTimer;
    uint16_t _fpsCounter = 0;
};

Application* CreateApplication();

}  // namespace sage