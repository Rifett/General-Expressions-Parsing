#ifndef BACHELOR_THESIS_ATOMICPARSINGOP_H
#define BACHELOR_THESIS_ATOMICPARSINGOP_H
#include "../Tokenizer/Tokenizer.h"
#include "../ParsedStorage/ParsedStorage.h"
#include "../ParsingLayers/ParsingLayers.h"
#include <utility>
#include <vector>

class ParsingLayers;
class ParsingLayer;

class AtomicParsingOp
{
public:
    AtomicParsingOp( std::vector < Token > tokens, bool left, bool right) : tokens( std::move(tokens) ), left( left ), right( right ) {};

    bool parse ( ParsingLayers &layers, ParsedStorage &storage, Tokenizer &tokenizer, size_t layerIndex ) const;

private:
    bool hasLeftOperand() const;
    bool hasRightOperand() const;

    static bool parseInnerLayer( ParsingLayers &layers, ParsedStorage &storage, Tokenizer &tokenizer, size_t layerIndex, const ParsingLayer * layer ) ;
    static bool parseInnerToken( ParsedStorage &storage, Tokenizer &tokenizer, Token token ) ;

    bool right;
    bool left;
    std::vector< Token > tokens;
};


#endif //BACHELOR_THESIS_ATOMICPARSINGOP_H
