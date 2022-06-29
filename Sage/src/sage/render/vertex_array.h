#pragma once

#include <memory>

#include "buffer.h"
#include "renderer.h"

namespace sage {

class VertexArray {
public:
    virtual ~VertexArray();
    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer> & vertexBufer) = 0;
    virtual void addIndexBuffer(const std::shared_ptr<IndexBuffer> & indexBufer) = 0;

    virtual const std::vector<std::shared_ptr<VertexBuffer>>& getVertexBuffers() const = 0;
    virtual const std::shared_ptr<IndexBuffer>& getIndexBuffer() const = 0;
 
    static VertexArray* init();
};

}  // namespace sage