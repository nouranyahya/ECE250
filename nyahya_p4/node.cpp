#include "node.h"
#include <algorithm>

Node::Node(const std::string& id, const std::string& name, const std::string& type) : id(id), name(name), type(type){} //initialize node w data
std::string Node::getId()const{return id;}
std::string Node::getName()const{return name;}
std::string Node::getType()const{return type;}
const std::vector<std::tuple<Node*, std::string, double>>& Node::getEdges()const{return edges;}
void Node::setName(const std::string& newName){name = newName;}
void Node::setType(const std::string& newType){type = newType;}

void Node::addEdge(Node* dest, const std::string& label, double weight){
    edges.push_back(std::make_tuple(dest, label, weight));
}

void Node::removeEdge(Node* dest){
    std::vector<std::tuple<Node*, std::string, double>>::iterator it;
    it = std::remove_if(edges.begin(), edges.end(),[dest](const std::tuple<Node*, std::string, double>& edge){return std::get<0>(edge) == dest;}); //remove_if to find and remove edge with same dest
    edges.erase(it, edges.end());
}

bool Node::hasEdge(Node* dest)const{ //search edges for matching dest
    std::vector<std::tuple<Node*, std::string, double>>::const_iterator it;
    it = std::find_if(edges.begin(), edges.end(),[dest](const std::tuple<Node*, std::string, double>& edge) {return std::get<0>(edge) == dest;});
    return it != edges.end(); //ret true if found
}

void Node::updateEdge(Node* dest, const std::string& label, double weight){
    for (std::tuple<Node*, std::string, double>& edge:edges){ //iterate edges to find match
        if (std::get<0>(edge) == dest){ //update if match
            std::get<1>(edge) = label;
            std::get<2>(edge) = weight;
            break; //stop imm after updating
        }
    }
}