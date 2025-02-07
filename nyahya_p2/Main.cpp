#include "HashTable.h"
#include <iostream>
#include <string>

using namespace std;

int main(){
    string command;
    HashTable* hashTable = nullptr;
    
    while (cin>>command){
        if(command == "NEW"){
            unsigned int size;
            int type;
            cin>>size>>type;
            if(hashTable == nullptr && size>0){ 
                hashTable = new HashTable(size, type == 1); //1 for chaining
                cout<<"success"<<endl;
            }else{
                cout<<"failure"<<endl; //table exists or size invalid
            }
        } 
        else if(command == "STORE"){
            unsigned int ID;
            string data;
            cin >>ID>>ws; //read ID ignore whitespace before payload
            getline(cin, data, '!'); //read data until !
            if(hashTable){
                if(hashTable->store(ID, data)){
                    cout<<"success"<<endl; //store successful
                }else{
                    cout<<"failure"<<endl; //store failed
                }
            }else{
                cout<<"failure"<<endl; //table not created
            }
        } 
        else if(command == "SEARCH"){
            unsigned int ID;
            cin >> ID;
            unsigned int position;
            if(hashTable->search(ID, position)){
                cout<<"found "<<ID<<" in "<<position<<endl;
            }else{
                cout<<"not found"<<endl;
            }
        } 
        else if(command == "DELETE"){
            unsigned int ID;
            cin>>ID;
            if(hashTable){
                if(hashTable->remove(ID)){
                    cout<<"success"<<endl; //removed
                }else{
                    cout<<"failure"<<endl; //not removed
                }
            }else{
                cout<<"failure"<<endl; //table not initialized
            }
        } 
        else if(command == "CORRUPT"){
            unsigned int ID;
            string data;
            cin>>ID>>ws;
            getline(cin, data, '!');
            if(hashTable){
                if(hashTable->corrupt(ID, data)){
                    cout<<"success"<<endl;
                }else{
                    cout<<"failure"<<endl; //no block exists, corruption fails
                }
            }else{
                cout<<"failure"<<endl; //table not initialized
            }
        } 
        else if(command == "VALIDATE"){
            unsigned int ID;
            cin>>ID;
            if(hashTable){
                unsigned int position;
                bool exists = hashTable->search(ID, position);
                if(!exists){
                    cout<<"failure"<<endl; //block dne
                }else{
                    if(hashTable->validate(ID)){
                        cout<<"valid"<<endl;  //block exists, checksum match
                    }else{
                    cout<<"invalid"<<endl;  //block ecists, checksum !equal
                    }
                }
            }else{
                cout<<"failure"<<endl; //table dne
            }
        } 
        else if(command == "PRINT"){
            int index;
            cin >> index;
            if(hashTable && hashTable->is_chaining()){
                bool result = hashTable->print_chain(index);
            if(!result){
                cout << "failure" << endl;
            }
            }else{
                cout << "failure" << endl;
            }
        } 
        else if(command=="EXIT"){
            delete hashTable;
            hashTable = nullptr;
            exit(0);
        }
    }

    delete hashTable;
    return 0;
}
