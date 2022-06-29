#include "opengl_vertex_array.h"

#include <glad/glad.h>

namespace sage {

static GLenum ShaderTypetoGLType(ShaderType type) {
    switch (type) {
        case sage::ShaderType::fVec:
            return GL_FLOAT;
        case sage::ShaderType::fVec2:
            return GL_FLOAT;
        case sage::ShaderType::fVec3:
            return GL_FLOAT;
        case sage::ShaderType::fVec4:
            return GL_FLOAT;
        case sage::ShaderType::Mat3:
            return GL_FLOAT;
        case sage::ShaderType::Mat4:
            return GL_FLOAT;
        case sage::ShaderType::iVec:
            return GL_INT;
        case sage::ShaderType::iVec2:
            return GL_INT;
        case sage::ShaderType::iVec3:
            return GL_INT;
        case sage::ShaderType::iVec4:
            return GL_INT;
        case sage::ShaderType::Bool:
            return GL_BOOL;
        default: {
            sage::Log::warning("Unknown shader data type(converter)");
            return 0;
        }
    }
    return 0;
}

OpenGlVertexArray::OpenGlVertexArray() {
    /** @warning Replace with glCreateVertexArray. **/
    glGenVertexArrays(1, &_rendererId);
}

OpenGlVertexArray::~OpenGlVertexArray() {
    glDeleteVertexArrays(1, &_rendererId);
}

void OpenGlVertexArray::bind() const {
    glBindVertexArray(_rendererId);
}

void OpenGlVertexArray::unbind() const {
    glBindVertexArray(0);
}

void OpenGlVertexArray::addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBufer) {
    assert(vertexBufer->getLayout().getElements().size() && "Vertex buffer doesn't have layout");

    glBindVertexArray(_rendererId);
    vertexBufer->bind();

    uint32_t index = 0;
    const auto& layout = vertexBufer->getLayout();
    for (const auto& elem : layout) {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index,
                              elem.getElementsCount(),
                              ShaderTypetoGLType(elem.type),
                              elem.normalized ? GL_TRUE : GL_FALSE,
                              layout.getStride(),
                              reinterpret_cast<const void*>(elem.offset));
        index++;
    }
    _vertexBuffer.push_back(vertexBufer);
}

void OpenGlVertexArray::addIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBufer) {
    glBindVertexArray(_rendererId);
    //> Assign index buffer to current vertex array.
    indexBufer->bind();
    _indexBuffer = indexBufer;
}

const std::vector<std::shared_ptr<VertexBuffer>>& OpenGlVertexArray::getVertexBuffers() const {
    return _vertexBuffer;
}

const std::shared_ptr<IndexBuffer>& OpenGlVertexArray::getIndexBuffer() const {
    return _indexBuffer;
}

}  // namespace sage