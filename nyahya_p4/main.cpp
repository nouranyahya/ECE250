#include "graph.h"
#include "illegal_exception.h"
#include <iostream>
#include <string>

int main(){
    Graph graph;
    std::string command;
    
    while (std::cin>>command){
        try{
            if(command == "LOAD"){
                std::string filename, type;
                std::cin>>filename>>type;
                
                if(type == "entities"){
                    graph.loadEntities(filename);
                }else if(type == "relationships"){
                    graph.loadRelationships(filename);
                }
                std::cout<<"success"<<std::endl;
            }else if(command == "RELATIONSHIP"){
                std::string sourceid, label, destid;
                double weight;
                std::cin>>sourceid>>label>>destid>>weight;

                if(graph.addRelationship(sourceid, label, destid, weight)){
                    std::cout<<"success"<<std::endl;
                }else{
                    std::cout<<"failure"<<std::endl;
                }
            }else if(command == "ENTITY"){
                std::string id, name, type;
                std::cin>>id>>name>>type;

                graph.addEntity(id, name, type);
                std::cout<<"success"<<std::endl;
            }else if(command == "PRINT"){
                std::string id;
                std::cin>>id;

                std::vector<std::string> adjacent = graph.getAdjacentNodes(id);
                if (!adjacent.empty()){
                    for (const std::string& adjid : adjacent){
                        std::cout<<adjid<< " ";
                    }
                }
                std::cout<<std::endl;
            }else if(command == "DELETE"){
                std::string id;
                std::cin >> id;

                if (graph.deleteNode(id)){
                    std::cout<<"success"<<std::endl;
                }else{
                    std::cout<<"failure"<<std::endl;
                }
            }else if(command == "PATH"){
                std::string id1, id2;
                std::cin>>id1>>id2;

                std::tuple<std::vector<std::string>, double> result = graph.findPath(id1, id2);
                std::vector<std::string> path = std::get<0>(result);
                if (!path.empty()){
                    for (const std::string& id:path){
                        std::cout<<id<<" ";
                    }
                    std::cout<<std::get<1>(result)<<std::endl;
                }else{
                    std::cout<<"failure"<<std::endl;
                }
            }else if(command == "HIGHEST"){
                std::tuple<std::string, std::string, double> result = graph.findHighest();
                if (std::get<2>(result) > 0){
                    std::cout<<std::get<0>(result)<<" "<<std::get<1>(result)<<" "<<std::get<2>(result)<<std::endl;
                }else{
                    std::cout<<"failure"<<std::endl;
                }
            } else if(command == "FINDALL"){
                std::string fieldType, fieldString;
                std::cin>>fieldType>>fieldString;

                std::vector<std::string> results = graph.findAll(fieldType, fieldString);
                if (!results.empty()){
                    for (const std::string& id:results){
                        std::cout<<id<<" ";
                    }
                    std::cout<<std::endl;
                }else{
                    std::cout<<"failure"<<std::endl;
                }
            }else if(command == "EXIT"){
                return 0;
            }
        }catch(const illegal_exception& e){
            std::cout<<e.what()<<std::endl;
        }
    }
    return 0;
}