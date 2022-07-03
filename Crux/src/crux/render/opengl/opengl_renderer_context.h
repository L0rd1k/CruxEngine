#pragma once

#include "src/crux/render/renderer_context.h"
#include "src/crux/utils/logger/log.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct GLFWwindow;

namespace crux {

class OpenGlRendererContext : public RendererContext {
public:
    OpenGlRendererContext(GLFWwindow* window);
    
    virtual void init() override;
    virtual void swapBuffer() override;

private:
    GLFWwindow* _window = nullptr;
};

}  // namespace crux