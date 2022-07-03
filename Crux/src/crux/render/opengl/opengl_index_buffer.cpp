#include "opengl_index_buffer.h"

namespace crux {

OpenGlIndexBuffer::OpenGlIndexBuffer(uint32_t* indices, uint32_t size)
    : _size(size) {
    /** @warning Add glCreateBuffer in newer version. **/
    glGenBuffers(1, &_rendererId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rendererId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}

OpenGlIndexBuffer::~OpenGlIndexBuffer() {
    glDeleteBuffers(1, &_rendererId);
}

void OpenGlIndexBuffer::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rendererId);
}

void OpenGlIndexBuffer::unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

}  // namespace crux