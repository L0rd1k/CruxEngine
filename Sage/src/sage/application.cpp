#include "application.h"
namespace sage {

std::unique_ptr<Window> Application::_window = nullptr;
Application* Application::_appInstance = nullptr;

static GLenum ShaderTypetoGLType(ShaderType type) {
    switch (type) {
        case sage::ShaderType::fVec:
            return GL_FLOAT;
        case sage::ShaderType::fVec2:
            return GL_FLOAT;
        case sage::ShaderType::fVec3:
            return GL_FLOAT;
        case sage::ShaderType::fVec4:
            return GL_FLOAT;
        case sage::ShaderType::Mat3:
            return GL_FLOAT;
        case sage::ShaderType::Mat4:
            return GL_FLOAT;
        case sage::ShaderType::iVec:
            return GL_INT;
        case sage::ShaderType::iVec2:
            return GL_INT;
        case sage::ShaderType::iVec3:
            return GL_INT;
        case sage::ShaderType::iVec4:
            return GL_INT;
        case sage::ShaderType::Bool:
            return GL_BOOL;
        default: {
            sage::Log::warning("Unknown shader data type(converter)");
            return 0;
        }
    }
    return 0;
}

Application::Application() {
    _appInstance = this;
    _window = std::unique_ptr<Window>(Window::create());
    _window->setEventCallback(std::bind(&Application::onApplyEvent, this, std::placeholders::_1));

    _guiLayer = new GuiLayer();
    pushOverlay(_guiLayer);
}

Application::~Application() {
}

void Application::pushLayer(Layer* layer) {
    _layerSet.pushLayer(layer);
    layer->onAttach();
}

void Application::pushOverlay(Layer* layer) {
    _layerSet.pushOverlay(layer);
    layer->onAttach();
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

    float posSquare[3 * 7] = {
        -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
        0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
        0.0f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f};

    unsigned int indices[3] = {0, 1, 2};

    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    _vertexBuffer.reset(VertexBuffer::init(posSquare, sizeof(posSquare)));

    {
        sage::BufferArrLayout m_layout = {
            {ShaderType::fVec3, "a_Position"},
            {ShaderType::fVec4, "a_Color"}
        };
        _vertexBuffer->setLayout(m_layout);
    }

    uint32_t index = 0;
    const auto& layout = _vertexBuffer->getLayout();
    for (const auto& elem : layout) {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index,
                              elem.getElementsCount(), 
                              ShaderTypetoGLType(elem.type),
                              elem.normalized ? GL_TRUE : GL_FALSE,
                              layout.getStride(),
                              reinterpret_cast<const void*>(elem.offset));
        index++;
    }

    _indexBuffer.reset(IndexBuffer::init(indices, sizeof(indices) / sizeof(indices[0])));

    /** @warning remove absolute path **/
    ShaderData data = parseShader("../../Sage/data/test.shader");

    _shader.reset(new Shader(data.VertexData, data.FragmentData));

    while (_isRunning) {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        _shader->bind();

        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, _indexBuffer->getSize(), GL_UNSIGNED_INT, nullptr);

        for (Layer* layer : _layerSet) {
            layer->onUpdate();
        }

        _guiLayer->begin();
        for (Layer* layer : _layerSet) {
            layer->onDraw();
        }
        _guiLayer->end();

        _window->onUpdate();
    }

    // glDeleteProgram(shader);
}

}  // namespace sage