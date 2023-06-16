#include <iostream>
#include "Array.h"
#include "HashTable.h"
#include "ListNode.h"
#include "GlobalIncludes.h"
#include "TEST.h"   

#if 0 
========================= GLOBAL TODO ===========================
    1) [ ] Figure out how to structure HashItem as a composition of ListNode
    2) [ ] Implement list node basic methods
            [ ] Deletion
            [ ] Searching
            [x] PushBack
    3) [ ] Test ListNode
            [x] Ctors
            [x] Dtor
            [x] copy
            [x] Move
            [ ] Delete
            [ ] Find
            [x] PushBack
    4) [ ] Element destructor >> ostream bug.  See: HashTable.h -- NOT_SURE_BOUT_DIS
    5) [ ] Finish Hash Table 

#endif

int main(int argc, char** argv)
{
    TestCases::RunTestSuite();

    return 0;
}