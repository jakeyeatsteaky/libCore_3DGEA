#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>

template <typename T>
class Array
{
public:
    Array<T>() = default;
    Array<T>(size_t quantity, size_t growBy) : m_quantity(quantity), m_growBy(growBy) {}
    ~Array<T>() = default;


private:
    size_t m_quantity;
    size_t m_growBy;
};



#endif