#ifndef BACHELOR_THESIS_TABLEPARSER_H
#define BACHELOR_THESIS_TABLEPARSER_H
#include "../ParsingLayers/ParsingLayers.h"
#include <iostream>
#include <utility>
#include <vector>


class TableParser
{
public:
    TableParser( ParsingLayers layers ) : layers( std::move(layers) ) {};

    bool parse ( const std::string& input );

    bool compareStorage( const ParsedStorage& otherStorage );

private:
    ParsingLayers layers;
    ParsedStorage parsedAST;
    Tokenizer tokenizer;
};


#endif //BACHELOR_THESIS_TABLEPARSER_H
