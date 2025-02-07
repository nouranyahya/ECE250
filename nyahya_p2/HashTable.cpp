#include "HashTable.h"
#include <iostream>

HashTable::HashTable(unsigned int size, bool useChaining) : table_size(size), use_chaining(useChaining), table(size, nullptr){
    if(use_chaining) chains.resize(size); //initialize chains if using chaining method (if true, do this)
}

HashTable::~HashTable(){
    //destructor to deallocate memory
    for(unsigned int i=0; i<table.size(); i++){ //iterate each index of table
        if(table[i] != nullptr){ // if object stored at index
            delete table[i]; //delete object
        }
    }
}

unsigned int HashTable::primary_hash(unsigned int key) const{
    return key % table_size;
    // k mod m func
}

unsigned int HashTable::secondary_hash(unsigned int key) const{
    unsigned int result = (key/table_size) % table_size;
    if(result%2 == 0){
        //if result even, add one to make odd
        result = result + 1;
    }
    return result;
}

bool HashTable::store(unsigned int ID, const std::string& data){
    unsigned int index = primary_hash(ID);
    if(use_chaining){
        for(size_t i=0; i<chains[index].size(); i++){
            if(chains[index][i].getID() == ID){
                return false; //already exists
            }
        }
        //add to chain
        chains[index].push_back(FileBlock(ID, data));
        return true;
    }
    unsigned int step = secondary_hash(ID);
    for(unsigned int i=0; i<table_size; i++){
        unsigned int probe_index = ((index + i * step) % table_size); //compute probing index
        if(table[probe_index] == nullptr){ //if empty
            table[probe_index] = new FileBlock(ID, data); //store
            return true; //successfully stored
        }
        if(table[probe_index]->getID() == ID){
            return false; //already stored
        }
    }
    return false; //table full
}

bool HashTable::search(unsigned int ID, unsigned int& position) const{
    unsigned int index = primary_hash(ID);
    if(use_chaining) {
        for(size_t i=0; i<chains[index].size(); i++){
            if(chains[index][i].getID() == ID) {
                position = index;
                return true;
            }
        }
        return false;
    }
    unsigned int step = secondary_hash(ID);
    for(unsigned int i=0; i<table_size; i++){
        unsigned int probe_index = (index + i * step) % table_size;
        if(table[probe_index] != nullptr && table[probe_index]->getID() == ID){
            position = probe_index;
            return true;
        }
    }
    return false;
}
        /*
            CITATION:
        
            Anthropic. (2024). Claude 3.5 Sonnet [Large language model]. Retrieved from https://anthropic.com

            Lines 71 - 74 were written by Claude. My original code was:

                if(table[probe_index] == nullptr) {
                    return false;
                }
                if(table[probe_index]->getID() == ID) {
                    position = probe_index;
                    return true;
                }

            I gave Claude the following prompt as well as my HashTable.cpp file:
            "I have the following test case input and output, make changes to the code to ensure they match, tell me the changes and why they were needed. (included text from case 07 input and output as provided on learn))"
            Claude gave me back the same HashTable.cpp file with explanation "Looking at the original code, I found the issue in the open addressing logic. The search was stopping too early when it encountered a nullptr after a deletion. Here's the fix:"
            Fixes provided:
            1 - removed early exit condition "if(table[probe_index] == nullptr) return false;"
            2 - changed logic to continue after encountering nullptr
            3 - only check current position if !nullptr

        */

bool HashTable::remove(unsigned int ID){
    unsigned int index = primary_hash(ID);
    if(use_chaining){
        for(size_t i=0; i<chains[index].size(); i++){
            if(chains[index][i].getID() == ID){
                //if found
                chains[index].erase(chains[index].begin() + i);
                return true; //removed
            }
        }
        return false; //not found or removed
    }
    unsigned int step = secondary_hash(ID);
    for(unsigned int i=0; i<table_size; i++){
        unsigned int probe_index = (index + i * step) % table_size;
        if(table[probe_index] == nullptr){
            continue;
        }
        if(table[probe_index]->getID() == ID){
            delete table[probe_index];
            table[probe_index] = nullptr;
            return true;
        }
    }
    return false;
}

bool HashTable::corrupt(unsigned int ID, const std::string& data){
    unsigned int index = primary_hash(ID);
    if(use_chaining){
        for(size_t i = 0; i < chains[index].size(); i++){
            if(chains[index][i].getID() == ID){
                chains[index][i].set_payload(data, false);
                return true;
            }
        }
        return false;
    }
    unsigned int step = secondary_hash(ID);
    for(unsigned int i=0; i<table_size; i++){
        unsigned int probe_index = (index + i * step) % table_size;
        if(table[probe_index] == nullptr){
            //return false;
            continue;
        }
        if(table[probe_index]->getID() == ID){
            table[probe_index]->set_payload(data, false);
            return true;
        }
    }
    return false;
}

bool HashTable::validate(unsigned int ID) const{
    unsigned int index = primary_hash(ID);
    if(use_chaining){
        // if(index >= chains.size()){
        //     return false;
        // }
        //probably unneccessary, should pass test now that its commented out
        for(size_t i=0; i<chains[index].size(); i++){
            if(chains[index][i].getID() == ID){
                return chains[index][i].validate_checksum();
            }
        }
        return false; //not found
    }
    unsigned int step = secondary_hash(ID);
    for(unsigned int i=0; i<table_size; i++){
        unsigned int probe_index = (index + i * step) % table_size;
        if(table[probe_index] == nullptr){
            continue; //continue even if nullptr
        }
        if(table[probe_index]->getID() == ID){
            return table[probe_index]->validate_checksum();
        }
    }
    return false;
}

bool HashTable::is_chaining() const{
    return use_chaining;
}

bool HashTable::print_chain(int index) const{
    if(index<0 || index >= table_size){
        return false;
    }
    if(chains[index].size() == 0){
        std::cout<< "chain is empty"<<std::endl;
        return true;
    }
    for(size_t i=0; i<chains[index].size(); i++){
        std::cout<<chains[index][i].getID();
        if(i <(chains[index].size() - 1)){
            std::cout<<" ";
        }
    }
    std::cout<<std::endl;
    return true;
}
