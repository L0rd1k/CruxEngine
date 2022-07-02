#pragma once

#include <cassert>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <vector>

#include "src/sage/utils/logger/log.h"

namespace sage {

class Shader {
public:
    Shader(const std::string& vertex, const std::string& fragment);
    ~Shader();

    void bind() const;
    void unbind() const;

    unsigned int getShaderPorgram() {
        return _rendererId;
    }

    /** @brief Upload Vec4 uniform in shader. **/
    void loadUniform(const std::string& name, const glm::mat4& mat);

private:
    unsigned int compileShader(unsigned int type, const std::string& source);
    void createShader(const std::string& vertexShader, const std::string& fragmentShader);

private:
    unsigned int _rendererId;
};

}  // namespace sage