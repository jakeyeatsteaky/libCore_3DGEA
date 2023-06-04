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
    return 0;
}