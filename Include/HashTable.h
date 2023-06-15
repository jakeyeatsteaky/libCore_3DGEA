#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include "GlobalIncludes.h"
#include "ListNode.h"
#include "Array.h"




template <typename TKey, typename TValue>
class HashTable
{
public:
    struct HashItem
    {
        TKey hi_key;
        TValue hi_value;
        ListNode<HashItem>* hi_next;
    };

    HashTable() {};



    // This fixes a compilation bug from the ~Element() print statement.  maybe from sizeof(T)?
    // I don't know how this works or why friend is there
    // Tag: NOT_SURE_BOUT_DIS
    friend std::ostream& operator<<(std::ostream& os, const HashItem& item)
    {
        os << "Key: " << item.hi_key << ", Value: " << item.hi_value;
        return os;
    }

private:
    Array<HashItem> m_table;


};






#endif