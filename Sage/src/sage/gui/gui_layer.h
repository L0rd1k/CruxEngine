#pragma once


#include "src/sage/layer/layer.h"

namespace sage {

class GuiLayer : public Layer {
public:
    GuiLayer();
    ~GuiLayer();
    virtual void onAttach() override;
    virtual void onDetach() override;
    virtual void onDraw() override;

    void begin();
    void end();
    
private:
    float _time = 0.0f;
};

}  // namespace sage