#include "TableParser.h"

bool TableParser::parse( const std::string& input ) {
    tokenizer  = Tokenizer ( input );
    tokenizer . initialize();
    parsedAST . clear();
    bool res = false;
    try {
        res = layers . getUpperLayer() && layers . getUpperLayer() -> parse( layers, parsedAST, tokenizer );
    } catch (const std::logic_error &error) {
        return false;
    }
    return res && tokenizer . tokenizationComplete();
}

bool TableParser::compareStorage(const ParsedStorage &otherStorage) {
    return this -> parsedAST == otherStorage;
}
