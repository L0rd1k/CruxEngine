#include "opengl_renderer_context.h"

namespace crux {

OpenGlRendererContext::OpenGlRendererContext(GLFWwindow* window)
    : _window(window) {
}

void OpenGlRendererContext::init() {
    glfwMakeContextCurrent(_window);
    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);  //> Make use of existing GLFW loader;
    Log::info("OpenGL renderer:", glGetString(GL_VENDOR), glGetString(GL_RENDERER), glGetString(GL_VERSION));
}

void OpenGlRendererContext::swapBuffer() {
    glfwSwapBuffers(_window);
}

}  // namespace crux