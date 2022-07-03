#pragma once

#include <memory>

#include "opengl/opengl_shader.h"

#include "cameras/ortho_camera.h"
#include "render_cmd.h"
#include "shader.h"
#include "vertex_array.h"

namespace crux {

/** @brief Main renderer class for specific api type. **/
class Renderer {
public:
    virtual ~Renderer();

    /** @brief Start rendering scene without camera. **/
    static void startScene();

    /** @brief Start rendering scene with ortho camera. **/
    static void startScene(OrthographicCamera& cam);

    /** @brief Complete rendering scene. **/
    static void endScene();

    /** @brief Push request for drawing specific element. **/
    static void submit(const std::shared_ptr<VertexArray>& vao,
                       const std::shared_ptr<Shader>& shader,
                       const glm::mat4& transform = glm::mat4(1.0f));

    /** @brief Get currently used rendering api type. **/
    inline static RendererApi::RendererType getRendererType() {
        return RendererApi::getAPI();
    }

private:
    struct SceneData {
        glm::mat4 viewProjectionMat;
    };
    static SceneData* _sceneData;
};

}  // namespace crux