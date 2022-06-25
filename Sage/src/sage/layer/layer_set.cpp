#include "layer_set.h"

namespace sage {

LayerSet::LayerSet()
    : _layerInsertIdx(0) {
}

LayerSet::~LayerSet() {
    for (auto layer : _layers) {
        delete layer;
    }
}

void LayerSet::pushLayer(Layer* layer) {
    _layers.emplace(_layers.begin() + _layerInsertIdx, layer);
    _layerInsertIdx++;
}

void LayerSet::pushOverlay(Layer* overlay) {
    _layers.emplace_back(overlay);
}

void LayerSet::popLayer(Layer* layer) {
    auto it = std::find(_layers.begin(), _layers.end(), layer);
    if (it != _layers.end()) {
        _layers.erase(it);
        _layerInsertIdx--;
    }
}

void LayerSet::popOverlay(Layer* overlay) {
    auto it = std::find(_layers.begin(), _layers.end(), overlay);
    if (it != _layers.end())
        _layers.erase(it);
}

}  // namespace sage
