#pragma once

#include "src/crux/render/opengl/opengl_vertex_array.h"
#include "src/crux/render/opengl/opengl_vertex_buffer.h"
#include "src/crux/render/opengl/opengl_index_buffer.h"

#include "src/crux/render/renderer.h"

namespace crux {

class VertexArrayBuilder {
public:
    static VertexArray* create() noexcept {
        switch (Renderer::getRendererType()) {
            case RendererApi::RendererType::Undefined: {
                Log::warning("Error: Selected renderer type is undefined!");
                return nullptr;
            }
            case RendererApi::RendererType::OpenGL: {
                return new OpenGlVertexArray();
            }
        }
    }
};

class VertexBufferBuilder {
public:
    static VertexBuffer* create(float* vertices, uint32_t size) noexcept {
        switch (Renderer::getRendererType()) {
            case RendererApi::RendererType::Undefined: {
                Log::error("Error: Selected renderer type is undefined!");
                return nullptr;
            }
            case RendererApi::RendererType::OpenGL: {
                return new OpenGlVertexBuffer(vertices, size);
            }
        }
        return nullptr;
    }
};

class IndexBufferBuilder {
public:
    static IndexBuffer* create(uint32_t* indices, uint32_t size) {
        switch (Renderer::getRendererType()) {
            case RendererApi::RendererType::OpenGL: {
                return new OpenGlIndexBuffer(indices, size);
            }
            case RendererApi::RendererType::Undefined: {
                Log::error("Error: Selected renderer type is undefined!");
                return nullptr;
            }
            return nullptr;
        }
    }
};

}  // namespace crux