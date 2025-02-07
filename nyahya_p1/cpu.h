// cpu class will assign, execute, and redistribute tasks as well as shutdown a core
#ifndef CPU_H
#define CPU_H

#include "deque.h"

class cpu {

    private:

        deque* cores; //pointer for array of deque objects, each for a single core task queue
        int number_cores; //number of cores in the cpu

    public:

        cpu(int N); //constructor initializing cpu with N cores
        ~cpu(); //destructor

        void spawn_task(int P_ID); //function to add task P_ID to queue of least busy core
        void run_task(int C_ID); //function to run task from specific core C_ID
        void sleep_core(int C_ID); //functiont to reassign core C_ID tasks and make it sleep
        void shutdown(); //function to clear tasks for all cores
        void print_size(int C_ID); //function to print number of tasks in C_ID queue
        void print_capacity(int C_ID); //function to print the current capacity of core C_ID

};

#endif