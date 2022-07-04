#pragma once

#include <array>
#include <cassert>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <sstream>
#include <string>
#include <vector>

#include "src/crux/utils/logger/log.h"

namespace crux {

/** @brief Avaliable shader types. **/
enum class ShaderFormat {
    VERTEX = 0,      //> Vertex shader
    FRAGMENT = 1,    //> Fragment shader
    UNDEFINED = 255  //> Shader type not defined
};

/** @brief Shader sources data. **/
struct ShaderData {
    std::string VertexData;    //> Vertex source
    std::string FragmentData;  //> Fragment source
};

/** @brief Abstract shader class. **/
class Shader {
public:
    /** @brief Shader destructor. **/
    virtual ~Shader() = default;

    /** @brief Abstract shader binding. **/
    virtual void bind() const = 0;

    /** @brief Abstract shader unbinding. **/
    virtual void unbind() const = 0;

    /** @brief Parse single shader file to vertex and fragment sources.
     * @param[in] path Path to shader source file.
     * @return Return shader data(vertex and fragment sources). **/
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