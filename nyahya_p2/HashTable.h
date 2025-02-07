#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "FileBlock.h"
#include <vector>

class HashTable {
private:
    unsigned int table_size; //hash table
    bool use_chaining; //if true, use chaining method
    std::vector<FileBlock*> table; //open addressing table
    std::vector<std::vector<FileBlock>> chains; //chains for chaining
    unsigned int primary_hash(unsigned int key) const; //hash func 1
    unsigned int secondary_hash(unsigned int key) const; //hash func 2 for double hashing

public:
    HashTable(unsigned int size, bool use_chaining); //constructor
    ~HashTable(); //destructor
    bool store(unsigned int id, const std::string& data); //stores file block
    bool search(unsigned int id, unsigned int& position) const; //finds file block
    bool remove(unsigned int id); //removes file block
    bool corrupt(unsigned int id, const std::string& data); //corrupts block data
    bool validate(unsigned int id) const; //validates checksum
    bool is_chaining() const; //check if chaining
    bool print_chain(int index) const; //prints chain
};
#endif
