#include "src/Sage.h"

class ExampleLayer : public Sage::Layer {
public:
	ExampleLayer() : Layer("Example") {
	}
	void onUpdate() override {
	}
	void onEvent(Sage::Event& event) override {
		Sage::Log::debug(getName(), ": ", event.GetName(), " ", event.ToString());
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
