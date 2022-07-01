#pragma once

#include "buffer_layout.h"

namespace sage {

class VertexBuffer {
public:
    virtual ~VertexBuffer() = default;
    virtual void bind() const = 0;
    virtual void unbind() const = 0;
    virtual void setLayout(const BufferLayout& layout) = 0;
    virtual const BufferLayout& getLayout() const = 0;
};

}  // namespace sage