#include "ParsingLayer.h"

bool ParsingLayer::parse(ParsingLayers &layers, ParsedStorage &storage, Tokenizer &tokenizer, size_t layerIndex) const {
    for ( auto op = operators . begin(); op != operators . end(); ) {
        if ( op -> parse( layers, storage, tokenizer, layerIndex ) ) {
            if ( associativity != LEFT && storage . isPacked() ) return true;
            op = operators.begin();
        } else
            ++op;
        storage . resetPosition();
    }

    auto nextLayer = layers . getLayer( layerIndex + 1 );
    return storage.isPacked() || ( nextLayer && nextLayer->parse(layers, storage, tokenizer, layerIndex + 1) );
}

Associativity ParsingLayer::getAssociativity() const {
    return associativity;
}

ParsingLayer& ParsingLayer::addOperator(const AtomicParsingOp &op) {
    operators . push_back( op );
    return *this;
}
