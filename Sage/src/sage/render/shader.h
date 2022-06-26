#pragma once

#include <string>
#include <vector>
#include <cassert>

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
private:
    unsigned int compileShader(unsigned int type, const std::string& source);
    void createShader(const std::string& vertexShader, const std::string& fragmentShader);

private:
    unsigned int _rendererId;
};

}  // namespace sage