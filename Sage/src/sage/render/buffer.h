#pragma once

#include <inttypes.h>
#include "src/sage/render/renderer.h"
#include "src/sage/utils/logger/log.h"


namespace sage {

class VertexBuffer {
public:
    virtual ~VertexBuffer();
    virtual void bind() const = 0;
    virtual void unbind() const = 0;
    static VertexBuffer* init(float* vertices, uint32_t size);
};

class IndexBuffer {
public:
    virtual ~IndexBuffer();
    virtual void bind() const = 0;
    virtual void unbind() const = 0;
    virtual uint32_t getSize() const = 0;
    static IndexBuffer* init(uint32_t* indices, uint32_t size);
};

}  // namespace sage