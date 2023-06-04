#ifndef ARRAY_H
#define ARRAY_H
#include <iostream>
#if 0 // =========== GLOBAL TO DO =============

    1) [x] implement Append method 
    2) [x] implement SetElement method
    3) [ ] Create TEST Class and test cases from append and setelement
    4) [ ] Test Append
    5) [ ] Test SetElement -

    --> write your own implementation, then confer with GenQuest to see if theres anything to add
    --> Debug and release mode error handling.

#endif

template <typename T>
class Array
{
public:

    Array(size_t quantity = 1, size_t growBy = 1): m_quantity(quantity), m_maxQuantity(m_quantity), m_growBy(growBy) {
        m_memBlock = new T[m_quantity];
        // new calls T object default constructors under the hood to initialize this memory 
    }

    Array(const Array& other): m_quantity(other.m_quantity), m_maxQuantity(other.m_maxQuantity), m_growBy(other.m_growBy) {
        
        m_memBlock = new T[m_quantity];
        for(size_t i = 0; i < m_quantity; ++i) {
            m_memBlock[i] = other.m_memBlock[i];
        }        
    }

    Array(Array&& other) noexcept :
        m_memBlock(other.m_memBlock),
        m_quantity(other.m_quantity),
        m_maxQuantity(other.m_maxQuantity),
        m_growBy(other.m_growBy) {
            other.m_memBlock = nullptr;
            other.m_quantity = 0;
            other.m_maxQuantity = 0;
        }

    ~Array() {
        delete[] m_memBlock;
    }

    Array& operator=(const Array& other) {
        if (&other == this)
            return *this;
        
        delete[] m_memBlock; // free existing resources

        m_maxQuantity = other.m_maxQuantity;
        m_quantity = other.m_quantity;
        m_growBy = other.m_growBy;

        m_memBlock = new T[m_quantity];
        for(size_t i = 0; i < m_quantity; ++i) {
            m_memBlock[i] = other.m_memBlock[i];
        }

        return *this;
    }

    Array& operator=(Array&& other) noexcept {
        if(this != &other) {
            m_memBlock = std::exchange(other.m_memBlock, nullptr);
            m_quantity = std::exchange(other.m_quantity, 0);
            m_maxQuantity = std::exchange(other.m_maxQuantity, 0);
            m_growBy = std::exchange(other.m_growBy, 0);
        }
        return *this;
    }

    size_t Size() const;
    T* Data();
    const T* Data() const;
    T& operator[] (size_t idx);
    const T& operator[] (size_t idx) const;
    void Append (const T& element);
    void SetElement(size_t idx, const T& element);


private:
    T* m_memBlock;
    size_t m_quantity;
    size_t m_maxQuantity;
    size_t m_growBy;
};




#endif