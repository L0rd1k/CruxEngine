#pragma once

namespace crux {

class RendererContext {
public:
    virtual void init() = 0;
    virtual void swapBuffer() = 0;
};

}  // namespace crux