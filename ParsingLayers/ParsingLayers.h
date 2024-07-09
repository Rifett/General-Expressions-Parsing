#ifndef BACHELOR_THESIS_PARSINGLAYERS_H
#define BACHELOR_THESIS_PARSINGLAYERS_H
#include "ParsingLayer/ParsingLayer.h"
#include <iostream>
#include <optional>

class ParsingLayer;

class ParsingLayers
{
public:
    ParsingLayers& addLayer( const ParsingLayer& layer );

    const ParsingLayer* getUpperLayer ( ) const;

    const ParsingLayer* getLayer ( size_t index ) const;

private:
    std::vector < ParsingLayer > layersCollection;
};


#endif //BACHELOR_THESIS_PARSINGLAYERS_H
