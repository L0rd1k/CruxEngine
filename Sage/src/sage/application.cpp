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
    float posTriangle[3 * 7] = {
        -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
        0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
        0.0f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f};
    _vertexArray.reset(VertexArray::init());
    _vertexBuffer.reset(VertexBuffer::init(posTriangle, sizeof(posTriangle)));
    sage::BufferArrLayout m_layout = {
        {ShaderType::fVec3, "a_Position"},
        {ShaderType::fVec4, "a_Color"}};
    _vertexBuffer->setLayout(m_layout);
    _vertexArray->addVertexBuffer(_vertexBuffer);
    unsigned int indices[3] = {0, 1, 2};
    _indexBuffer.reset(IndexBuffer::init(indices, sizeof(indices) / sizeof(indices[0])));
    _vertexArray->addIndexBuffer(_indexBuffer);
    /** @warning remove absolute path **/
    ShaderData data = parseShader("../../Sage/data/test.shader");
    _shader.reset(new Shader(data.VertexData, data.FragmentData));



    /** ======================= SECOND ELEMENT ======================== **/
    ShaderData data2 = parseShader("../../Sage/data/test2.shader");
    _shader2.reset(new Shader(data2.VertexData, data2.FragmentData));
    _squareVertexArray.reset(VertexArray::init());
    float posSquare[3 * 4] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f
    };
    std::shared_ptr<VertexBuffer> squareVertexBuffer;
    squareVertexBuffer.reset(VertexBuffer::init(posSquare, sizeof(posSquare)));
    squareVertexBuffer->setLayout({
        {ShaderType::fVec3, "a_Position"},
    });
    _squareVertexArray->addVertexBuffer(squareVertexBuffer);
    unsigned int squareIndices[6] = {0, 1, 2, 2, 3, 0};
    std::shared_ptr<IndexBuffer>_suqareindexBuffer;
    _suqareindexBuffer.reset(IndexBuffer::init(squareIndices, sizeof(squareIndices) / sizeof(squareIndices[0])));
    _squareVertexArray->addIndexBuffer(_suqareindexBuffer); 

    while (_isRunning) {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        _shader2->bind();
        _squareVertexArray->bind();
        glDrawElements(GL_TRIANGLES, _squareVertexArray->getIndexBuffer()->getSize(), GL_UNSIGNED_INT, nullptr);

        _shader->bind();
        _vertexArray->bind();
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
}

}  // namespace sage