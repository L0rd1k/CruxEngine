#pragma once

#include "src/sage/core.h"

#include <utility>

namespace sage {

class Input {
public:
    inline static bool isKeyPressed(int keyCode) {
        return _keyInstance->impl_isKeyPressed(keyCode);
    }
    inline static bool isMouseButtonPressed(int keyCode) {
        return _keyInstance->impl_isMouseButtonPresed(keyCode);
    }
    inline static float getMouseX() {
        return _keyInstance->impl_getMouseX();
    }
    inline static float getMouseY() {
        return _keyInstance->impl_getMouseY();
    }
    inline static std::pair<float, float> getMousePos() {
        return _keyInstance->impl_getMousePos();
    }

protected:
    virtual bool impl_isKeyPressed(int keyCode) = 0;
    virtual bool impl_isMouseButtonPresed(int keyCode) = 0;
    virtual float impl_getMouseX() = 0;
    virtual float impl_getMouseY() = 0;
    virtual std::pair<float, float> impl_getMousePos() = 0;

private:
    static Input* _keyInstance;
};

}  // namespace sage