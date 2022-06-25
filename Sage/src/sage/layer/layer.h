#pragma once

#include <string>

#include "../events/event.h"

namespace sage {

class Layer {
    
public:
    Layer(const std::string& name = "DefaultLayer");
    virtual ~Layer();
    virtual void onAttach() {
    }
    virtual void onDetach() {
    }
    virtual void onUpdate() {
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