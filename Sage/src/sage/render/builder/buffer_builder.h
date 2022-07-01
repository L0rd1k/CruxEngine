#pragma once

#include "src/sage/render/opengl/opengl_vertex_array.h"
#include "src/sage/render/opengl/opengl_vertex_buffer.h"
#include "src/sage/render/opengl/opengl_index_buffer.h"

#include "src/sage/render/renderer.h"

// #include "src/sage/render/renderer_api.h"

namespace sage {

class VertexArrayBuilder {
public:
    static VertexArray* create() noexcept {
        switch (Renderer::getRendererType()) {
            // case RendererType::Undefined: {
            case RendererApi::RendererType::Undefined: {
                Log::warning("Error: Selected renderer type is undefined!");
                return nullptr;
            }
            case RendererApi::RendererType::OpenGL: {
            // case RendererType::OpenGL: {
                return new OpenGlVertexArray();
            }
        }
    }
};

class VertexBufferBuilder {
public:
    static VertexBuffer* create(float* vertices, uint32_t size) noexcept {
        switch (Renderer::getRendererType()) {
            // case RendererType::Undefined: {
            case RendererApi::RendererType::Undefined: {
                Log::error("Error: Selected renderer type is undefined!");
                return nullptr;
            }
            // case RendererType::OpenGL: {
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
            // case RendererType::OpenGL: {
            case RendererApi::RendererType::OpenGL: {
                return new OpenGlIndexBuffer(indices, size);
            }
            // case RendererType::Undefined: {
            case RendererApi::RendererType::Undefined: {
                Log::error("Error: Selected renderer type is undefined!");
                return nullptr;
            }
            return nullptr;
        }
    }
};

}  // namespace sage