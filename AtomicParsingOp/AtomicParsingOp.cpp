#include "AtomicParsingOp.h"
#include "../ParsedStorage/ParsedStorage.h"


bool AtomicParsingOp::parse(ParsingLayers &layers, ParsedStorage &storage, Tokenizer &tokenizer, size_t layerIndex) const {
    auto upperLayer = layers.getUpperLayer(), nextLayer = layers.getLayer(layerIndex + 1);

    //Parse optional left operand
    if ( this -> hasLeftOperand() ) {
        bool storageWasEmpty = storage . empty();
        if ( !nextLayer ) throw std::runtime_error("Wrong expression format: operator has left operand at the last layer.");
        if ( !parseInnerLayer( layers, storage, tokenizer, layerIndex + 1, nextLayer ) ) {
            if ( storageWasEmpty && !storage . empty() )
                return true;
            else
                return false;
        }
    }

    //Parse necessary first token
    if ( !parseInnerToken( storage, tokenizer, tokens.front() ) )
        return false;

    //Parse middle part
    for (size_t tokenPos = 1; tokenPos < tokens.size(); ++tokenPos) {
        if ( !parseInnerLayer( layers, storage, tokenizer, 0, upperLayer ) || !parseInnerToken( storage, tokenizer, tokens . at( tokenPos ) ) )
            return false;
    }

    //Parse optional right operand
    if ( this -> hasRightOperand() ) {
        switch ( layers . getLayer( layerIndex ) -> getAssociativity() ) {
            case RIGHT:
                if ( !parseInnerLayer( layers, storage, tokenizer, layerIndex, layers . getLayer( layerIndex ) ) )
                    return false;
                break;
            default:
                if ( !parseInnerLayer( layers, storage, tokenizer, layerIndex + 1, nextLayer ) )
                    return false;
        }
    }

    //Mark completion of the storage
    storage.pack();
    return true;
}

bool AtomicParsingOp::hasLeftOperand() const {
    return left;
}

bool AtomicParsingOp::hasRightOperand() const {
    return right;
}

bool AtomicParsingOp::parseInnerLayer(ParsingLayers &layers, ParsedStorage &storage, Tokenizer &tokenizer, size_t layerIndex, const ParsingLayer *layer) {
    ParsedStorage exploringStorage;
    if ( storage . reparsed() ) {
        if ( layer -> parse( layers, exploringStorage, tokenizer, layerIndex ) ) {
            storage . pushBack( exploringStorage . getPackedStorage() );
        } else {
            if ( storage.empty() ) {
                std::swap( storage, exploringStorage );
                return false;
            } else {
                throw std::logic_error("Parsing error while having something in the storage -> two unfinished storages -> parsing failed.");
            }
        }
    } else {
        return storage . matchSubstorage();
    }

    return true;
}

bool AtomicParsingOp::parseInnerToken(ParsedStorage &storage, Tokenizer &tokenizer, Token token) {
    if ( storage . reparsed() ) {
        if ( !tokenizer . tokenMatch( token ) )
            return false;
        storage . pushBack( token );
    } else {
        return storage . match( token );
    }

    return true;
}
