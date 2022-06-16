#include "src/sage.h"

class ExampleLayer : public sage::Layer {
public:
	ExampleLayer() : Layer("Example") {
	}
	void onUpdate() override {
	}
	void onEvent(sage::Event& event) override {
		sage::Log::debug(getName(), ": ", event.GetName(), " ", event.ToString());
	}
};

class Sandbox : public sage::Application {
public:
    Sandbox() {
        pushLayer(new ExampleLayer());
    }
    virtual ~Sandbox() {
    }
};

sage::Application* sage::CreateApplication() {
    return new Sandbox();
}
