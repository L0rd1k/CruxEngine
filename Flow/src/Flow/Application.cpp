#include "Application.h"


namespace Flow {

Application::Application() {
    _window = std::unique_ptr<Window>(Window::create());
    _window->setEventCallback(std::bind(&Application::onApplyEvent, this, std::placeholders::_1));
}

Application::~Application() {
}

void Application::pushLayer(Layer* layer) {
    _layerSet.pushLayer(layer);
}

void Application::pushOverlay(Layer* layer) {
    _layerSet.pushOverlay(layer);
}

void Application::onApplyEvent(Event& e) {
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::onWindowClose, this, std::placeholders::_1));
    std::cout << e.GetName() << " " << e.ToString() << std::endl;
    for(auto it = _layerSet.end(); it != _layerSet.begin();) {
        (*--it)->onEvent(e);
        if(e.isHandled) {
            break;
        }
    }


}

bool Application::onWindowClose(WindowCloseEvent& e) {
    _isRunning = false;
    return true;
}

void Application::run() {
    while(_isRunning) {
        glClearColor(0,0,1,1);
        glClear(GL_COLOR_BUFFER_BIT);

        for(Layer* layer : _layerSet) {
            layer->onUpdate();
        }

        _window->onUpdate();
    }
}

}