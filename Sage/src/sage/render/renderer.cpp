#include "renderer.h"

namespace sage {

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
                      const std::shared_ptr<Shader>& shader) {
    shader->bind();
    shader->loadUniform("view_proj", _sceneData->viewProjectionMat);
    vao->bind();
    RenderCmd::drawIndexed(vao);
}

}  // namespace sage
