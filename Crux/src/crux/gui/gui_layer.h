#pragma once


#include "src/crux/layer/layer.h"

namespace crux {

class GuiLayer : public Layer {
public:
    GuiLayer();
    virtual ~GuiLayer();
    virtual void onAttach() override;
    virtual void onDetach() override;
    virtual void onDraw() override;

    void begin();
    void end();
    
private:
    float _time = 0.0f;
};

}  // namespace crux