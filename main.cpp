#include <iostream>
#include "Array.h"

#include "TEST.h"   

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
    TestCases::TestArray(); 
    Array<int> array(5,5);
    Array<int> array1 = array;
    std::cout << array.Data() << " " << array.Size() << std::endl;
    return 0;
}