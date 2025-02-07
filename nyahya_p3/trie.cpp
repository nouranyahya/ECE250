#include "ece250_socket.h"
#include "illegal_exception.h"
#include "trie.h"
#include <iostream>
#include <sstream>
#include <fstream>

std::vector<std::string> Trie::split(const std::string& str, char delimiter){
    //split string into vector of substrings based on delimiter
    std::vector<std::string> tokens; //stores split strings
    std::string token; //temp storage
    std::istringstream tokenline(str);
    while (std::getline(tokenline, token, delimiter)){
        tokens.push_back(token);
    }
    return tokens; //return vector of tokens/split
}

bool Trie::containsUppercase(const std::string& str){
    //check for uppercase, return true immediately if found
    for (int i=0; i<str.length(); ++i){
        if (isupper(str[i])){
            return true; //uppercase found
        }
    }
    return false; //not found
}

void Trie::gatherClassifications(TrieNode* node, std::string currentPath, std::vector<std::string>& result){
    //helper to collect all complete classifications for print
    if (node == nullptr){
        return; //nothing to gather
    }
    
    if (!node->hasChildren() && node->isEndNode()){
        //add only if terminal node w/ no children
        if (!currentPath.empty()){
            result.push_back(currentPath);
        }
    }

    for (int i=0; i<15; ++i){
        //process child nodes
        TrieNode* child = node->getChild(i);
        if (child != nullptr){
            std::string newPath = currentPath;
            std::string childClass = child->getClassification();
            
            if (!childClass.empty()){
                if (!newPath.empty()){
                    newPath += ",";
                }
                newPath += childClass; //add child classification
            }
            gatherClassifications(child, newPath, result);
        }
    }
}

Trie::Trie() : root(new TrieNode()), classificationCount(0){} //constructor, initialize empty trie with root node

Trie::~Trie(){
    delete root; //destructor
}

bool Trie::insert(const std::string& classification){
    //insert new classification into trie
    if (classification.empty()){
        return false;  //dont insert if empty
    }

    if (containsUppercase(classification)){
        throw illegal_exception();
    }

    std::vector<std::string> levels = split(classification, ',');
    TrieNode* current = root; //start at root
    bool isNew = false; //tracking if new nodes created

    for (int i=0; i<levels.size(); ++i){
        if (!current){
            return false; //root/trie dne, cannot insert
        }
        int childIndex = -1; //initialize to invalid index, will track where to insert child
        bool found = false; //track if existing child found

        //find existing matching child
        for (int j=0; j<15; j++){
            TrieNode* child = current->getChild(j);
            if (child && child->getClassification() == levels[i]){
                childIndex = j; //child found at j
                found = true;
                break;
            }
        }

        //if not found, find first empty spot
        if (!found){
            for (int j=0; j<15; j++){
                if (current->getChild(j) == nullptr){
                    childIndex = j;
                    current->setChild(childIndex, new TrieNode(levels[i]));
                    isNew = true; //new insertion
                    break;
                }
            }
            if (childIndex == -1){
                return false; //no space
            }
        }

        current = current->getChild(childIndex); //move to child node
        if (!current){ //verify successful move
            return false; //unsuccessful move, failed insert
        }
    }

    if (isNew || !current->isEndNode()){
        //update terminal status and count
        current->setTerminal(true);
        classificationCount++;
        return true; //successful insert
    }
    return false; //failed insert
}

std::string Trie::classify(const std::string& input){
    if (containsUppercase(input)){
        throw illegal_exception();
    }

    TrieNode* current = root;
    std::string classification;
    
    while (current != nullptr && current->hasChildren()){
        //build comma-separated list of candidates at this level
        std::string candidates;
        for (int i=0; i<15; ++i){
            TrieNode* child = current->getChild(i);
            if (child != nullptr){
                std::string childClass = child->getClassification();
                if (!childClass.empty()){
                    if (!candidates.empty()){
                        candidates += ",";
                    }
                    candidates += childClass;
                }
            }
        }

        if (candidates.empty()){
            break;
        }

        std::string label = labelText(input, candidates); //llm

        //find matching child node
        bool found = false;
        for (int i=0; i<15; ++i){
            TrieNode* child = current->getChild(i);
            if (child != nullptr && child->getClassification() == label){
                //compares classification of the child of current with label from llm
                //if they match, then label==classification for input
                if (!classification.empty()) {
                    classification += ",";
                }
                classification += label;
                current = child;
                found = true;
                break;
            }
        }
        
        if (!found){
            break; //child not found, no classification
        }
    }
    
    return classification;
}

void Trie::clear(){
    //reset trie to empty
    delete root;
    root = new TrieNode("");
    classificationCount = 0;
}

bool Trie::empty() const{
    return (classificationCount == 0); //true if count == 0
}

int Trie::size() const{
    return classificationCount;
}

std::string Trie::print(){
    //print string of all classifications
    if (empty()){
        return "trie is empty"; //main outputs this
    }
    
    //build result string with underscores starting with classification at each node not empty string
    std::vector<std::string> classifications;
    gatherClassifications(root, "", classifications);
    std::string result;
    for (int i=0; i<classifications.size(); ++i){
        if (i>0){
            result += "_";
        }
        result += classifications[i];
    }
    result += "_";
    return result;
}

bool Trie::erase(const std::string& classification){
    if (containsUppercase(classification)){
        throw illegal_exception();
    }
    if (empty()){
        return false; //nothing to erase
    }

    /*
        CITATION:
        
        Anthropic. (2024). Claude 3.5 Sonnet [Large language model]. Retrieved from https://anthropic.com

        Lines 238 - 261 (apart from comments) were written by Claude.

        I gave Claude the following prompt as well as my trie.cpp file and the project requirements for the ERASE command pasted from the provided doc on learn:
        "write the missing code for this project in my erase function to find the appropriate classification to erase when command ERASE is entered. below is the requirement for ERASE. keep your implementation as simple as possible and explain it to me in detail"
        Claude gave me back lines 238 - 261 with a detailed explanation for the code
            
    */

    std::vector<std::string> levels = split(classification, ',');
    TrieNode* current = root;
    TrieNode* parent = nullptr; //tracking for deletion
    int lastIndex = -1; //tracking parent index

    //find node to erase
    //level is one part of split from levels which is full string of split
    //iterate through each split part of string levels
    for (const std::string& level : levels){
        bool found = false;
        for (int i=0; i<15; i++){
            TrieNode* child = current->getChild(i);
            if (child && child->getClassification() == level){
                parent = current;
                lastIndex = i;
                current = child;
                found = true;
                break;
            }
        }
        if (!found){
            return false; //classification not found
        }
    }

    if (!current->isEndNode()) {
        return false; //cant erase nonterminal node
    }

    current->setTerminal(false); //mark non-terminal
    classificationCount--;

    if (!current->hasChildren() && !current->isEndNode() && parent != nullptr){
        //remove node if no children and not terminal
        parent->setChild(lastIndex, nullptr); //remove from parent
        delete current;
    }
    return true; //successfully erased
}