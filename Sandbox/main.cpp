#include "3rdParty/ImGui/imgui.h"
#include "src/sage.h"

class ExampleLayer : public sage::Layer {
public:
    ExampleLayer()
        : Layer("Example"),
          _cam(-1.6f, 1.6f, -0.9f, 0.9f),
          _camPosition(0) {
        float posTriangle[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
            0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
            0.0f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f};
        _vertexArray.reset(sage::VertexArrayBuilder::create());
        _vertexBuffer.reset(sage::VertexBufferBuilder::create(posTriangle, sizeof(posTriangle)));
        sage::BufferLayout m_layout = {
            {sage::ShaderType::fVec3, "a_Position"},
            {sage::ShaderType::fVec4, "a_Color"}};
        _vertexBuffer->setLayout(m_layout);
        _vertexArray->addVertexBuffer(_vertexBuffer);
        unsigned int indices[3] = {0, 1, 2};
        _indexBuffer.reset(sage::IndexBufferBuilder::create(indices, sizeof(indices) / sizeof(indices[0])));
        _vertexArray->addIndexBuffer(_indexBuffer);
        /** @warning remove absolute path **/
        ShaderData data = parseShader("../../Sage/data/shaders/test.shader");
        _shader.reset(new sage::Shader(data.VertexData, data.FragmentData));

        /** ======================= SECOND ELEMENT ======================== **/
        ShaderData data2 = parseShader("../../Sage/data/shaders/test2.shader");
        _shader2.reset(new sage::Shader(data2.VertexData, data2.FragmentData));
        _squareVertexArray.reset(sage::VertexArrayBuilder::create());
        float posSquare[3 * 4] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.5f, 0.5f, 0.0f,
            -0.5f, 0.5f, 0.0f};
        std::shared_ptr<sage::VertexBuffer> squareVertexBuffer;
        squareVertexBuffer.reset(sage::VertexBufferBuilder::create(posSquare, sizeof(posSquare)));
        squareVertexBuffer->setLayout({
            {sage::ShaderType::fVec3, "a_Position"},
        });
        _squareVertexArray->addVertexBuffer(squareVertexBuffer);
        unsigned int squareIndices[6] = {0, 1, 2, 2, 3, 0};
        std::shared_ptr<sage::IndexBuffer> _suqareindexBuffer;
        _suqareindexBuffer.reset(sage::IndexBufferBuilder::create(squareIndices, sizeof(squareIndices) / sizeof(squareIndices[0])));
        _squareVertexArray->addIndexBuffer(_suqareindexBuffer);
    }

    void onUpdate(sage::Timestep timestep) override {
        // auto pos = sage::Input::getMousePos();
        // sage::Log::info(pos.first, "/", pos.second);
        // if (sage::Input::isKeyPressed(SAGE_KEY_TAB)) {
        //     sage::Log::trace("Tab is pressed");
        // }
        if (sage::Input::isKeyPressed(SAGE_KEY_LEFT)) {
            _camPosition.x -= _camMoveSpeed * timestep;
        }
        if (sage::Input::isKeyPressed(SAGE_KEY_RIGHT)) {
            _camPosition.x += _camMoveSpeed * timestep;
        }
        if (sage::Input::isKeyPressed(SAGE_KEY_UP)) {
            _camPosition.y += _camMoveSpeed * timestep;
        }
        if (sage::Input::isKeyPressed(SAGE_KEY_DOWN)) {
            _camPosition.y -= _camMoveSpeed * timestep;
        }
        if (sage::Input::isKeyPressed(SAGE_KEY_Q)) {
            _camRotation += _camRotationSpeed * timestep;
        }
        if (sage::Input::isKeyPressed(SAGE_KEY_E)) {
            _camRotation -= _camRotationSpeed * timestep;
        }

        sage::RenderCmd::clearColor({0.1f, 0.1f, 0.1f, 1.0f});
        sage::RenderCmd::clear();

        _cam.setPosition(_camPosition);
        _cam.setRotation(_camRotation);

        sage::Renderer::startScene(_cam);
        sage::Renderer::submit(_squareVertexArray, _shader2);
        sage::Renderer::submit(_vertexArray, _shader);
        sage::Renderer::endScene();
    }

    void onEvent(sage::Event& event) override {
        // sage::Log::debug(getName(), ": ", event.GetName(), " ", event.ToString());
        // if (event.GetEventType() == sage::EventTypes::KeyPressed) {
        //     sage::KeyPressedEvent& e = (sage::KeyPressedEvent&)event;
        //     sage::Log::trace((char)e.GetKeyCode());
        // }
    }

    void onDraw() override {
    }

private:
    std::shared_ptr<sage::Shader> _shader;
    std::shared_ptr<sage::VertexArray> _vertexArray;

    std::shared_ptr<sage::VertexBuffer> _vertexBuffer;
    std::shared_ptr<sage::IndexBuffer> _indexBuffer;

    std::shared_ptr<sage::Shader> _shader2;
    std::shared_ptr<sage::VertexArray> _squareVertexArray;

    sage::OrthographicCamera _cam;
    glm::vec3 _camPosition;

    float _camMoveSpeed = 5.0f;
    float _camRotationSpeed = 180.0f;
    float _camRotation = 0.0f;
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
