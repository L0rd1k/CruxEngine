#pragma once

#include "opengl/opengl_renderer_api.h"
#include "renderer_api.h"


namespace crux {

class RenderCmd {
public:
    static void clearColor(const glm::vec4& color);
    static void clear();

    static void drawIndexed(const std::shared_ptr<VertexArray>& vao);

private:
    static RendererApi* _rendererApi;
};

}  // namespace crux