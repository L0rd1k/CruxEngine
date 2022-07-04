#include "opengl_vertex_array.h"


namespace crux {

static GLenum ShaderTypetoGLType(ShaderType type) {
    switch (type) {
        case crux::ShaderType::fVec:
            return GL_FLOAT;
        case crux::ShaderType::fVec2:
            return GL_FLOAT;
        case crux::ShaderType::fVec3:
            return GL_FLOAT;
        case crux::ShaderType::fVec4:
            return GL_FLOAT;
        case crux::ShaderType::Mat3:
            return GL_FLOAT;
        case crux::ShaderType::Mat4:
            return GL_FLOAT;
        case crux::ShaderType::iVec:
            return GL_INT;
        case crux::ShaderType::iVec2:
            return GL_INT;
        case crux::ShaderType::iVec3:
            return GL_INT;
        case crux::ShaderType::iVec4:
            return GL_INT;
        case crux::ShaderType::Bool:
            return GL_BOOL;
        default: {
            crux::Log::warning("Unknown shader data type(converter)");
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

void OpenGlVertexArray::addVertexBuffer(const crux_shared<VertexBuffer>& vertexBufer) {
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

void OpenGlVertexArray::addIndexBuffer(const crux_shared<IndexBuffer>& indexBufer) {
    glBindVertexArray(_rendererId);
    //> Assign index buffer to current vertex array.
    indexBufer->bind();
    _indexBuffer = indexBufer;
}

const std::vector<crux_shared<VertexBuffer>>& OpenGlVertexArray::getVertexBuffers() const {
    return _vertexBuffer;
}

const crux_shared<IndexBuffer>& OpenGlVertexArray::getIndexBuffer() const {
    return _indexBuffer;
}

}  // namespace crux