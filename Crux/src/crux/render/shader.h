#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cassert>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <array>

#include "src/crux/utils/logger/log.h"

namespace crux {

enum class ShaderFormat {
    VERTEX = 0,
    FRAGMENT = 1,
    UNDEFINED = 255
};

struct ShaderData {
    std::string VertexData;
    std::string FragmentData;
};

class Shader {
public:
    virtual ~Shader() = default;
    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    static ShaderData parseShader(const std::string& path) {
        std::ifstream shaderStream(path);
        if (!shaderStream.is_open()) {
            crux::Log::error("Shader", path, "not opened!");
            return {};
        }
        std::string line;
        std::array<std::stringstream, 2> sstr;
        ShaderFormat shaderType = ShaderFormat::UNDEFINED;
        while (getline(shaderStream, line)) {
            if (line.find("#shader") != std::string::npos) {
                if (line.find("vertex") != std::string::npos) {
                    shaderType = ShaderFormat::VERTEX;
                } else if (line.find(line.find("fragment") != std::string::npos)) {
                    shaderType = ShaderFormat::FRAGMENT;
                }
            } else {
                sstr[(int)shaderType] << line << '\n';
            }
        }
        return {sstr[0].str(), sstr[1].str()};
    }
};

}  // namespace crux