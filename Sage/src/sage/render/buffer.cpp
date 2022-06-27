#include "buffer.h"

#include "src/sage/render/opengl/opengl_buffer.h"

namespace sage {

/** VERTEX BUFFER **/

VertexBuffer::~VertexBuffer() {
}

VertexBuffer* VertexBuffer::init(float* vertices, uint32_t size) {
    switch (Renderer::getRendererType()) {
        case RendererType::OpenGL: {
            return new OpenGlVertexBuffer(vertices, size);
        }
        case RendererType::Undefined: {
            Log::error("Error: Selected renderer type is undefined!");
            return nullptr;
        }
    }
    return nullptr;
}

/** INDEX BUFFER **/

IndexBuffer::~IndexBuffer() {
}

IndexBuffer* IndexBuffer::init(uint32_t* indices, uint32_t size) {
    switch (Renderer::getRendererType()) {
        case RendererType::OpenGL: {
            return new OpenGlIndexBuffer(indices, size);
        }
        case RendererType::Undefined: {
            Log::error("Error: Selected renderer type is undefined!");
            return nullptr;
        }
    }
    return nullptr;
}

}  // namespace sage