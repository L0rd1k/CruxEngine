#include "shader.h"

#include <glad/glad.h>

namespace sage {

Shader::Shader(const std::string& vertex, const std::string& fragment) {
    createShader(vertex, fragment);
}

unsigned int Shader::compileShader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);  //> Create empty vertex shader
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);  //> Get vertexShader sources
    glCompileShader(id);                   //> CompileShader

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

void Shader::createShader(const std::string& vertexShader, const std::string& fragmentShader) {
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);
    _rendererId = glCreateProgram();
    glAttachShader(_rendererId, vs);
    glAttachShader(_rendererId, fs);

    glLinkProgram(_rendererId);
    int linkingResult = 0;
    glGetProgramiv(_rendererId, GL_LINK_STATUS, (int*)&linkingResult);
    if (linkingResult == GL_FALSE) {
        int length;
        glGetProgramiv(_rendererId, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetProgramInfoLog(_rendererId, length, &length, message);
        sage::Log::error("Linking error", message);
        glDeleteProgram(_rendererId);
        glDeleteShader(vs);
        glDeleteShader(fs);
        return;
    }
    glValidateProgram(_rendererId);

    glDetachShader(_rendererId, vs);
    glDetachShader(_rendererId, fs);
}

Shader::~Shader() {
    glDeleteProgram(_rendererId);
}

void Shader::bind() const {
    glUseProgram(_rendererId);
}

void Shader::unbind() const {
    glUseProgram(0);
}

void Shader::loadUniform(const std::string& name, const glm::mat4& mat) {
    int location = glGetUniformLocation(_rendererId, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}

}  // namespace sage