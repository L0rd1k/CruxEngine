#pragma once

#include "3rdParty/ImGui/backends/imgui_impl_glfw.h"
#include "3rdParty/ImGui/backends/imgui_impl_opengl3.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "src/sage/application.h"

#include "src/sage/events/key_event.h"
#include "src/sage/events/mouse_event.h"
#include "src/sage/events/application_event.h"

#include "src/sage/layer/layer.h"

namespace sage {

class GuiLayer : public Layer {
public:
    GuiLayer();
    ~GuiLayer();
    void onAttach() override;
    void onDetach() override;
    void onUpdate() override;
    void onEvent(Event& e) override;

private:
    bool onMouseButtonPressedEvent(MouseButtonPressedEvent& e);
    bool onMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
    bool onMouseMovedEvent(MouseMovedEvent& e);
    bool onMouseScrolledEvent(MouseScrolledEvent& e);
    bool onKeyPressedEvent(KeyPressedEvent& e);
    bool onKeyReleasedEvent(KeyReleasedEvent& e);
    bool onWindowResizeEvent(WindowResizeEvent& e);
    bool onKeyTypedEvent(KeyTypedEvent& e);
private:
    float _time = 0.0f;
};

}  // namespace sage