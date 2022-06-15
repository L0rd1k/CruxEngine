#include "application.h"
namespace Sage {

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
    Log::debug(e.GetName(), " ", e.ToString());
    for(auto it = _layerSet.end(); it != _layerSet.begin();) {
        (*--it)->onEvent(e);
        if(e.isHandled) {
            break;
        }
    }
}

bool Application::onWindowClose(WindowCloseEvent& e) {
    _isRunning = false;
    return true;
}

static unsigned int compileShader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE)  {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        Log::error("Compilation error: ", (type == GL_VERTEX_SHADER ? "vertex " : "fragment "));
        Log::error(message);
        glDeleteShader(id);
        return 0;
    }
    return id;
}

static unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}


void Application::run() {
    float poss[6] = {
        -0.5f, -0.5f, 0.0f, 0.5f, 0.5f, -0.5f,
    };

    //> Vertex buffer - Pass data to OpenGL
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), poss, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
    // glBindBuffer(GL_ARRAY_BUFFER, 0);

    /** @warning remove absolute path **/
    ShaderData data = parseShader("../../Sage/data/test.shader");
    unsigned int shader = createShader(data.VertexData, data.FragmentData);
    glUseProgram(shader);
    

    while(_isRunning) {
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        for(Layer* layer : _layerSet) {
            layer->onUpdate();
        }
        _window->onUpdate();
    }

    glDeleteProgram(shader);

}

}