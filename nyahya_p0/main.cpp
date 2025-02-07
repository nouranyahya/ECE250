
#include "grid.hpp"

using namespace std;

int main(){

    int N;
    int M;
    char T;
    int x;
    int y;

    grid* map=nullptr; //pointer is nullptr since no map yet
    string command; //store command from user input

    while (cin>>command){
        if(command=="CREATE"){
            cin>>N>>M;
            if (map!=nullptr){
                delete map;
            }
            map=new grid(N,M);
            cout<<"success"<<endl;
        }else if(command=="POINT"){
            cin>>T>>x>>y;
            map->add_g_o(x, y, T);
        }else if(command=="MOVE"){
            cin>>x>>y;
            map->next_move(x,y);
        }else if(command=="CLEAR"){
            map->clear();
        }else if(command=="UPDATE"){
            float new_k;
            cin>>new_k;
            map->update_k(new_k);
        }else if(command=="EXIT"){
            break;
        }
    }
    delete map;
    return 0;
}