#include "opengl_shader.h"

namespace crux {

OpenGlShader::OpenGlShader(const std::string& vertex, const std::string& fragment) {
    createShader(vertex, fragment);
}

OpenGlShader::~OpenGlShader() {
    glDeleteProgram(_rendererId);
}

void OpenGlShader::bind() const {
    glUseProgram(_rendererId);
}

void OpenGlShader::unbind() const {
    glUseProgram(0);
}

uint32_t OpenGlShader::getShaderProgram() {
    return _rendererId;
}

void OpenGlShader::createShader(const std::string& vertexShader, const std::string& fragmentShader) {
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
        crux::Log::error("Linking error", message);
        glDeleteProgram(_rendererId);
        glDeleteShader(vs);
        glDeleteShader(fs);
        return;
    }
    glValidateProgram(_rendererId);

    glDetachShader(_rendererId, vs);
    glDetachShader(_rendererId, fs);
}

unsigned int OpenGlShader::compileShader(unsigned int type, const std::string& source) {
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
        crux::Log::error("Compilation error: ", (type == GL_VERTEX_SHADER ? "vertex " : "fragment "));
        crux::Log::error(message);
        glDeleteShader(id);
        return 0;
    }
    return id;
}

void OpenGlShader::loadUniformInt(const std::string& name, int value) {
    int location = glGetUniformLocation(_rendererId, name.c_str());
    glUniform1f(location, value);
}

void OpenGlShader::loadUniformFloat(const std::string& name, int value) {
    int location = glGetUniformLocation(_rendererId, name.c_str());
    glUniform1f(location, value);
}

void OpenGlShader::loadUniformFloat2(const std::string& name, const glm::vec2& value) {
    int location = glGetUniformLocation(_rendererId, name.c_str());
    glUniform2f(location, value.x, value.y);
}

void OpenGlShader::loadUniformFloat3(const std::string& name, const glm::vec3& value) {
    int location = glGetUniformLocation(_rendererId, name.c_str());
    glUniform3f(location, value.x, value.y, value.z);
}

void OpenGlShader::loadUniformFloat4(const std::string& name, const glm::vec4& value) {
    int location = glGetUniformLocation(_rendererId, name.c_str());
    glUniform4f(location, value.x, value.y, value.z, value.w);
}

void OpenGlShader::loadUniformMat3(const std::string& name, const glm::mat3& matrix) {
    int location = glGetUniformLocation(_rendererId, name.c_str());
    glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void OpenGlShader::loadUniformMat4(const std::string& name, const glm::mat4& matrix) {
    int location = glGetUniformLocation(_rendererId, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

}  // namespace crux