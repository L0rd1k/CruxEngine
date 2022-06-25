#pragma once

#include <algorithm>
#include <vector>

#include "layer.h"

namespace sage {

class LayerSet {
public:
    LayerSet();
    virtual ~LayerSet();

    void pushLayer(Layer* layer);
    void popLayer(Layer* layer);
    void pushOverlay(Layer* overlay);
    void popOverlay(Layer* overlay);

    std::vector<Layer*>::iterator begin() {
        return _layers.begin();
    }
    std::vector<Layer*>::iterator end() {
        return _layers.end();
    }

private:
    std::vector<Layer*> _layers;
    uint _layerInsertIdx = 0;
};

}  // namespace sage