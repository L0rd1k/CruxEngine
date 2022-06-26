#include "3rdParty/ImGui/imgui.h"
#include "src/sage.h"

class ExampleLayer : public sage::Layer {
public:
    ExampleLayer() : Layer("Example") {
    }
    void onUpdate() override {
        // auto pos = sage::Input::getMousePos();
        // sage::Log::info(pos.first, "/", pos.second);

        if (sage::Input::isKeyPressed(SAGE_KEY_TAB)) {
            sage::Log::trace("Tab is pressed");
        }
    }
    void onEvent(sage::Event& event) override {
        sage::Log::debug(getName(), ": ", event.GetName(), " ", event.ToString());
        if (event.GetEventType() == sage::EventTypes::KeyPressed) {
            sage::KeyPressedEvent& e = (sage::KeyPressedEvent&)event;
            sage::Log::trace((char)e.GetKeyCode());
        }
    }

    void onDraw() override {
        // ImGui::Begin("Test");
        // ImGui::Text("This is some useful text.");           // Display some text (you can use a format strings too)
        // float f = 0.0;
        // ImGui::SliderFloat("Velocity", &f, 0.0f, 1.0f);             // Edit 1 float using a slider from 0.0f to 1.0f
        // ImGui::End();
    }
};

class Sandbox : public sage::Application {
public:
    Sandbox() {
        pushLayer(new ExampleLayer());
        // pushOverlay(new sage::GuiLayer());
    }
    virtual ~Sandbox() {
    }
};

sage::Application* sage::CreateApplication() {
    return new Sandbox();
}
