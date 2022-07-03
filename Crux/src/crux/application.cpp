#include "application.h"

namespace crux {

std::unique_ptr<Window> Application::_window = nullptr;
Application* Application::_appInstance = nullptr;

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

void Application::fpsCounter() {
    if (_fpsTimer.elapsedSec() > 1) {
        Log::trace("FPS :", _fpsCounter);
        _fpsTimer.restart();
        _fpsCounter = 0;
    }
    _fpsCounter++;
}

void Application::run() {
    while (_isRunning) {
        
        fpsCounter();

        float time = (float)glfwGetTime();
        Timestep t_step = time - _last_time;
        _last_time = time;
        accumulator += t_step;
        while (accumulator >= dt) {
            // Log::trace(accumulator);
            accumulator -= dt;
        }

        // Log::info(t_step);

        for (Layer* layer : _layerSet) {
            layer->onUpdate(t_step);
        }
        _guiLayer->begin();
        for (Layer* layer : _layerSet) {
            layer->onDraw();
        }
        _guiLayer->end();
        _window->onUpdate();
    }
}

}  // namespace crux