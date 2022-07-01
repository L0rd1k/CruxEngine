#pragma once

#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

#include "events/application_event.h"
#include "events/event.h"
#include "layer/layer_set.h"
#include "opengl/shader/shader_utils.h"

#include "render/buffer_layout.h"
#include "render/index_buffer.h"
#include "render/vertex_buffer.h"

#include "render/shader.h"
#include "render/vertex_array.h"

#include "render/renderer.h"

#include "render/renderer_api.h"

#include "render/builder/buffer_builder.h"

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
    
    std::shared_ptr<Shader> _shader;
    std::shared_ptr<VertexBuffer> _vertexBuffer;
    std::shared_ptr<IndexBuffer> _indexBuffer;
    std::shared_ptr<VertexArray> _vertexArray;


    std::shared_ptr<Shader> _shader2;
    std::shared_ptr<VertexArray> _squareVertexArray;

    GuiLayer* _guiLayer;
    bool _isRunning = true;
    LayerSet _layerSet; 
    static Application* _appInstance;
};

Application* CreateApplication();

}  // namespace sage