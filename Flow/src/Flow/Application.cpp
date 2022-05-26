#include "Application.h"


namespace Flow {

Application::Application() {
    _window = std::unique_ptr<Window>(Window::create());
    _window->setEventCallback(std::bind(&Application::onApplyEvent, this, std::placeholders::_1));
}

Application::~Application() {
}

void Application::onApplyEvent(Event& e) {
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::onWindowClose, this, std::placeholders::_1));
    std::cout << e.GetName() << " " << e.ToString() << std::endl;
}

bool Application::onWindowClose(WindowCloseEvent& e) {
    _isRunning = false;
    return true;
}

void Application::run() {
    while(_isRunning) {
        glClearColor(0,0,1,1);
        glClear(GL_COLOR_BUFFER_BIT);
        _window->onUpdate();
    }
}

}