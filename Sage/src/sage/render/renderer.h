#pragma once

#include <memory>

#include "render_cmd.h"
#include "vertex_array.h"

namespace sage {

class Renderer {
public:
    static void startScene();
    static void endScene();
    static void submit(const std::shared_ptr<VertexArray>& vao);
    inline static RendererApi::RendererType getRendererType() {
        return RendererApi::getAPI();
    }
};

}  // namespace sage