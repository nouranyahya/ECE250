#include "grid.hpp"


using namespace std;

grid::grid (int n, int m): N(n), M(m), k(1.0){ 
    //constructor for class grid, takes parameters rows and columns
    map=new robot*[N]; //dynamically allocating memory for 2d array, first dim. for rows
    for (int i=0; i<N; ++i){
        map[i]=new robot[M]; //dynamically allocating memory for each column
    }
}

grid:: ~grid(){
    //destructor for class grid, prevents memory leaks by freeing dynamically allocated memory
    for (int i=0; i<N; ++i){
         delete[] map[i]; //delete rows
    }
    delete[] map; //delete array of pointers
}

void grid::add_g_o(int x, int y, char T){
    if((x>=0)&&(x<N)&&(y>=0)&&(y<M)){
        //if position is within bounds
        if(T=='G'||T=='O'){
            map[x][y].add_description(T); //add description of cell to be obstacle or goal
            cout<<"success"<<endl; //insertion was successful
            calculate_potential(x, y, T);
        }else{
            cout<<"failure"<<endl; //insertion not successful
        }
    }else{
        //then out of bounds
        cout<<"failure"<<endl; //insertion not successful
    }
}

float grid::calculate_potential_cell(int x, int y, int xg, int yg, char T){
    //calculating for each single cell
    float potential;
    if(x==xg && y==yg){
        //if we are in the same position as obstacle or goal, potential is 0
        potential=0.0;
        return potential;
    }
    
    float dist=std::sqrt(((x-xg)*(x-xg))+((y-yg)*(y-yg)));
    potential=k/dist;

    if(T=='G'){
        potential=-potential;
    }

    return potential;
}

void grid::calculate_potential(int xg, int yg, char T){
    //calculating for entire map
    for (int i=0; i<N; ++i){
        for (int j=0; j<M; ++j){
            if(i == xg && j == yg){
                //if we are in same spot as obstacle or goal, skip calculating the potential
            } else {
                float potential=calculate_potential_cell(i, j, xg, yg, T);
                float initial_potential=map[i][j].get_potential();
                map[i][j].add_potential(initial_potential + potential);
            }
        }
    }
}

void grid::next_move(int x, int y){
    if((x>=0)&&(x<N)&&(y>=0)&&(y<M)){
        //location is in array
        float output=map[x][y].get_potential();
        cout<<output<<" "<<output<<endl;
    }else{
        cout<<"failure"<<endl;
    }
}

void grid::clear(){
    if(map!=(nullptr)){
        //if a grid has been created continue to resetting all values to 0
        for (int i=0; i<N; ++i){
            for (int j=0; j<M; ++j){
                map[i][j].add_potential(0);
            }
        }
        cout<<"success"<<endl;
    }else{
        //if no grid then cannot set any values to 0.0, failure
        cout<<"failure"<<endl;

    }
}

void grid::update_k(float new_k){
    if(new_k>0){
        //if k valid
        k = new_k; //update k value
        char T;

        for (int x=0; x<N; ++x){
            for (int y=0; y<M; ++y){
                //iterate through all cells and recalculate all potentials
                char description=map[x][y].get_description();
                if((description=='G')||(description=='O')){
                    calculate_potential(x, y, T);
                }
            }
        }
        cout<<"success"<<endl;
    }else{
        //if k not valid
        cout<<"failure"<<endl;
    }
}