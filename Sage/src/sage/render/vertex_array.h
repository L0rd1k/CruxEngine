#pragma once

#include <memory>

#include "vertex_buffer.h"
#include "index_buffer.h"

namespace sage {

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
    virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBufer) = 0;

    /** @brief Abstraction of enabling VBO indexing .
     * @param[in] vertexBufer Pointer to index buffer class. **/
    virtual void addIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBufer) = 0;

    /** @brief Abstraction of getting list of used VBO. **/
    virtual const std::vector<std::shared_ptr<VertexBuffer>>& getVertexBuffers() const = 0;

    /** @brief Abstraction of used Index Buffer . **/
    virtual const std::shared_ptr<IndexBuffer>& getIndexBuffer() const = 0;

};

}  // namespace sage