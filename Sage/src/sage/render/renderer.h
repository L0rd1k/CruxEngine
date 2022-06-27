#pragma once

namespace sage {

enum class RendererType {
    Undefined = 0,
    OpenGL = 1,
};

class Renderer {
public:
    inline static RendererType getRendererType() {
        return _rendererType;
    }
private:
    static RendererType _rendererType;
};

}  // namespace sage