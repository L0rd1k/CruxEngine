#include "gui_layer.h"

namespace sage {

GuiLayer::GuiLayer()
    : Layer("Gui layer") {
}

GuiLayer::~GuiLayer() {
}

void GuiLayer::onAttach() {
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

    io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;

    ImGui::StyleColorsLight();
    ImGui_ImplOpenGL3_Init("#version 300 es");
}

void GuiLayer::onUpdate() {
    ImGuiIO& io = ImGui::GetIO();
    Application& app = Application::getApplication();
    io.DisplaySize = ImVec2(app.getWindow().getWidth(), app.getWindow().getHeight());

    float time = (float)glfwGetTime();
    io.DeltaTime = _time > 0.0f ? (time - _time) : (1.0f / 60.0f);
    _time = time;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

    static bool show = true;
    ImGui::ShowDemoWindow(&show);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GuiLayer::onDetach() {
}

void GuiLayer::onEvent(Event& event) {
    EventDispatcher dispatch(event);
    dispatch.Dispatch<MouseButtonPressedEvent>(std::bind(&GuiLayer::onMouseButtonPressedEvent, this, std::placeholders::_1));
    dispatch.Dispatch<MouseButtonReleasedEvent>(std::bind(&GuiLayer::onMouseButtonReleasedEvent, this, std::placeholders::_1));
    dispatch.Dispatch<MouseMovedEvent>(std::bind(&GuiLayer::onMouseMovedEvent, this, std::placeholders::_1));
    dispatch.Dispatch<MouseScrolledEvent>(std::bind(&GuiLayer::onMouseScrolledEvent, this, std::placeholders::_1));
    dispatch.Dispatch<KeyPressedEvent>(std::bind(&GuiLayer::onKeyPressedEvent, this, std::placeholders::_1));
    dispatch.Dispatch<KeyReleasedEvent>(std::bind(&GuiLayer::onKeyReleasedEvent, this, std::placeholders::_1));
    dispatch.Dispatch<WindowResizeEvent>(std::bind(&GuiLayer::onWindowResizeEvent, this, std::placeholders::_1));
    dispatch.Dispatch<KeyTypedEvent>(std::bind(&GuiLayer::onKeyTypedEvent, this, std::placeholders::_1));
}

bool GuiLayer::onMouseButtonPressedEvent(MouseButtonPressedEvent& e) {
    ImGuiIO& io = ImGui::GetIO();
    io.MouseDown[(int)e.GetMouseButton()] = true;
    return false;
}

bool GuiLayer::onMouseButtonReleasedEvent(MouseButtonReleasedEvent& e) {
    ImGuiIO& io = ImGui::GetIO();
    io.MouseDown[(int)e.GetMouseButton()] = false;
    return false;
}

bool GuiLayer::onMouseMovedEvent(MouseMovedEvent& e) {
    ImGuiIO& io = ImGui::GetIO();
    io.MousePos = ImVec2(e.GetX(), e.GetY());
    return false;
}

bool GuiLayer::onMouseScrolledEvent(MouseScrolledEvent& e) {
    ImGuiIO& io = ImGui::GetIO();
    io.MouseWheelH += e.GetXOffset();
    io.MouseWheel += e.GetYOffset();
    return false;
}

bool GuiLayer::onKeyPressedEvent(KeyPressedEvent& e) {
    ImGuiIO& io = ImGui::GetIO();
    io.KeysDown[(int)e.GetKeyCode()] = true;

    io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
    io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
    io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
    io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

    return false;
}

bool GuiLayer::onKeyReleasedEvent(KeyReleasedEvent& e) {
    ImGuiIO& io = ImGui::GetIO();
    io.KeysDown[(int)e.GetKeyCode()] = false;
    return false;
}

bool GuiLayer::onWindowResizeEvent(WindowResizeEvent& e) {
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
    io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
    glViewport(0, 0, e.GetWidth(), e.GetHeight());
    return false;
}

bool GuiLayer::onKeyTypedEvent(KeyTypedEvent& e) {
    ImGuiIO& io = ImGui::GetIO();
    int character_code = e.GetKeyCode();
    if(character_code > 0 && character_code < 0x10000)
        io.AddInputCharacter((unsigned short)character_code);
    return false;
}

}  // namespace sage