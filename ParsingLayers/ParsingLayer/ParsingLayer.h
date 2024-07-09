#ifndef BACHELOR_THESIS_PARSINGLAYER_H
#define BACHELOR_THESIS_PARSINGLAYER_H
#include "../../AtomicParsingOp/AtomicParsingOp.h"
#include "../ParsingLayers.h"
#include <iostream>
#include <vector>

enum Associativity {
    RIGHT,
    LEFT,
    NONE
};

class ParsingLayers;
class AtomicParsingOp;

class ParsingLayer
{
public:
    ParsingLayer( Associativity associativity ) : associativity( associativity ) {};

    ParsingLayer& addOperator( const AtomicParsingOp& op );

   bool parse(ParsingLayers &layers, ParsedStorage &storage, Tokenizer &tokenizer, size_t layerIndex = 0) const;

   Associativity getAssociativity() const;

private:
    std::vector < AtomicParsingOp > operators;
    Associativity associativity;
};


#endif //BACHELOR_THESIS_PARSINGLAYER_H
