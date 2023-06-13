#include <iostream>
#include "Array.h"
#include "HashTable.h"
#include "ListNode.h"
#include "GlobalIncludes.h"
#include "TEST.h"   

int main(int argc, char** argv)
{
    TestCases::RunTestSuite();
    HashTable<int,int> hash;
    ListNode<int> node;

    return 0;
}