#pragma once

#include <inttypes.h>
#include <glad/glad.h>

#include "src/crux/render/index_buffer.h"

namespace crux {

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

}  // namespace crux