#include "LinuxWindow.h"

namespace Flow {

static bool _isGlfwInitialized = false;
static void GLFWErrorCallback(int error, const char* msg) {
    std::cerr << "GLFW ERROR: " << msg << std::endl;
}

Window* Window::create(const WindowConf& conf) {
    return new LinuxWindow(conf);
}

LinuxWindow::LinuxWindow(const WindowConf& conf) {
    init(conf);
}

LinuxWindow::~LinuxWindow() {
}

void LinuxWindow::init(const WindowConf& conf) {
    _data.title = conf.headerTitle;
    _data.height = conf.height;
    _data.width = conf.width;

    std::cout << "Linux window creating: " <<  conf.headerTitle << " " 
        << " " << conf.height << " x " << conf.width << std::endl;

    if(!_isGlfwInitialized) {
        if(!glfwInit()) {
            std::cerr << "Could not initilaize GLFW!" << std::endl;
            glfwSetErrorCallback(GLFWErrorCallback);
            return ;
        }
        _isGlfwInitialized = true;
    }

    _window = glfwCreateWindow((int)conf.width, (int)conf.height, _data.title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(_window);
    glfwSetWindowUserPointer(_window, &_data);
    setVSync(true);

    glfwSetWindowSizeCallback(_window, [](GLFWwindow* window, int width, int height) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        data.height = height;
        data.width = width;
        WindowResizeEvent event(width, height);
        data.eventCallback(event);
    });

    glfwSetWindowCloseCallback(_window, [](GLFWwindow* window) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        WindowCloseEvent event;
        data.eventCallback(event);
    }); 
 
    glfwSetKeyCallback(_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        switch (action) {
            case GLFW_PRESS: {
                KeyPressedEvent event(key, 0);
                data.eventCallback(event);
                break;
            } case GLFW_RELEASE: {
                KeyReleasedEvent event(key);
                data.eventCallback(event);
                break;
            } case GLFW_REPEAT: {
                KeyPressedEvent event(key, 1);
                data.eventCallback(event);
                break;
            } 
        }
    }); 

    glfwSetMouseButtonCallback(_window, [](GLFWwindow* window, int button, int action, int modes) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        switch (action) {
            case GLFW_PRESS: {
                MouseButtonPressedEvent event(button);
                data.eventCallback(event);
                break;
            } case GLFW_RELEASE: {
                MouseButtonReleasedEvent event(button);
                data.eventCallback(event);
                break; 
            }
        }
    });

    glfwSetScrollCallback(_window, [](GLFWwindow* window, double xOffset,double yOffset) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        MouseScrolledEvent event((float)xOffset, (float)yOffset);
        data.eventCallback(event);
    });

    glfwSetCursorPosCallback(_window, [](GLFWwindow* window, double xPos,double yPos){
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        MouseMovedEvent event((float)xPos, (float)yPos);
        data.eventCallback(event);
    });
}

void LinuxWindow::close() {
    glfwDestroyWindow(_window);
}

void LinuxWindow::onUpdate() {
    glfwPollEvents();
    glfwSwapBuffers(_window);
}

void LinuxWindow::setVSync(bool enabled) {
    if(enabled) {
        glfwSwapInterval(1);
    } else {
        glfwSwapInterval(0);
    }
    _data.isVSync = enabled;
} 

bool LinuxWindow::isVSunc() const {
    return _data.isVSync;
}

}  // namespace Flow