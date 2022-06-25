#include "gui_layer.h"

#define IMGUI_IMPL_API
#include "3rdParty/ImGui/backends/imgui_impl_glfw.h"
#include "3rdParty/ImGui/backends/imgui_impl_opengl3.h"

#include "src/sage/application.h"

#include "src/sage/events/key_event.h"
#include "src/sage/events/mouse_event.h"
#include "src/sage/events/application_event.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace sage {

GuiLayer::GuiLayer()
    : Layer("Gui layer") {
}

GuiLayer::~GuiLayer() {
}


void GuiLayer::onAttach() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    ImGui::StyleColorsLight();
    ImGuiStyle& style = ImGui::GetStyle();
    if(io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    Application& app = Application::getApplication();
    GLFWwindow* window = static_cast<GLFWwindow*>(app.getWindow().getOriginalWindow());
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 300 es");
} 

void GuiLayer::onDetach() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void GuiLayer::begin() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void GuiLayer::end() {
    ImGuiIO& io = ImGui::GetIO();
    Application& app = Application::getApplication();
    io.DisplaySize = ImVec2(app.getWindow().getWidth(), app.getWindow().getHeight());
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    if(io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        GLFWwindow* context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(context);
    }
}

void GuiLayer::onDraw() {
    static bool isShow = true;
    ImGui::ShowDemoWindow(&isShow);
}

}  // namespace sage