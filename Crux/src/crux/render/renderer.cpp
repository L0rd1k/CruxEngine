#include "renderer.h"

namespace crux {

Renderer::SceneData* Renderer::_sceneData = new Renderer::SceneData;

Renderer::~Renderer() {
    delete _sceneData;
}

void Renderer::startScene() {
}

void Renderer::startScene(OrthographicCamera& cam) {
    _sceneData->viewProjectionMat = cam.getOrthoViewProjectionMat();
}

void Renderer::endScene() {
}

void Renderer::submit(const std::shared_ptr<VertexArray>& vao,
                      const std::shared_ptr<Shader>& shader,
                      const glm::mat4& transform) {
    shader->bind();

    std::dynamic_pointer_cast<OpenGlShader>(shader)->loadUniformMat4("view_proj", _sceneData->viewProjectionMat);
    std::dynamic_pointer_cast<OpenGlShader>(shader)->loadUniformMat4("transform", transform);

    vao->bind();
    RenderCmd::drawIndexed(vao);
}

}  // namespace crux
