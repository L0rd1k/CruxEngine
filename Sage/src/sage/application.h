#pragma once

#include "window/window.h"

#include "events/event.h"
#include "events/application_event.h"
#include "layer/layer_set.h"
#include "utils/logger/log.h"

#include <iostream>
#include <memory>

#include <vector>
#include <algorithm>

#include "opengl/shader/shader_utils.h"

#include "src/sage/dstructs/pair/pair.h"
#include "src/sage/dstructs//map/map.h"

#include "src/sage/dstructs/tree/rb_tree/rb_tree.h"
#include "src/sage/dstructs/tree/rb_tree/rb_tree_node.h"
#include "src/sage/dstructs/tree/rb_tree/rb_tree_iterator.h"
#include "src/sage/dstructs/tree/rb_tree/rb_tree_header.h"

namespace sage {

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

}  // namespace sage