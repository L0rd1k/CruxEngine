#include "application.h"

namespace sage {

std::unique_ptr<Window> Application::_window = nullptr;
Application* Application::_appInstance = nullptr;

static GLenum ShaderTypetoGLType(ShaderType type) {
    switch (type) {
        case sage::ShaderType::fVec:
            return GL_FLOAT;
        case sage::ShaderType::fVec2:
            return GL_FLOAT;
        case sage::ShaderType::fVec3:
            return GL_FLOAT;
        case sage::ShaderType::fVec4:
            return GL_FLOAT;
        case sage::ShaderType::Mat3:
            return GL_FLOAT;
        case sage::ShaderType::Mat4:
            return GL_FLOAT;
        case sage::ShaderType::iVec:
            return GL_INT;
        case sage::ShaderType::iVec2:
            return GL_INT;
        case sage::ShaderType::iVec3:
            return GL_INT;
        case sage::ShaderType::iVec4:
            return GL_INT;
        case sage::ShaderType::Bool:
            return GL_BOOL;
        default: {
            sage::Log::warning("Unknown shader data type(converter)");
            return 0;
        }
    }
    return 0;
}

Application::Application() {
    _appInstance = this;
    _window = std::unique_ptr<Window>(Window::create());
    _window->setEventCallback(std::bind(&Application::onApplyEvent, this, std::placeholders::_1));

    _guiLayer = new GuiLayer();
    pushOverlay(_guiLayer);
}

Application::~Application() {
}

void Application::pushLayer(Layer* layer) {
    _layerSet.pushLayer(layer);
    layer->onAttach();
}

void Application::pushOverlay(Layer* layer) {
    _layerSet.pushOverlay(layer);
    layer->onAttach();
}

void Application::onApplyEvent(Event& e) {
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::onWindowClose, this, std::placeholders::_1));
    // Log::debug(e.GetName(), e.ToString());
    for (auto it = _layerSet.end(); it != _layerSet.begin();) {
        (*--it)->onEvent(e);
        if (e.isHandled) {
            break;
        }
    }
}

bool Application::onWindowClose(WindowCloseEvent& e) {
    _isRunning = false;
    return true;
}

void Application::run() {
    while (_isRunning) {
        for (Layer* layer : _layerSet) {
            layer->onUpdate();
        }
        _guiLayer->begin();
        for (Layer* layer : _layerSet) {
            layer->onDraw();
        }
        _guiLayer->end();
        _window->onUpdate();
    }
}

}  // namespace sage