#include "opengl_buffer.h"

#include <glad/glad.h>

namespace sage {

//> VERTEX BUFFER

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

//> INDEX BUFFER

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

}  // namespace sage