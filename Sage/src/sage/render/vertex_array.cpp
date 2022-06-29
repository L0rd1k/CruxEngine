#include "vertex_array.h"

#include "src/sage/render/opengl/opengl_vertex_array.h"

namespace sage {

VertexArray::~VertexArray() {
}

void VertexArray::bind() const {
}

void VertexArray::unbind() const {
}

VertexArray* VertexArray::init() {
    switch(Renderer::getRendererType()) {
        case RendererType::Undefined: {
            Log::warning("Error: Selected renderer type is undefined!");
            return nullptr;
        }
        case RendererType::OpenGL: {
            return new OpenGlVertexArray();
        }
    }
    return nullptr;
}

}  // namespace sage