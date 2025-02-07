#include "graph.h"
#include "illegal_exception.h"
#include <fstream>

Graph::Graph(){} //initializes empty graph

Graph::~Graph(){
    for (Node* node:nodes){
        delete node;
    }
}

bool Graph::isValidId(const std::string& id)const{
    return std::all_of(id.begin(), id.end(), [](char c){ return std::isalnum(c);});
}

Node* Graph::findNode(const std::string& id)const{
    //find and return pointer for id
    std::vector<Node*>::const_iterator it = std::find_if(nodes.begin(), nodes.end(), [&id](const Node* node) { return node->getId() == id;});
    return it != nodes.end() ? *it : nullptr;
}

void Graph::loadEntities(const std::string& filename){
    std::ifstream file(filename);
    std::string id, name, type;
    while (file>>id>>name>>type){
        addEntity(id, name, type);
    }
}

void Graph::loadRelationships(const std::string& filename){
    std::ifstream file(filename);
    std::string sourceid, label, destid;
    double weight;
    while (file>>sourceid>>label>>destid>>weight){
        addRelationship(sourceid, label, destid, weight);
    }
}

bool Graph::addRelationship(const std::string& sourceid, const std::string& label, const std::string& destid, double weight){
    
    if (!isValidId(sourceid) || !isValidId(destid)){throw illegal_exception();}
    
    Node* source = findNode(sourceid);
    Node* dest = findNode(destid);
    if (!source || !dest) return false; //if either dne, cant add rel.
    if (source->hasEdge(dest)){ //if rel. exists, update
        source->updateEdge(dest, label, weight);
        dest->updateEdge(source, label, weight);
    }else{ //rel dne, add it
        source->addEdge(dest, label, weight);
        dest->addEdge(source, label, weight);
    }
    return true; //successfully added
}

void Graph::addEntity(const std::string& id, const std::string& name, const std::string& type){
    
    if (!isValidId(id)){throw illegal_exception();}

    Node* existing = findNode(id);
    if (existing){ //exists, update
        existing->setName(name);
        existing->setType(type);
    }else{ //dne, add new
        nodes.push_back(new Node(id, name, type));
    }
}

bool Graph::deleteNode(const std::string& id){
    
    if (!isValidId(id)){throw illegal_exception();}
    
    //find node to delete, func compares node id w target id
    std::vector<Node*>::iterator it = std::find_if(nodes.begin(), nodes.end(),[&id](const Node* node){return node->getId() == id;});
    if (it == nodes.end()) return false; //node dne, cant delete
    Node* nodeToDelete = *it; //pointer for node to delete
    for (Node* node:nodes){
        if (node != nodeToDelete){ //will skip node being deleted
            node->removeEdge(nodeToDelete);
        }
    }
    
    nodes.erase(it); //remove from vector
    delete nodeToDelete;
    return true; //successfully deleted
}

std::vector<std::string> Graph::getAdjacentNodes(const std::string& id){
    
    if (!isValidId(id)){throw illegal_exception();}
    
    Node* node = findNode(id);
    if (!node) return std::vector<std::string>(); //ret empty path id node dne
    std::vector<std::string> adjacent; //vector will store adj node ids
    for (const auto& edge : node->getEdges()){
        adjacent.push_back(std::get<0>(edge)->getId());
    }
    std::sort(adjacent.begin(), adjacent.end(), std::greater<std::string>()); //descending order
    return adjacent; //ret sorted list
}

std::tuple<std::vector<std::string>, double> Graph::findPath(const std::string& id1, const std::string& id2){
    
    if (!isValidId(id1) || !isValidId(id2)){throw illegal_exception();}
    
    Node* start = findNode(id1);
    Node* end = findNode(id2);
    if (!start || !end){ //ret empty path if either node dne
        return std::make_tuple(std::vector<std::string>(), 0.0);
    }
    double pathweight = 0.0; //store path weight
    std::vector<std::string> path = dijkstra(start, end, pathweight); //find path weight using dijkstra
    return std::make_tuple(path, pathweight); //ret path and weight
}

/*
    CITATION:
    
    Anthropic. (2024). Claude 3.5 Sonnet [Large language model]. Retrieved from https://anthropic.com

    Lines 134 - 188 (apart from the comments) were written entirely by Claude. (complete dijkstra() method)

    I gave Claude the following prompt as well as my graph.cpp, graph.h, and node.h file and the p4 project doc provided on learn:
    "here are some of my files for this project as well as the project doc. i need to modify dijkstras algorithm for heighest weight instead of shortest path.
    dijkstras will be used by PATH command to return the highest weight path. below are requirements from the project doc, implement this method to find the highest weight path, keep your implementation as simple as possible and stick to the allowed libraries in the doc.
    explain your implemenation in detail and include detailed comments on every line, keep them clear and concise. make sure your implementation meets the runtime requirements specified in the project doc and prove it.
    (insert PATH command requirements from project doc, all 4 columns)"
    Claude gave me back lines 134 - 188 with a detailed explanation for the code, i removed the comments provided and added my own, i also changed the variable names
        
*/

//dijkstras alg. - for max weight path
std::vector<std::string> Graph::dijkstra(Node* start, Node* end, double& pathweight)const{
    
    std::vector<double> dist(nodes.size(), -1e9); //-ve inf val
    std::vector<Node*> prev(nodes.size(), nullptr); //store prev nodes in path
    std::vector<bool> visited(nodes.size(), false); //to track visited nodes
    std::vector<std::pair<double, Node*>> heap; //maxheap
    
    auto comparison = [](const std::pair<double, Node*>& a, const std::pair<double, Node*>& b){ //maxheap compare func
        return a.first < b.first;
    }; 

    size_t startindex = std::find(nodes.begin(), nodes.end(), start) - nodes.begin(); //find index of start node
    dist[startindex] = 0; //initialize dist w 0
    heap.push_back(std::make_pair(0.0, start)); //add start node to heap
    std::make_heap(heap.begin(), heap.end(), comparison); //creat maxheap
    
    while (!heap.empty()){ //continue until heap empty
        //remove top element
        std::pop_heap(heap.begin(), heap.end(), comparison);
        std::pair<double, Node*> current = heap.back();
        heap.pop_back();
        
        Node* currentnode = current.second; //get current
        size_t currentindex = std::find(nodes.begin(), nodes.end(), currentnode) - nodes.begin(); //find index
        if (visited[currentindex]) continue; //skip if alr visited
        visited[currentindex] = true; //mark visisted
        
        for (const auto& edge : currentnode->getEdges()){ //process all edges for current node
            Node* neighbor = std::get<0>(edge);
            double weight = std::get<2>(edge);
            size_t neighborindex = std::find(nodes.begin(), nodes.end(), neighbor) - nodes.begin(); //find index
            if (!visited[neighborindex]){ //process unvisited neighbors
                double newdist = dist[currentindex] + weight;
                if (newdist > dist[neighborindex]){ //update if newdist is greater, finding max weight
                    dist[neighborindex] = newdist;
                    prev[neighborindex] = currentnode;
                    heap.push_back(std::make_pair(newdist, neighbor)); //add to heap
                    std::push_heap(heap.begin(), heap.end(), comparison); //maintain property
                }
            }
        }
    }
    
    std::vector<std::string> path;
    size_t endindex = std::find(nodes.begin(), nodes.end(), end) - nodes.begin(); //find end node index
    pathweight = dist[endindex]; //store weight
    if (pathweight == -1e9){
        return path; //ret empty if path dne
    }
    for (Node* at = end; at != nullptr; at = prev[std::find(nodes.begin(), nodes.end(), at) - nodes.begin()]){ //reconstruct path
        path.push_back(at->getId()); //add node id to path
    }
    std::reverse(path.begin(), path.end());
    return path; //ret updated path
}

std::tuple<std::string, std::string, double> Graph::findHighest(){
    
    if (nodes.empty()){ //ret empty path if graph empty
        return std::make_tuple("", "", 0.0);
    }
    std::string maxid1, maxid2;
    double maxweight = -1e9;
    for (Node* start:nodes){ //nested loops check all possible pairs
        for (Node* end:nodes){
            if (start != end){ //skips same node
                double pathweight = 0.0;
                std::vector<std::string> path = dijkstra(start, end, pathweight); //find path bw this pair
                if (pathweight > maxweight){ //update if new path weight higher
                    maxweight = pathweight;
                    maxid1 = start->getId();
                    maxid2 = end->getId();
                }
            }
        }
    }
    return std::make_tuple(maxid1, maxid2, maxweight); //ret highest path
}

std::vector<std::string> Graph::findAll(const std::string& fieldtype, const std::string& fieldstring){
    
    std::vector<std::string> result;
    for (Node* node:nodes){
        if (fieldtype == "name" && node->getName() == fieldstring){ //if name match
            result.push_back(node->getId());
        }else if(fieldtype == "type" && node->getType() == fieldstring){ //if type match
            result.push_back(node->getId());
        }
    }
    return result; //ret matching node ids
}