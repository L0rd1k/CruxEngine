#include "src/Sage.h"

class ExampleLayer : public Sage::Layer {
public:
	ExampleLayer() : Layer("Example") {
	}
	void onUpdate() override {
	}
	void onEvent(Sage::Event& event) override {
		std::cout << getName() << ": " << event.GetName() << " " << event.ToString() << std::endl;
	}
};

class Sandbox : public Sage::Application {
public:
    Sandbox() {
        pushLayer(new ExampleLayer());
    }
    virtual ~Sandbox() {
    }
};

Sage::Application* Sage::CreateApplication() {
    return new Sandbox();
}
