#include "cpu.h"
#include <iostream>

using namespace std;

cpu::cpu(int N) : number_cores(N){
    //constructor initializing cpu with N cores
    cores = new deque[number_cores]; //array of deque, one for each core
}

cpu::~cpu(){
    //destructor
    delete[] cores; //freeing memory used for array
}

void cpu::spawn_task(int P_ID){
    //function to add task P_ID to queue of least busy core
    if(P_ID<=0){
        cout<<"failure"<<endl; //P_ID is negative and invalid
        return;
    }
    int min_index = 0; //used to find core with least tasks
    for(int i=1; i<number_cores; i++){
        if(cores[i].get_size()<cores[min_index].get_size()){
            //if size of current core less than current min core, update min core
            min_index = i;
        }else if(cores[i].get_size()==cores[min_index].get_size()){
            //if sizes are same, task will be assigned to core with lower C_ID
            if(i<min_index){
                min_index = i; //to assign to core with lower C_ID
            }
        }
    }

    cores[min_index].push_back(P_ID); //put task P_ID to the back of the core with least tasks
    cout<<"core "<<min_index<<" assigned task "<<P_ID<<endl;
}

void cpu::run_task(int C_ID){
    //function to run task from specific core C_ID
    if(C_ID<0 || C_ID>=number_cores){
        cout<<"failure"<<endl; //C_ID is negative or greater than cores present and invalid
        return;
    }
    int P_ID = cores[C_ID].pop_front(); //task we are looking at is the one at front of core C_ID
    if(P_ID != -1){
        //if task valid
        cout<<"core "<<C_ID<<" is running task "<<P_ID<<endl;
    }else{
        //no task to run
        cout<<"core "<<C_ID<<" has no tasks to run"<<endl;
    }

    if(cores[C_ID].get_size()==0){
        //if core queue empty after running a task, steal from busiest core
        int max_index = -1; //will be used to find core with most tasks if one exists
        int max_size = 0;
        for(int i=0; i<number_cores; i++){
            if(i!=C_ID && cores[i].get_size()>max_size){
                //if current core has more tasks than current max core, update max core
                max_size = cores[i].get_size();
                max_index = i;
            }
        }
        if (max_index!=-1){
            //if core with max index was found, value will not equal -1 so proceed with stealing
            P_ID = cores[max_index].pop_back(); //P_ID of task being stolen
            if(P_ID != -1){
                cores[C_ID].push_back(P_ID); //put at back of queue of core we just ran task from
            }
        }
    }
}


void cpu::sleep_core(int C_ID){
    //function to reassign core C_ID tasks and make it sleep
    if(C_ID<0 || C_ID>= number_cores){
        cout<<"failure"<<endl; //C_ID not valid
        return;
    }
    if (cores[C_ID].get_size()==0){
        cout<<"core "<<C_ID<<" has no tasks to assign"; //all tasks for this core have been redistributed
    }
    while(cores[C_ID].get_size()>0){
        //while core C_ID has tasks, redistribute them
        int P_ID= cores[C_ID].pop_back();
        //find the core with least number of tasks
        int min_index = (C_ID == 0) ? 1 : 0; //line written by claude, used to find core with least tasks
        // original line I had was int min_index = 0;

        /*
            CITATION:
        
            Anthropic. (2024). Claude 3.5 Sonnet [Large language model]. Retrieved from https://anthropic.com

            Line 89 was written by Claude. My original line was
                int min_index = 0; followed by the for loop to begin finding the least busy core for task reassignment.
            I gave Claude the following prompt as well as my cpu.cpp file:
            "when I run the sleep command, the code outputs an infinite loop saying its reassigning the same task, whats happening and whats the fix for this"
            My code was originally outputting an infinitely long loop saying task x assigned to core y and I did not know why
            Claude gave me back the same cpu.cpp file with the only change being line 89 above, I did not understand the syntax nor the reasoning behind it
            so I prompted Claude with the following:
            "explain what this line is doing and how and the syntax int min_index = (C_ID == 0) ? 1 : 0;"
            Claude gave responded, the following was the most useful to me of Claudes response
            It can be read as:
            If (C_ID == 0) is true, then min_index = 1
            If (C_ID == 0) is false, then min_index = 0

        */

        for(int i = 0; i < number_cores; i++){
            if(i != C_ID && cores[i].get_size()<cores[min_index].get_size()){
                //if core isnt the core going to sleep and it has less tasks than the current min core
                min_index = i;
            }
        }

        cores[min_index].push_back(P_ID); // push task to the back of core with least tasks
        cout<<"task "<<P_ID<<" assigned to core "<<min_index<<" ";
    }
    cout<<endl;
}

void cpu::shutdown(){
    bool tasks_remaining=false;
        for (int i=0; i<number_cores; i++) {
            while(cores[i].get_size()>0){
                tasks_remaining=true;
                int P_ID = cores[i].pop_front();
                if(P_ID != -1){
                    //if task valid
                    cout<< "deleting task "<<P_ID<<" from core "<<i<<" ";
                }
            } //loop breaks when no more tasks available to reassign, goes to next core
        }
        //if no cores have tasks to reassign, tasks_remaining is false
    if(!tasks_remaining){
        cout<<"no tasks to remove";
    }
    
    std::cout << std::endl;

}

void cpu::print_size(int C_ID){
    //function to print number of tasks in C_ID queue
    if(C_ID<0 || C_ID>=number_cores){
        cout<<"failure"<<endl; //invalid C_ID
        return;
    }
    cout<<"size is "<<cores[C_ID].get_size()<<endl;
}

void cpu::print_capacity(int C_ID){
    //function to print capacity of tasks in C_ID
    if(C_ID<0 || C_ID>=number_cores){
        cout<<"failure"<<endl; //invalid C_ID
        return;
    }
    cout<<"capacity is "<< cores[C_ID].get_capacity()<<endl;
}