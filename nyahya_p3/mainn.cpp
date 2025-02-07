#include "trie.h"
#include "trie_node.h"
#include "ece250_socket.h"
#include "illegal_exception.h"
#include <iostream>
#include <fstream>
#include <string>

int main() {

    Trie trie;
    std::string command;
    
    while (std::cin >> command){
        if (command == "LOAD"){
            std::string filename;
            std::cin >> filename;
            std::ifstream inFile(filename);
            if (!inFile.is_open()){
                continue;
            }
            std::string line;
            bool loadSuccess = true;
            while (std::getline(inFile, line)){
                if (!line.empty()){
                    try {
                        trie.insert(line);
                    }catch (const illegal_exception& e){
                        std::cout << e.what() << std::endl;
                        loadSuccess = false;
                    }
                }
            }
            inFile.close();
            if(loadSuccess){
                std::cout << "success" << std::endl;
            }
        }else if (command == "INSERT"){
            std::string classification;
            std::cin.ignore();
            std::getline(std::cin, classification);
            try{
                std::cout << (trie.insert(classification) ? "success" : "failure") << std::endl;
            }catch (const illegal_exception& e){
                std::cout << e.what() << std::endl;
            }
        }else if (command == "CLASSIFY"){
            std::string input;
            std::cin.ignore();
            std::getline(std::cin, input);
            try{
                std::cout << trie.classify(input) << std::endl;
            }catch (const illegal_exception& e){
                std::cout << e.what() << std::endl;
            }
        } else if (command == "ERASE"){
            std::string classification;
            std::cin.ignore();
            std::getline(std::cin, classification);
            try{
                std::cout << (trie.erase(classification) ? "success" : "failure") << std::endl;
            }catch (const illegal_exception& e){
                std::cout << e.what() << std::endl;}
        }else if (command == "PRINT"){
            std::cout << trie.print() << std::endl;
        }else if (command == "EMPTY"){
            std::cout << "empty " << (trie.empty() ? "1" : "0") << std::endl;
        }else if (command == "CLEAR"){
            trie.clear();
            std::cout << "success" << std::endl;
        }else if (command == "SIZE"){
            std::cout << "number of classifications is " << trie.size() << std::endl;
        }else if (command == "EXIT"){
           return 0;
        }
    }
    
return 0;
}