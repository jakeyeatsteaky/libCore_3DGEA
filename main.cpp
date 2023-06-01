#include <iostream>
#include "Array.h"


int main(int argc, char** argv)
{
    std::cout << "Hello World!\n";
    Array<int> array;
    Array<int> arrayray(4,4);
    std::cout << sizeof(array) << " " << sizeof(arrayray) << std::endl;
    return 0;
}