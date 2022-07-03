#include <glm/gtc/matrix_transform.hpp>

#include "3rdParty/ImGui/imgui.h"
#include "src/crux.h"

#include <GLFW/glfw3.h>

class ExampleLayer : public crux::Layer {
public:
    ExampleLayer()
        : Layer("Example"),
          _cam(-1.6f, 1.6f, -0.9f, 0.9f),
          _camPosition(0) {
        float posTriangle[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
            0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
            0.0f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f};
        _vertexArray.reset(crux::VertexArrayBuilder::create());
        _vertexBuffer.reset(crux::VertexBufferBuilder::create(posTriangle, sizeof(posTriangle)));
        crux::BufferLayout m_layout = {
            {crux::ShaderType::fVec3, "a_Position"},
            {crux::ShaderType::fVec4, "a_Color"}};
        _vertexBuffer->setLayout(m_layout);
        _vertexArray->addVertexBuffer(_vertexBuffer);
        unsigned int indices[3] = {0, 1, 2};
        _indexBuffer.reset(crux::IndexBufferBuilder::create(indices, sizeof(indices) / sizeof(indices[0])));
        _vertexArray->addIndexBuffer(_indexBuffer);

        /** @warning remove absolute path **/
        crux::ShaderData data = crux::Shader::parseShader("../../Crux/data/shaders/test.shader");
        _shader.reset(crux::ShaderBuilder::create(data.VertexData, data.FragmentData));
        /** ======================= SECOND ELEMENT ======================== **/

        crux::ShaderData data2 = crux::Shader::parseShader("../../Crux/data/shaders/test2.shader");
        _shader2.reset(crux::ShaderBuilder::create(data2.VertexData, data2.FragmentData));
        _squareVertexArray.reset(crux::VertexArrayBuilder::create());
        float posSquare[3 * 4] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.5f, 0.5f, 0.0f,
            -0.5f, 0.5f, 0.0f};
        std::shared_ptr<crux::VertexBuffer> squareVertexBuffer;
        squareVertexBuffer.reset(crux::VertexBufferBuilder::create(posSquare, sizeof(posSquare)));
        squareVertexBuffer->setLayout({
            {crux::ShaderType::fVec3, "a_Position"},
        });
        _squareVertexArray->addVertexBuffer(squareVertexBuffer);
        unsigned int squareIndices[6] = {0, 1, 2, 2, 3, 0};
        std::shared_ptr<crux::IndexBuffer> _suqareindexBuffer;
        _suqareindexBuffer.reset(crux::IndexBufferBuilder::create(squareIndices, sizeof(squareIndices) / sizeof(squareIndices[0])));
        _squareVertexArray->addIndexBuffer(_suqareindexBuffer);
    }

    void onUpdate(crux::Timestep timestep) override {
        if (crux::Input::isKeyPressed(CRUX_KEY_LEFT)) {
            _camPosition.x -= _camMoveSpeed * timestep;
        }
        if (crux::Input::isKeyPressed(CRUX_KEY_RIGHT)) {
            _camPosition.x += _camMoveSpeed * timestep;
        }
        if (crux::Input::isKeyPressed(CRUX_KEY_UP)) {
            _camPosition.y += _camMoveSpeed * timestep;
        }
        if (crux::Input::isKeyPressed(CRUX_KEY_DOWN)) {
            _camPosition.y -= _camMoveSpeed * timestep;
        }
        if (crux::Input::isKeyPressed(CRUX_KEY_Q)) {
            _camRotation += _camRotationSpeed * timestep;
        }
        if (crux::Input::isKeyPressed(CRUX_KEY_E)) {
            _camRotation -= _camRotationSpeed * timestep;
        }

        crux::RenderCmd::clearColor({0.1f, 0.1f, 0.1f, 1.0f});
        crux::RenderCmd::clear();

        _cam.setPosition(_camPosition);
        _cam.setRotation(_camRotation);

        crux::Renderer::startScene(_cam);

        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

        std::dynamic_pointer_cast<crux::OpenGlShader>(_shader2)->bind();
        std::dynamic_pointer_cast<crux::OpenGlShader>(_shader2)->loadUniformFloat3("n_color", square_color);

        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 20; j++) {
                glm::vec3 pos(i * 0.11f, j * 0.11f, 0.0f);
                glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
                crux::Renderer::submit(_squareVertexArray, _shader2, transform);
            }
        }
        crux::Renderer::submit(_vertexArray, _shader);
        crux::Renderer::endScene();
    }

    void onEvent(crux::Event& event) override {
    }

    void onDraw() override {
        ImGui::Begin("Settings");
        ImGui::ColorEdit3("Square Color", glm::value_ptr(square_color));
        ImGui::End();
    }

private:
    std::shared_ptr<crux::Shader> _shader;
    std::shared_ptr<crux::VertexArray> _vertexArray;

    std::shared_ptr<crux::VertexBuffer> _vertexBuffer;
    std::shared_ptr<crux::IndexBuffer> _indexBuffer;

    std::shared_ptr<crux::Shader> _shader2;
    std::shared_ptr<crux::VertexArray> _squareVertexArray;

    crux::OrthographicCamera _cam;
    glm::vec3 _camPosition;

    float _camMoveSpeed = 5.0f;
    float _camRotationSpeed = 180.0f;
    float _camRotation = 0.0f;

    glm::vec3 square_color = {0.2f, 0.3f, 0.8f};
};

class Sandbox : public crux::Application {
public:
    Sandbox() {
        pushLayer(new ExampleLayer());
    }
    virtual ~Sandbox() {
    }
};

crux::Application* crux::CreateApplication() {
    return new Sandbox();
}
