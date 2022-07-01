#pragma once

#include <glm/glm.hpp>
#include <memory>

#include "vertex_array.h"

namespace sage {

/** @brief Renderer abstraction api. **/
class RendererApi {
public:
    /** @brief List os available renderer types. **/
    enum class RendererType {
        Undefined = 0,
        OpenGL = 1,
    };
public:
    /** @brief Abstraction for buffers to be cleared. **/
    virtual void clear() = 0;

    /** @brief Abstraction for specifying clear values for the color buffers.
     * @param[in] color  Vector of red, green, blue, and alpha values. **/
    virtual void clearColor(const glm::vec4& color) = 0;

    /** @brief Abstraction for render primitives from array data. **/
    virtual void drawIndexed(const std::shared_ptr<VertexArray>& vao) = 0;

    /** @brief Get currently used render API type. **/
    inline static RendererType getAPI() {
        return _api;
    }

private:
    static RendererType _api;  //> Currently use renderer api type.
};

}  // namespace sage