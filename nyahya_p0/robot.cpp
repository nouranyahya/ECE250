#include "robot.hpp"
#include <iostream>

robot::robot() : potential(0.0), description(){}

char robot::get_description(){
    return description;
}

void robot::add_description(char new_description){
    description=new_description;
}

float robot::get_potential(){
    return potential;
}

void robot::add_potential(float new_potential){
    potential=new_potential;
}
