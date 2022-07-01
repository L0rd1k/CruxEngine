#pragma once

#include "src/sage/render/renderer_api.h"
#include <glad/glad.h>

namespace sage {

class OpenGlRendererAPI : public RendererApi {
public:
    virtual void clear() override;
    virtual void clearColor(const glm::vec4& color) override;
    virtual void drawIndexed(const std::shared_ptr<VertexArray>& vao) override;
};

}  // namespace sage