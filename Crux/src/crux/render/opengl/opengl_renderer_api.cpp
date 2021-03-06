#include "opengl_renderer_api.h"

namespace crux {

void OpenGlRendererAPI::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGlRendererAPI::clearColor(const glm::vec4& color) {
    glClearColor(color.r, color.g, color.b, color.a);
}

void OpenGlRendererAPI::drawIndexed(const crux_shared<VertexArray>& vao) {
    glDrawElements(GL_TRIANGLES, vao->getIndexBuffer()->getSize(), GL_UNSIGNED_INT, nullptr);
}

}  // namespace crux