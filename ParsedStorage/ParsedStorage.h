#ifndef BACHELOR_THESIS_PARSEDSTORAGE_H
#define BACHELOR_THESIS_PARSEDSTORAGE_H
#include <vector>
#include <optional>
#include <variant>
#include "../Tokenizer/Tokenizer.h"
#define STORAGE 0
#define TOKEN 1


//TODO -> Maybe utilize moving semantics in some places? ( after the tests are written, in order not to break anything )
class ParsedStorage
{
public:
    ParsedStorage& pushBack(const ParsedStorage &storage);

    ParsedStorage& pushBack(Token token);

    bool operator== ( const ParsedStorage& other) const;

    void clear();

    void resetPosition();

    bool matchSubstorage();

    bool match(Token token);

    bool reparsed() const;

    bool empty();

    ParsedStorage& pack();

    bool isPacked();

    ParsedStorage getPackedStorage();

private:
    std::vector < std::variant < ParsedStorage, Token > > storage;
    size_t storageIndex = 0;
};


#endif //BACHELOR_THESIS_PARSEDSTORAGE_H
