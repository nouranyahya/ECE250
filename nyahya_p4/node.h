#ifndef NODE_H
#define NODE_H

#include <vector>
#include <string>
#include <tuple>

class Node{
    private:
    std::string id;
    std::string name;
    std::string type;
    std::vector<std::tuple<Node*, std::string, double>> edges;

    public:
    Node(const std::string& id, const std::string& name, const std::string& type); //constructor, initializes node w identifying info
    //accessor methods, get node properties
    std::string getId() const;
    std::string getName() const;
    std::string getType() const;
    const std::vector<std::tuple<Node*, std::string, double>>& getEdges()const; //ret edge list
    //mutator methods, mod node properties
    void setName(const std::string& name);
    void setType(const std::string& type);
    //edge methods
    void addEdge(Node* dest, const std::string& label, double weight);
    void removeEdge(Node* dest);
    bool hasEdge(Node* dest) const;
    void updateEdge(Node* dest, const std::string& label, double weight);
};

#endif