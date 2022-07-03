#include "render_cmd.h"

namespace crux {

RendererApi* RenderCmd::_rendererApi = new OpenGlRendererAPI;

void RenderCmd::clearColor(const glm::vec4& color) {
    _rendererApi->clearColor(color);
}
void RenderCmd::clear() {
    _rendererApi->clear();
}

void RenderCmd::drawIndexed(const std::shared_ptr<VertexArray>& vao) {
    _rendererApi->drawIndexed(vao);
}

}  // namespace crux