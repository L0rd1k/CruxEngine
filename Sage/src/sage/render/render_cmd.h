#pragma once 

#include "renderer_api.h"

#include "opengl/opengl_renderer_api.h"

namespace sage {

class RenderCmd {
public:

    inline static void clearColor(const glm::vec4& color) {
        _rendererApi->clearColor(color);
    }
    inline static void clear() {
        _rendererApi->clear();
    }

    inline static void drawIndexed(const std::shared_ptr<VertexArray>& vao) {
        _rendererApi->drawIndexed(vao);
    }
private:
    static RendererApi* _rendererApi;
};

}