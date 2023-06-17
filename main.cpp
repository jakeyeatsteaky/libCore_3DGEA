#include <iostream>
#include "Array.h"
#include "HashTable.h"
#include "ListNode.h"
#include "GlobalIncludes.h"
#include "TEST.h"   

#if 0 
========================= GLOBAL TODO ===========================
    1) [ ] Figure out how to structure HashItem as a composition of ListNode
    2) [x] Implement list node basic methods
            [x] Deletion
            [x] Searching
            [x] PushBack
    3) [x] Test ListNode
            [x] Ctors
            [x] Dtor
            [x] copy
            [x] Move
            [x] Delete
            [x] Find
            [x] PushBack
    5) [ ] Finish Hash Table
            [ ] HashItem Struct - > what are the main methods needed?  Definitely need comparison operator 

    N) [ ] Element destructor >> ostream bug.  See: HashTable.h -- NOT_SURE_BOUT_DIS

#endif

int main(int argc, char** argv)
{
    TestCases::RunTestSuite();

    return 0;
}