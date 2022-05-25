#include "Application.h"

namespace Flow {

Application::Application() {
}

Application::~Application() {
}

void Application::Run() {
    WindowResizeEvent win(1024, 768);
    if(win.IsInCategory(EventCategoryApplication)) {
        std::cout << "IN: " << win.ToString() << std::endl;    
    } else {
        std::cout << "Out: " << win.ToString() << std::endl;    
    }

    if(win.IsInCategory(EventCategoryKeyboard)) {
        std::cout << "IN: " << win.ToString() << std::endl;    
    } else {
        std::cout << "Out: " << win.ToString() << std::endl;    
    }

    while(true) {

    }
}

}