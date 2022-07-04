#pragma once

namespace crux {

/** @brief Abstract rendering context class. **/
class RendererContext {
public:
    /** @brief Abstraction of initialization rendering context.
     * Make the context of specified window.**/
    virtual void init() = 0;

    /** @brief Abstraction of swap buffer.
     * Swaps the front and back buffers of the specified window. **/
    virtual void swapBuffer() = 0;
};

}  // namespace crux