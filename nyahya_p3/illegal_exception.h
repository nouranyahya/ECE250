#ifndef ILLEGAL_EXCEPTION_H
#define ILLEGAL_EXCEPTION_H

//class for handling illegal arguments (uppercase letters)
class illegal_exception{

    private:
    const char* message;  //stores error message

    public:
    illegal_exception():message("illegal argument"){} //constructor - initialize with message
    const char* what() const {
        return message;
    }
};

#endif