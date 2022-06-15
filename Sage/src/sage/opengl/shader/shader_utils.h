#pragma once

#include <fstream>
#include <sstream>
#include <string>

#include "src/sage/dstructs/array/array.h"
#include "src/sage/utils/logger/log.h"

enum class ShaderType {
    VERTEX = 0,
    FRAGMENT = 1,
    UNDEFINED = 255
};

struct ShaderData {
    std::string VertexData;
    std::string FragmentData;
};

static ShaderData parseShader(const std::string& path) {
    std::ifstream shaderStream(path);
    if (!shaderStream.is_open()) {
        Sage::Log::error("Shader", path, "not opened!");
        return {};
    }
    std::string line;
    sage::array<std::stringstream, 2> sstr;
    ShaderType shaderType = ShaderType::UNDEFINED;
    while (getline(shaderStream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                shaderType = ShaderType::VERTEX;
            } else if (line.find(line.find("fragment") != std::string::npos)) {
                shaderType = ShaderType::FRAGMENT;
            }
        } else {
            sstr[(int)shaderType] << line << '\n';
        }
    }
    return {sstr[0].str(), sstr[1].str()};
}