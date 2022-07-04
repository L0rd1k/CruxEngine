#pragma once

#include <memory>

#include "src/crux/core.h"

#include "vertex_buffer.h"
#include "index_buffer.h"

namespace crux {

/** @brief Abstraction class of vertex array object.(VAO)
 * @details Stores all of the state needed to supply vertex data. **/
class VertexArray {
public:
    /** @brief Constructor. **/
    virtual ~VertexArray() = default;

    /** @brief Abstraction of binding a VAO. **/
    virtual void bind() const = 0;

    /** @brief Abstraction of VAO unbinding. **/
    virtual void unbind() const = 0;

    /** @brief Abstraction of enabling a generic VAO.
     * @param[in] vertexBufer Pointer to VBO class. **/
    virtual void addVertexBuffer(const crux_shared<VertexBuffer>& vertexBufer) = 0;

    /** @brief Abstraction of enabling VBO indexing .
     * @param[in] vertexBufer Pointer to index buffer class. **/
    virtual void addIndexBuffer(const crux_shared<IndexBuffer>& indexBufer) = 0;

    /** @brief Abstraction of getting list of used VBO. **/
    virtual const std::vector<crux_shared<VertexBuffer>>& getVertexBuffers() const = 0;

    /** @brief Abstraction of used Index Buffer . **/
    virtual const crux_shared<IndexBuffer>& getIndexBuffer() const = 0;

};

}  // namespace crux