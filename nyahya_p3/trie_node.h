#ifndef TRIE_NODE_H
#define TRIE_NODE_H

#include "illegal_exception.h"
#include <vector>
#include <string>

class TrieNode{

    private:
    std::vector<TrieNode*> children; //store child nodes (max 15)
    std::string classification; //classification stored at this node ("animal", "plant", etc.)
    bool isTerminal; //flag indicates if node is complete classification. Was expicitly INSERTed

    public:
    TrieNode(const std::string& class_name = ""); //constructor, initializes node with given classification, default empty string for root
    ~TrieNode();
    bool isEndNode() const; //true if node marks end of classification
    const std::string& getClassification() const; //return classification at node
    TrieNode* getChild(int index) const; //return child node at specified index
    void setTerminal(bool value); //check if node terminal
    void setChild(int index, TrieNode* node); //set child node at specified index
    bool hasChildren() const; //return true if node has non-null children
};

#endif