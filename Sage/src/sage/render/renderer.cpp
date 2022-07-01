#include "renderer.h"

namespace sage {

void Renderer::startScene() {
}

void Renderer::endScene() {
}

void Renderer::submit(const std::shared_ptr<VertexArray>& vao) {
    vao->bind();
    RenderCmd::drawIndexed(vao);
}

}  // namespace sage
