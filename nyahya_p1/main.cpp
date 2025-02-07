#include "cpu.h"
#include "deque.h"
#include <iostream>

using namespace std;


int main() 
{
    string command;
    cpu* cpu_inst = nullptr;
    
    while(cin>>command){
        if(command=="ON"){
            int N;
            cin >> N;
            if(cpu_inst==nullptr && N>1){ 
                cpu_inst = new cpu(N);
                cout<<"success"<<endl;
            }else{
                cout<<"failure"<<endl; // Failure if CPU is already on or N is invalid
            }
        } else if(command=="SPAWN"){
            int P_ID;
            cin >> P_ID;
            if (cpu_inst){
                cpu_inst->spawn_task(P_ID);  // Spawn task with task ID P_ID
            }else{
                cout<<"failure"<<endl; // Failure if CPU is not initialized
            }
        } else if(command=="RUN"){
            int C_ID;
            cin >> C_ID;
            if(cpu_inst){
                cpu_inst->run_task(C_ID);  // Run task from core with ID C_ID
            }else{
                cout<<"failure"<<endl; // Failure if CPU is not initialized
            }
        } else if(command=="SLEEP"){
            int C_ID;
            cin >> C_ID;
            if(cpu_inst){
                cpu_inst->sleep_core(C_ID);  // Put core to sleep and redistribute its tasks
            }else{
                cout<<"failure"<<endl; // Failure if CPU is not initialized
            }
        } else if(command=="SHUTDOWN"){
            if(cpu_inst){
                cpu_inst->shutdown(); // Shutdown CPU and clear all tasks
            }else{
                cout<<"failure"<<endl; // Failure if CPU is not initialized
            }
        }else if(command=="SIZE") {
            int C_ID;
            cin >> C_ID;
            if(cpu_inst){
                cpu_inst->print_size(C_ID);  // Print the size of core's queue
            }else{
                cout<<"failure"<<endl; // Failure if CPU is not initialized
            }
        }else if(command=="CAPACITY"){
            int C_ID;
            cin >> C_ID;
            if(cpu_inst){
                cpu_inst->print_capacity(C_ID);  // Print the capacity of core's queue
            }else{
                cout<<"failure"<<endl; // Failure if CPU is not initialized
            }
        }else if(command=="EXIT"){
            delete cpu_inst;
            cpu_inst = nullptr;
            exit(0);
        }
    }

    delete cpu_inst;
    return 0;
}
