#include "application.h"
namespace sage {

Application::Application() {
    _window = std::unique_ptr<Window>(Window::create());
    _window->setEventCallback(std::bind(&Application::onApplyEvent, this, std::placeholders::_1));
}

Application::~Application() {
}

void Application::pushLayer(Layer* layer) {
    _layerSet.pushLayer(layer);
}

void Application::pushOverlay(Layer* layer) {
    _layerSet.pushOverlay(layer);
}

void Application::onApplyEvent(Event& e) {
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::onWindowClose, this, std::placeholders::_1));
    // Log::debug(e.GetName(), e.ToString());
    for (auto it = _layerSet.end(); it != _layerSet.begin();) {
        (*--it)->onEvent(e);
        if (e.isHandled) {
            break;
        }
    }
}

bool Application::onWindowClose(WindowCloseEvent& e) {
    _isRunning = false;
    return true;
}

void Application::run() {
    sage::vector<int> vec;
    Log::info(vec.capacity(), vec.size());
    vec.reserve(7);
    Log::info(vec.capacity(), vec.size());
    

    float posSquare[] = {
        -0.5f, -0.5f,  // 0
        0.5f, -0.5f,   // 1
        0.5f, 0.5f,    // 2
        -0.5f, 0.5f,   // 3
    };

    unsigned int indices[] = {
        0, 1, 2, 2, 3, 0,
    };

    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    //> Vertex buffer - Pass data to OpenGL2,
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), posSquare, GL_STATIC_DRAW);

    // Links vertex buffer with vao
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    //> Index buffer
    unsigned int idx_buffer;
    glGenBuffers(1, &idx_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idx_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    /** @warning remove absolute path **/
    ShaderData data = parseShader("../../Sage/data/test.shader");
    unsigned int shader = createShader(data.VertexData, data.FragmentData);
    glUseProgram(shader);
    int location = glGetUniformLocation(shader, "u_color");
    assert(location != -1);
    glUniform4f(location, 0.3f, 0.3f, 0.3f, 1.0f);

    //> Unbinding
    glBindVertexArray(0);
    glUseProgram(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    while (_isRunning) {
        glClear(GL_COLOR_BUFFER_BIT);

        //> Binding
        glUseProgram(shader);
        glUniform4f(location, 0.3f, 0.3f, 0.3f, 1.0f);

        glBindVertexArray(vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idx_buffer);

        // glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        for (Layer* layer : _layerSet) {
            layer->onUpdate();
        }
        _window->onUpdate();
    }

    glDeleteProgram(shader);
}

}  // namespace sage