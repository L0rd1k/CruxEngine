#pragma once

#include "src/crux/render/renderer.h"
#include "src/crux/render/texture/texture.h"

namespace crux {

class Texture2DBuilder {
public:
    static crux_shared<Texture2D> create(const std::string& path) noexcept {
        switch (Renderer::getRendererType()) {
            case RendererApi::RendererType::Undefined: {
                Log::warning("Error: Selected renderer type is undefined!");
                return nullptr;
            }
            case RendererApi::RendererType::OpenGL: {
                return std::make_shared<Texture2D>(path);
            }
        }
        return nullptr;
    }
};

}  // namespace crux