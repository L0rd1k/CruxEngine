#pragma once

#include "src/crux/render/vertex_buffer.h"

#include <glad/glad.h>

namespace crux {

class OpenGlVertexBuffer : public VertexBuffer {
public:
    OpenGlVertexBuffer(float* vertices, uint32_t size);
    virtual ~OpenGlVertexBuffer();
    virtual void bind() const override;
    virtual void unbind() const override;

    virtual void setLayout(const BufferLayout& layout) override {
        _layout = layout;
    }
    virtual const BufferLayout& getLayout() const override {
        return _layout;
    }

private:
    uint32_t _rendererId;
    BufferLayout _layout;
};

}  // namespace crux