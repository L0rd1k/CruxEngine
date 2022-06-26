#pragma once

namespace sage {

class RendererContext {
public:
    virtual void init() = 0;
    virtual void swapBuffer() = 0;
};

}  // namespace sage