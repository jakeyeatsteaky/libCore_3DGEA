#ifndef ARRAY_EXPERIMENT_H
#define ARRAY_EXPERIMENT_H

#include <iostream>
#if 0 // =========== GLOBAL TO DO =============

    1) [x] implement Append method 
    2) [x] implement SetElement method
    3) [x] Create TEST Class and test cases from append and setelement
    4) [x] Test Append
    5) [x] Test SetElement -
    6) [ ] Consider if SetElement works the way I want it to --> Is there a better way to create an array and preinitialize the values, versus creating the container, then individually setting each index to be a specific value.  This is how SetElement works and I'm not sure if thats a good' way of doing things.
    7)      [ ] Create "element set" bit field to be able to correctly increment count with set element
    8) [ ] Continue on makin the rest of the Array Class

    ...) [ ] Start documenting some of the things you learn on a website
                --> squarespace?  github pages?  
                --> Non-trivial things that you did not expect would be worthwhile
                    to mention: template issue with .cpp file, TEST class, Array method things and considerations

    --> write your own implementation, then confer with GenQuest to see if theres anything to add
    --> Debug and release mode error handling.

#endif

template <typename T>
class Array
{
public:

    struct Element {
        T value;
        bool empty;

        Element(){
            new (&value) T();
            empty = true;
        }

        ~Element() {
            if (!empty) {
                value.~T();
            }
        }
    };

    inline Array(size_t size = 1, size_t growBy = 1): m_count(0), m_size(size), m_growBy(growBy) {
        m_memBlock = new Element[m_size]; // "new" operator calls default constructors for T.  Using malloc requires for loop of 'placement new' to initialize elements with default constructor
    }

    inline QuickAdd(size_t idx, const T& element) {
        m_memBlock[idx] = Element(std::move(element))
    }

    inline Array(const Array& other): m_count(other.m_count), m_size(other.m_size), m_growBy(other.m_growBy) {
        
        m_memBlock = new Element[m_size];
        for(size_t i = 0; i < m_size; ++i) {
            m_memBlock[i] = other.m_memBlock[i];
        }        
    }

    inline Array(Array&& other) noexcept :
        m_memBlock(other.m_memBlock),
        m_count(other.m_count),
        m_size(other.m_size),
        m_growBy(other.m_growBy) {
            other.m_memBlock = nullptr;
            other.m_count = 0;
            other.m_size = 0;
        }

    inline ~Array() {
        delete[] m_memBlock;
    }

    inline Array& operator=(const Array& other) {
        if (&other == this)
            return *this;
        
        delete[] m_memBlock; // free existing resources

        m_size = other.m_size;
        m_count = other.m_count;
        m_growBy = other.m_growBy;

        m_memBlock = new Element[m_count];
        for(size_t i = 0; i < m_count; ++i) {
            m_memBlock[i] = other.m_memBlock[i];
        }

        return *this;
    }

    inline Array& operator=(Array&& other) noexcept {
        if(this != &other) {
            m_memBlock = std::exchange(other.m_memBlock, nullptr);
            m_count = std::exchange(other.m_count, 0);
            m_size = std::exchange(other.m_size, 0);
            m_growBy = std::exchange(other.m_growBy, 0);
        }
        return *this;
    }

    size_t Size() const;
    T* Data();
    const T* Data() const;
    T& operator[] (size_t idx);
    const T& operator[] (size_t idx) const;
    void Append(const T& element);
    void SetElement(size_t idx, const T& element);
    size_t const GetGrowBy() const;
    size_t const GetCount() const;    

private:
    Element* m_memBlock;
    size_t m_count;
    size_t m_size;
    size_t m_growBy;
};


template <typename T>
inline size_t Array<T>::Size() const
{
    return m_size;
}

template <typename T>
inline T* Array<T>::Data()
{
    return m_memBlock;
}

template <typename T>
inline const T* Array<T>::Data() const
{
    return m_memBlock;
}

template <typename T>
inline const size_t Array<T>::GetCount() const
{
    return m_count;
}

template <typename T>
inline const size_t Array<T>::GetGrowBy() const
{
    return m_growBy;
}

template <typename T>
inline T& Array<T>::operator[] (size_t idx)
{
    #ifdef DEBUG
        if(idx > m_size - 1 || idx < 0) 
            throw std::out_of_range("Array index out of bounds\n");
    #else 
        if(idx > m_size) 
            idx = m_size;
        if(idx < 0) 
            idx = 0;
    #endif 
        return m_memBlock[idx]; 
}

template <typename T>
inline const T& Array<T>::operator[] (size_t idx) const
{
    #ifdef DEBUG
        if(idx > m_size - 1 || idx < 0) 
            throw std::out_of_range("Array index out of bounds\n");
    #else 
        if(idx > m_size) 
            idx = m_size;
        if(idx < 0) 
            idx = 0;
    #endif 
        return m_memBlock[idx]; 
}

template <typename T>
inline void Array<T>::Append (const T& element)
{
    // Add element to array at position = quantity, and will increment quantity by 1
    // If the memory block for this array is full, it will dynamically resize to accomodate the new element
    if(m_count == m_size)
    {
        size_t newSize = m_count + m_growBy;
        T* tempBlock = new (std::nothrow) T[newSize]; //std::nothrow returns nullptr if resize allocation fails
        if(tempBlock)
        {
            for(size_t i = 0; i < m_count; ++i) {
            #if 0
                // Deep copy of the data in the existing array - less efficient
                // There is support for move semantics so we're gonna use that
                // T needs to support move semantics for this to work,
                // Automatic fail state will be to perform a deep copy so additional
                // error checking is not necessary
                tempBlock[i] = m_memBlock[i];
            #else
                tempBlock[i] = std::move(m_memBlock[i]);
            #endif
            }
            delete[] m_memBlock;
            m_memBlock = tempBlock;
            m_size = newSize;
        }
        else {
            throw std::runtime_error("Memory Allocation Failed: Array::Append()\n");
        }
    }
    m_memBlock[m_count] = element;
    m_count++;
}

template <typename T>
inline void Array<T>::SetElement(size_t idx, const T& element)
{
    // Set element at any index.  If the index is outside the size of the array, resize so that idx = newQuantity-1
    if(idx > m_size) {
        size_t newSize = idx + 1;
        T* tempBlock = new (std::nothrow) T[newSize];
        if(tempBlock) {
            for(size_t i = 0; i < m_size; ++i) {
                tempBlock[i] = std::move(m_memBlock[i]);
            }
            delete[] m_memBlock;
            m_memBlock = tempBlock;
            m_size = newSize;
            m_count++;// SetElement only increments the Size of the array if the index of the element being set is bigger than th current size
        }
        else {
            throw std::runtime_error("Memory Allocation failed: Array::SetElement(size_t, const T&)\n");
        }
    }
    else {
        m_memBlock[idx] = element;
    }
}



#endif