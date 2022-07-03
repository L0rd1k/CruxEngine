#pragma once

#include "src/crux/inputs/input.h"

namespace crux {

class LinuxInput : public Input {
protected:
    virtual bool impl_isKeyPressed(int keyCode) override;
    virtual bool impl_isMouseButtonPresed(int keyCode) override;
    virtual float impl_getMouseX() override;
    virtual float impl_getMouseY() override;
    virtual std::pair<float, float> impl_getMousePos() override;
};

}  // namespace crux