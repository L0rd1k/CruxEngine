#pragma once

#include <vector>
#include <cassert>
#include <glad/glad.h>

#include "src/crux/render/vertex_array.h"

namespace crux {

class OpenGlVertexArray : public VertexArray {
public:
    OpenGlVertexArray();
    virtual ~OpenGlVertexArray();
    virtual void bind() const override;
    virtual void unbind() const override;

    virtual void addVertexBuffer(const crux_shared<VertexBuffer> & vertexBufer) override;
    virtual void addIndexBuffer(const crux_shared<IndexBuffer> & indexBufer) override;

    virtual const std::vector<crux_shared<VertexBuffer>>& getVertexBuffers() const override;
    virtual const crux_shared<IndexBuffer>& getIndexBuffer() const override;
private:
    std::vector<crux_shared<VertexBuffer>> _vertexBuffer;
    crux_shared<IndexBuffer> _indexBuffer;
    uint32_t _rendererId;
};

}  // namespace crux