#ifndef TRIE_H
#define TRIE_H

#include "trie_node.h"
#include "illegal_exception.h"
#include <vector>
#include <string>

class Trie{

    private:
    TrieNode* root; //trie root pointer, empty classification string
    int classificationCount; //increments on successful insert, decrements on successful erase
    bool containsUppercase(const std::string& str); //true if uppercase found
    void gatherClassifications(TrieNode* node, std::string currentPath, std::vector<std::string>& result); //helper for print, builds classifications list by traversing trie

    public:
    Trie(); //initialize empty trie with root node
    ~Trie();
    std::vector<std::string> split(const std::string& str, char delimiter); //takes string and delimiter, returns vector of substrings
    bool insert(const std::string& classification); //insert new classification path into trie, true if inserted, false if already exists
    std::string classify(const std::string& input); //return comma-separated classification path
    void clear();
    bool empty() const; //true if classificationCount==0
    int size() const; //return number of classifications
    std::string print(); //return string of all classifications
    bool erase(const std::string& classification); //remove classification from trie, true if found and erased

};

#endif