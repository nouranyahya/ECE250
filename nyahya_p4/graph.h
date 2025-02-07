#ifndef GRAPH_H
#define GRAPH_H

#include "node.h"
#include <vector>
#include <algorithm>
#include <tuple>

class Graph{
    private:
    std::vector<Node*> nodes; //stores node pointers
    //helpers for graph operations
    bool isValidId(const std::string& id) const;
    Node* findNode(const std::string& id) const;
    std::vector<std::string> dijkstra(Node* start, Node* end, double& pathWeight)const; //alg modified for max weight path

    public:
    Graph();
    ~Graph();
    void loadEntities(const std::string& filename);
    void loadRelationships(const std::string& filename);
    //graph operations
    bool addRelationship(const std::string& sourceId, const std::string& label, const std::string& destId, double weight);
    void addEntity(const std::string& id, const std::string& name, const std::string& type);
    bool deleteNode(const std::string& id);
    std::vector<std::string> getAdjacentNodes(const std::string& id);
    std::tuple<std::vector<std::string>, double> findPath(const std::string& id1,const std::string& id2); //find heighest w path bw two nodes
    std::tuple<std::string, std::string, double> findHighest(); //find highest w path in graph
    std::vector<std::string> findAll(const std::string& fieldType, const std::string& fieldString); //find matching nodes
};

#endif