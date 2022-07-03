#pragma once

#include "src/crux/render/opengl/opengl_shader.h"
#include "src/crux/render/renderer.h"

namespace crux {

class ShaderBuilder {
public:
    static Shader* create(const std::string& vertex, const std::string& fragment) noexcept {
        switch (Renderer::getRendererType()) {
            // case RendererType::Undefined: {
            case RendererApi::RendererType::Undefined: {
                Log::warning("Error: Selected renderer type is undefined!");
                return nullptr;
            }
            case RendererApi::RendererType::OpenGL: {
                return new OpenGlShader(vertex, fragment);
            }
        }
        return nullptr;
    }
};

}  // namespace crux