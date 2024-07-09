#include "ParsingLayers.h"

const ParsingLayer* ParsingLayers::getUpperLayer() const {
    if (layersCollection.empty()) return nullptr;
    return &layersCollection.front();
}

const ParsingLayer* ParsingLayers::getLayer(size_t index) const {
    if ( index >= layersCollection.size() ) return nullptr;
    return &layersCollection.at(index);
}

ParsingLayers& ParsingLayers::addLayer(const ParsingLayer &layer) {
    layersCollection . push_back( layer );
    return *this;
}
