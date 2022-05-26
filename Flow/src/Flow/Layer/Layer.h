#pragma once

#include <string>

#include "../Events/Event.h"

namespace Flow {

class Layer {
public:
    Layer(const std::string& name = "Layer");
    virtual ~Layer();

    virtual void onAttach() {}
    virtual void onDetach() {}
    virtual void onUpdate() {}
    virtual void onEvent(Event& e) {}

    inline const std::string& getName() const {
        return _layerName;
    }

protected:
    std::string _layerName;
};

}  // namespace Flow