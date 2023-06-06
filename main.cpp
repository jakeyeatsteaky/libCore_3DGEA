#include <iostream>
#include "Array.h"
#include "ArrayExperiment.h"
#include "TEST.h"   

int main(int argc, char** argv)
{
    //TestCases::TestArray(); 
    //Array<int> array(5,5);
    //Array<int> array1 = array;
    //std::cout << array.Data() << " " << array.Size() << std::endl;

    Array_Ex<int> array1(5,5);
    array1.QuickAdd(0, 1);
    array1.QuickAdd(1, 2);
    array1.QuickAdd(2, 3);
    array1.QuickAdd(3, 4);

    return 0;
}