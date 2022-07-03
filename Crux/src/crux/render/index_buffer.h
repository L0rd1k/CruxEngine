#pragma once

#include <inttypes.h>

namespace crux {

class IndexBuffer {
public:
    virtual ~IndexBuffer() = default;
    virtual void bind() const = 0;
    virtual void unbind() const = 0;
    virtual uint32_t getSize() const = 0;
};


}  // namespace crux