#include "layer_set.h"

namespace Sage {

LayerSet::LayerSet() {
    _layerInsert = _layers.begin();
}

LayerSet::~LayerSet() {
    for(auto layer : _layers) {
        delete layer;
    }
}

void LayerSet::pushLayer(Layer* layer) {
    _layerInsert = _layers.emplace(_layerInsert, layer);
}

void LayerSet::pushOverlay(Layer* overlay) {
    _layers.emplace_back(overlay);    
}

void LayerSet::popLayer(Layer* layer) {
	auto it = std::find(_layers.begin(), _layers.end(), layer);
	if (it != _layers.end()) {
		_layers.erase(it);
		_layerInsert--;
	}
}

void LayerSet::popOverlay(Layer* overlay) {
	auto it = std::find(_layers.begin(), _layers.end(), overlay);
	if (it != _layers.end())
		_layers.erase(it);
}

}
