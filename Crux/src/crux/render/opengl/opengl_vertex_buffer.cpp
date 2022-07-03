#include "opengl_vertex_buffer.h"

namespace crux {

OpenGlVertexBuffer::OpenGlVertexBuffer(float* vertices, uint32_t size) {
    /** @warning Add glCreateBuffer in newer version. **/
    glGenBuffers(1, &_rendererId);
    glBindBuffer(GL_ARRAY_BUFFER, _rendererId);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

OpenGlVertexBuffer::~OpenGlVertexBuffer() {
    glDeleteBuffers(1, &_rendererId);
}

void OpenGlVertexBuffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, _rendererId);
}

void OpenGlVertexBuffer::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

}  // namespace crux