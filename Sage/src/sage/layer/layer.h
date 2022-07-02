#pragma once

#include <string>

#include "src/sage/events/event.h"
#include "src/sage/core/timestep.h"

namespace sage {

class Layer {
    
public:
    Layer(const std::string& name = "DefaultLayer");
    virtual ~Layer();
    virtual void onAttach() {
    }
    virtual void onDetach() {
    }
    virtual void onUpdate(Timestep ts) {
    }
    virtual void onDraw() {
    }
    virtual void onEvent(Event& e) {
    }
    inline const std::string& getName() const {
        return _layerName;
    }
protected:
    std::string _layerName;
};

}  // namespace sage