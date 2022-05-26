#include "src/Flow.h"

class ExampleLayer : public Flow::Layer {
public:
	ExampleLayer() : Layer("Example") {
	}
	void onUpdate() override {
	}
	void onEvent(Flow::Event& event) override {
		std::cout << getName() << ": " << event.GetName() << " " << event.ToString() << std::endl;
	}
};

class Sandbox : public Flow::Application {
public:
    Sandbox() {
        pushLayer(new ExampleLayer());
    }
    virtual ~Sandbox() {
    }
};

Flow::Application* Flow::CreateApplication() {
    return new Sandbox();
}
