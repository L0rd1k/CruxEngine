#include <Flow.h>

class Sandbox : public Flow::Application {
public:
    Sandbox() {
    }
    virtual ~Sandbox() {
    }
};

Flow::Application* Flow::CreateApplication() {
    return new Sandbox();
}
