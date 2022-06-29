#pragma once

#include <vector>
#include <cassert>

#include "src/sage/render/vertex_array.h"

namespace sage {

class OpenGlVertexArray : public VertexArray {
public:
    OpenGlVertexArray();
    virtual ~OpenGlVertexArray();
    virtual void bind() const override;
    virtual void unbind() const override;

    virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer> & vertexBufer) override;
    virtual void addIndexBuffer(const std::shared_ptr<IndexBuffer> & indexBufer) override;

    virtual const std::vector<std::shared_ptr<VertexBuffer>>& getVertexBuffers() const override;
    virtual const std::shared_ptr<IndexBuffer>& getIndexBuffer() const override;
private:
    std::vector<std::shared_ptr<VertexBuffer>> _vertexBuffer;
    std::shared_ptr<IndexBuffer> _indexBuffer;
    uint32_t _rendererId;
};

}  // namespace sage