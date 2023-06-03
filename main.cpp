#include <iostream>
#include "Array.h"


struct Object
{
    int a;
    int b;
    float c;
    union {
        int aa;
        float bb;
    };
};


int main(int argc, char** argv)
{
    Array<int> defaultCtor;
    Array<int> ogArray(100, 100);
    Array<int> deepCopy(ogArray);
    Array<int> assignCopy = deepCopy;
    Array<int> moveCopy(std::move(ogArray));
    Array<int> assignMove = moveCopy;


    std::cout << "Default CTor: " << &defaultCtor 
              << "\nOG Array: " << &ogArray
              << "\nDeep Copy: " << &deepCopy
              << "\nAssign Copy: " << &assignCopy
              << "\nMove Copy: " << &moveCopy
              << "\nAssign Move: " << &assignMove << std::flush << std::endl;


    return 0;
}