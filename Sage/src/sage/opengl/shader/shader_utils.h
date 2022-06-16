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
        sage::Log::error("Shader", path, "not opened!");
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

static unsigned int compileShader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        sage::Log::error("Compilation error: ", (type == GL_VERTEX_SHADER ? "vertex " : "fragment "));
        sage::Log::error(message);
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