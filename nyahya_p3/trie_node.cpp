#include "trie_node.h"
#include "illegal_exception.h"

TrieNode::TrieNode(const std::string& class_name){
    //constructor, initialize node with classification name and empty children vector
    classification = class_name; //store classification string
    isTerminal = false;
    children.resize(15, nullptr); //vector of 15 null child pointers
}

TrieNode::~TrieNode(){
    //destructor, loop through children and delete
    for (int i=0; i<15; ++i){
        if (children[i] != nullptr){
            delete children[i];
            children[i]=nullptr;
        }
    }
}

bool TrieNode::isEndNode() const{
    //check if node is end of classification
    return isTerminal; //terminal status flag
}

const std::string& TrieNode::getClassification() const{
    //get classification string stored at node
    return classification; 
}

TrieNode* TrieNode::getChild(int index) const{
    //get child node at index, nullptr if no child
    if (index<0 || index>=children.size()){
        return nullptr;
    }
    return children[index];
}

void TrieNode::setTerminal(bool value){
    isTerminal=value; //update flag status
}

void TrieNode::setChild(int index, TrieNode* node){
    //set child pointer at index
    if (index>=0 && index<children.size()){
        children[index] = node;
    }
}

bool TrieNode::hasChildren() const{
    //return true if 1 or more child pointer is non-null, returns early if child found
    for (int i=0; i<15; ++i){
        if (children[i] != nullptr){
            return true;
        }
    }
    return false; //no children found
}