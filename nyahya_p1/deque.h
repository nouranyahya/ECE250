//deque class will manage the array of tasks for each core, it will handle resizing as well as adding and removing tasks from both ends

#ifndef DEQUE_H
#define DEQUE_H

class deque {

    private:

        int *tasks; //array that will store tasks for a core
        int front, back, size, capacity;

        void resize(int new_capacity); //function to resize array as required

    public:

        deque(); //constructor
        ~deque(); //destrcutor
        void push_back(int P_ID); //function to add task P_ID to back of queue
        int pop_front(); //function to remove task from front and return it
        int pop_back(); //function to remove task from back and return it
        int get_size(); // function to return the number of tasks in queue
        int get_capacity(); //function to return the current capacity of the deque

};

#endif