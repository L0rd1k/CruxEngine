#pragma once

#include "buffer_layout.h"

namespace crux {

/** @brief VBO abstraction class. **/
class VertexBuffer {
public:
    /** @brief Defaultconstructor. **/
    virtual ~VertexBuffer() = default;

    /** @brief Bind Vertex Buffer Object. **/
    virtual void bind() const = 0;

    /** @brief Unbind Vertex Buffer Object. **/
    virtual void unbind() const = 0;

    virtual void setLayout(const BufferLayout& layout) = 0;
    
    virtual const BufferLayout& getLayout() const = 0;
};

}  // namespace crux