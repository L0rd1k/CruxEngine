#include "linux_input.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "src/sage/application.h"

namespace sage {

/** @warning Clear memory. **/
Input* Input::_keyInstance = new LinuxInput();

bool LinuxInput::impl_isKeyPressed(int keyCode) {
    auto window = static_cast<GLFWwindow*>(Application::getWindow().getOriginalWindow());
    auto state = glfwGetKey(window, keyCode);
    return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool LinuxInput::impl_isMouseButtonPresed(int keyCode) {
    auto window = static_cast<GLFWwindow*>(Application::getWindow().getOriginalWindow());
    auto state = glfwGetMouseButton(window, keyCode);
    return state == GLFW_PRESS;
}

float LinuxInput::impl_getMouseX() {
    auto pos = impl_getMousePos();
    return pos.first;
}

float LinuxInput::impl_getMouseY() {
    auto pos = impl_getMousePos();
    return pos.second;
}

std::pair<float, float> LinuxInput::impl_getMousePos() {
    auto window = static_cast<GLFWwindow*>(Application::getWindow().getOriginalWindow());
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    return std::make_pair((float)xpos, (float)ypos);
}

}  // namespace sage