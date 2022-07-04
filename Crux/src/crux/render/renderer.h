#pragma once

#include <memory>

#include "cameras/ortho_camera.h"
#include "opengl/opengl_shader.h"
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

    /** @brief Start rendering scene with ortho camera.
     * @param[in] cam Reference to orthographic camera. **/
    static void startScene(OrthographicCamera& cam);

    /** @brief Complete rendering scene. **/
    static void endScene();

    /** @brief Push request for drawing specific element.
     * @param[in] vao Vertex array reference.
     * @param[in] shader Shader reference.
     * @param[in] transform Transformation matrix of gloabl scene 4x4. **/
    static void submit(const crux_shared<VertexArray>& vao,
                       const crux_shared<Shader>& shader,
                       const glm::mat4& transform = glm::mat4(1.0f));

    /** @brief Get currently used rendering api type.
     * @return Return current rendering type. **/
    inline static RendererApi::RendererType getRendererType() {
        return RendererApi::getAPI();
    }

private:
    /** @brief Struct with all data about scene. **/
    struct SceneData {
        glm::mat4 viewProjectionMat;  //> View projection matrix 4x4
    };
    static SceneData* _sceneData;  //> Pointer to scene data.
};

}  // namespace crux