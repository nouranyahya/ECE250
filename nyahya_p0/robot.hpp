#ifndef ROBOT_H
#define ROBOT_H

class robot
{

    public:
        robot();

        float get_potential();
        void add_potential(float new_potential);
        char get_description();
        void add_description(char new_description);

    private:

        float potential; //value of potential in cell
        char description; //G/O/N for type of object found in the cell
};

#endif
