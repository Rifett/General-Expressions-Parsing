#include <stdexcept>
#include "ParsedStorage.h"

void ParsedStorage::clear() {
    storage . clear();
    storageIndex = 0;
}

void ParsedStorage::resetPosition() {
    if ( storage . empty() ) return;
    storageIndex = 0;
}

bool ParsedStorage::reparsed() const {
    return storageIndex == storage . size();
}

bool ParsedStorage::match(Token token) {
    if ( this -> reparsed() ) return false;
    if ( storage . at( storageIndex ) . index() == TOKEN ) {
        if ( get < Token > ( storage . at( storageIndex ) ) != token ) return false;
        ++storageIndex;
        return true;
    }
    return false;
}

bool ParsedStorage::matchSubstorage() {
    if ( this -> reparsed() ) return false;
    if ( storage . at( storageIndex ) . index() == STORAGE ) {
        ++storageIndex;
        return true;
    }
    return false;
}

ParsedStorage& ParsedStorage::pushBack(Token token) {
    if ( !this -> reparsed() ) throw std::runtime_error("Attempt to push into not fully reparsed storage");
    if ( !storage . empty() && storage . back() . index() == TOKEN )
        throw std::runtime_error("Attempt to push two tokens in a row!");
    storage . emplace_back( token );
    ++storageIndex;
    return *this;
}

ParsedStorage& ParsedStorage::pushBack(const ParsedStorage& storage) {
    if ( !this -> reparsed() ) throw std::runtime_error("Attempt to push into not fully reparsed storage");
    if ( !this -> storage . empty() && this -> storage . back() . index() == STORAGE )
        throw std::runtime_error("Attempt to push two storages in a row!");
    this -> storage . emplace_back( storage );
    ++storageIndex;
    return *this;
}

bool ParsedStorage::empty() {
    return storage.empty();
}

ParsedStorage& ParsedStorage::pack() {
    auto packedCopy = ParsedStorage() . pushBack( * this );
    std::swap( *this, packedCopy );
    this -> resetPosition();
    return *this;
}

bool ParsedStorage::isPacked() {
    return storage.size() == 1 && storage.front().index() == STORAGE;
}

ParsedStorage ParsedStorage::getPackedStorage() {
    if ( this -> isPacked() )
        return get < ParsedStorage >( storage . front() );
    else
        throw std::runtime_error("Attempt to get packed inner storage of some unpacked storage.");
}

bool ParsedStorage::operator==(const ParsedStorage &other) const {
    return  other . storage == this -> storage;
}
