#ifndef GRID_H
#define GRID_H

#include "robot.hpp"
#include <iostream>
#include <cmath>

class grid
{

    public:

        grid(int n, int m); //constructor
        ~grid(); //destructor

        
        void add_g_o(int x, int y, char T); //function to add goal or obstacle to (x,y) within array
        void next_move(int x, int y); //will output next position to move to
        void clear(); //function to clear a grid of goals and obstacles
        void update_k(float new_k); //function to update k value

    private:

        int M,N;
        float k;
        robot** map; //pointer for 2D array that will hold potential values

        void calculate_potential(int xg, int yg, char T); //function to calculate potential value for map
        float calculate_potential_cell(int x, int y, int xg, int yg, char T); //function to calculate potential value for each cell
};
#endif