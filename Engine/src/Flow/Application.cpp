#include "Application.h"
 
namespace Flow {

Application::Application() {
}

Application::~Application() {
}

void Application::Run() {
    while(true) {
        std::cout << "Test" << std::endl;
    }
}

}