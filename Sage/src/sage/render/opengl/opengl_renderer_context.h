#pragma once

#include "src/sage/render/renderer_context_base.h"
#include "src/sage/utils/logger/log.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct GLFWwindow;

namespace sage {

class OpenGlRendererContext : public RendererContext {
public:
    OpenGlRendererContext(GLFWwindow* window);
    
    virtual void init() override;
    virtual void swapBuffer() override;

private:
    GLFWwindow* _window = nullptr;
};

}  // namespace sage