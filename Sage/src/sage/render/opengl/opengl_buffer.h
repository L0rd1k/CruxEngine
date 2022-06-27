#pragma once

#include "src/sage/render/buffer.h"

namespace sage {

class OpenGlVertexBuffer : public VertexBuffer {
public:
    OpenGlVertexBuffer(float* vertices, uint32_t size);
    virtual ~OpenGlVertexBuffer();
    virtual void bind() const;
    virtual void unbind() const;

private:
    uint32_t _rendererId;
};


class OpenGlIndexBuffer : public IndexBuffer {
public:
    OpenGlIndexBuffer(uint32_t* indices, uint32_t size);
    virtual ~OpenGlIndexBuffer();
    virtual void bind() const;
    virtual void unbind() const;

    virtual uint32_t getSize() const { return _size; };
private:
    unsigned int _rendererId;
    uint32_t _size;
};

}  // namespace sage