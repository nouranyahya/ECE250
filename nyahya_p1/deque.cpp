#include "deque.h"

deque::deque(): size(0), capacity(4), front(0), back(0){
    tasks = new int[capacity]; //allocate memory for array
}

deque::~deque(){
    delete[] tasks; //freeing memory used for array
}

void deque::push_back(int P_ID){
    //adding a task to back of queue
    tasks[back] = P_ID; //task P_ID is now back of queue
    back = (back+1) % capacity; //circular indexing
    size++; //task added now update size
    if(size==capacity){
        //capacity is full, need to double
        resize(capacity*2);
    }
}

int deque::pop_front(){
    //remove task at front and return it, -1 used because it is not a valid P_ID, will use in main.cpp
    if (size==0){
        return -1; //if no tasks available
    }
    int P_ID = tasks[front]; //task at front
    front = (front+1) % capacity; //circular indexing
    size--; //task removed now update size
    if (size<=(capacity/4) && capacity>=4 && size>0){
        //if size is 1/4 of capacity then half capacity
        resize(capacity/2);
    }
    return P_ID; //return task
}

int deque::pop_back(){
    //remove task at back and return it, -1 used for same reason above
    if (size==0){
        return -1; //if no tasks available
    }
    back = (back-1+capacity) % capacity; //circular indexing
    int P_ID = tasks[back]; //task at back
    size--; //task removed now update size
    if (size<=(capacity/4)&& capacity>=4 && size>0){
        //if size is 1/4 of capacity then half capacity
        resize(capacity/2);
    }
    return P_ID; //return task
}

void deque::resize(int new_capacity){
    //resize when capacity changes
    int *new_tasks = new int[new_capacity]; //array with new capacity
    for (int i=0; i<size; i++){
        //loop through old array and copy its contents to the new one
        new_tasks[i] = tasks[(front+i) % capacity];
    }
    delete[] tasks; //delete memory old array
    tasks = new_tasks; //updating array
    front = 0; //resetting front
    back = size; //resetting back to current size value
    capacity = new_capacity; //updating capacity value
}

int deque::get_size(){
    return size;
}

int deque::get_capacity(){
    return capacity;
}