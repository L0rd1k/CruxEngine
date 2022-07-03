#pragma once

#include <glad/glad.h>

#include "src/crux/render/shader.h"

namespace crux {

class OpenGlShader : public Shader {
public:
    OpenGlShader(const std::string& vertexShader, const std::string& fragmentShader);
    virtual ~OpenGlShader();

    virtual void bind() const override;
    virtual void unbind() const override;

    uint32_t getShaderProgram();

    void loadUniformInt(const std::string& name, int value);
    
    void loadUniformFloat(const std::string& name, int value);
    void loadUniformFloat2(const std::string& name, const glm::vec2& value);
    void loadUniformFloat3(const std::string& name, const glm::vec3& value);
    void loadUniformFloat4(const std::string& name, const glm::vec4& value);

    void loadUniformMat3(const std::string& name, const glm::mat3& matrix);
    void loadUniformMat4(const std::string& name, const glm::mat4& matrix);

private:
    unsigned int compileShader(unsigned int type, const std::string& source);
    void createShader(const std::string& vertexShader, const std::string& fragmentShader);

private:
    uint32_t _rendererId;
};

}  // namespace crux
