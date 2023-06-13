#ifndef ARRAY_H
#define ARRAY_H

#include "GlobalIncludes.h"

#include <iostream>
#include <initializer_list>
#if 0 // =========== GLOBAL TO DO =============

    1) [x] implement Append method 
    2) [x] implement SetElement method
    3) [x] Create TEST Class and test cases from append and setelement
    4) [x] Test Append
    5) [x] Test SetElement -
    6) [x] Consider if SetElement works the way I want it to --> Is there a better way to create an array and preinitialize the values, versus creating the container, then individually setting each index to be a specific value.  This is how SetElement works and I'm not sure if thats a good' way of doing things.
    7) [x] Experimental Array_Deprecated - using Element struct to create isEmpty flags
    8) [x] Fix existing test cases for Array_Deprecated (non-experimental) -- append and Setelement are messed up from m_count = 0 on init
    **9) [x] Write test cases for Array_Ex -> this could be the default array
         [x] Finish sub TODO list within Array_Ex --> found in TEST.cpp line 66
   10) [x] Write out the things you learned in Array_Ex
   11) [x] Remove (expensive), and RemoveAll methods
   12) [x] Write out Remove methods
   13) [x] Finish NDEBUG case for Remove methods
   14) [ ] Finish the damn Array

    ...) [ ] Start documenting some of the things you learn on a website
                --> squarespace?  github pages?  
                --> Non-trivial things that you did not expect would be worthwhile
                    to mention: template issue with .cpp file, TEST class, Array_Deprecated method things and considerations

    --> write your own implementation, then confer with GenQuest to see if theres anything to add
    --> Debug and release mode error handling.

#endif

template <typename T>
class Array
{
public:

    struct Element {
        T m_data = 0;
        bool m_empty = true;

        inline Element(){             // Default Ctor
            new (&m_data) T(); // placement new to call the T ctor at the memory location of the Element member: data
            m_empty = true;        
        }

        inline Element(const T& data) {    // Ctor for Array initialiation list instantiation
            m_data = data;
            m_empty = false;
        }

        inline Element(const Element& copy) {
            m_data = copy.m_data;
            m_empty = copy.m_empty; 
        }

        inline Element(const Element&& move) noexcept{
            m_data = std::move(move.m_data);
            m_empty = move.m_empty;
        }

        inline Element& operator= (const Element& other) {
            if(this != &other) {
                m_data = other.m_data;
                m_empty = other.m_empty;
            }
            return *this;
        }

        inline Element& operator= (const Element&& other) noexcept {
            if(this != &other)
            {
                m_data = std::move(other.m_data);
                m_empty = other.m_empty;
            }
            return *this;
        }

        ~Element() {
            if (!m_empty) {
                std::cout << "Destroying Element containing " << sizeof(T) << " bytes.  Value = " << m_data << std::endl;
                m_data.~T();
                
            }
        }
    };

    inline Array(size_t size = 5, size_t growBy = 5): 
        m_count(0), 
        m_size(size), 
        m_growBy(growBy) 
    {
        m_memBlock = new Element[m_size]; // "new" operator calls default constructors for T.  Using malloc requires for loop of 'placement new' to initialize elements with default constructor
    }

    inline Array(T* data, size_t numElements, size_t growBy = 5) :
        m_count(0),
        m_size(numElements),
        m_growBy(growBy)
    {
        try {
            if (data == nullptr) 
                throw std::invalid_argument("Invalid data pointer: nullptr");
        } 
        catch (const std::exception& ex) {
            std::cout << "Exception occurred: " << ex.what() << std::endl;
            m_memBlock = new Element[1];
            this->SetElement(0, static_cast<T>(0xDEADBEEF));
            return;
        }

        try {
            if (numElements == 0) 
                throw std::invalid_argument("Invalid number of elements: 0");
        }
        catch (const std::exception& ex) {
            std::cout << "Exception occurred: " << ex.what() << std::endl;
            m_memBlock = new Element[1];
            m_size = 1;
            this->SetElement(0, static_cast<T>(0xDEADBEEF));
            return;
        }

        m_memBlock = new Element[m_size];
        for(size_t i = 0; i < m_size; ++i) {
            this->SetElement(i, data[i]);
        }
        
    }

    inline Array(std::initializer_list<T> list) : Array(list.begin(), list.end()) {}

    inline Array(typename std::initializer_list<T>::const_iterator begin, 
                    typename std::initializer_list<T>::const_iterator end, size_t growBy = 5):
                    m_memBlock(nullptr),
                    m_count(0),
                    m_size(0),
                    m_growBy(growBy)
    {
        size_t numElements = std::distance(begin, end);
        m_size = numElements;
        m_memBlock = new Element[m_size];

        for(size_t i = 0; i < m_size; ++i) {
            m_memBlock[i] = Element(*begin);
            begin++;
            m_count++;
        }
    }

    inline Array(const Array& other): 
        m_count(other.m_count), 
        m_size(other.m_size), 
        m_growBy(other.m_growBy) 
    {    
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

    inline Array& operator=(const Array& copy) {
        if(this == &copy)
            return *this;
        delete[] m_memBlock;

        m_size = copy.m_size;
        m_count = copy.m_count;
        m_growBy = copy.m_growBy;

        m_memBlock = new Element[m_count];
        for(size_t i = 0; i < m_size; ++i) {
            m_memBlock[i] = copy.m_memBlock[i];
        }

        return *this;
    }

    inline Array& operator=(const Array&& move) {
        if(this != &move) {
            m_memBlock = std::exchange(move.m_memBlock, nullptr);
            m_count = std::exchange(move.m_count, 0);
            m_size = std::exchange(move.m_size, 0);
            m_growBy = std::exchange(move.m_growBy, 0);
        }
        return *this;
    }

    inline ~Array() {
        delete[] m_memBlock;
    }

    size_t Size() const;
    Element* Data();
    const Element* Data() const;

    Element& operator[] (size_t idx);
    const Element& operator[] (size_t idx) const;
    const T& At(size_t idx) const;
    void Append(const T& element_data);
    void SetElement(size_t idx, const T& element_data);
    void Remove(const size_t idx);
    void RemoveAll();
    const size_t GetGrowBy() const;
    const size_t GetCount() const;    
    const void PrintContents() const;    

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
inline typename Array<T>::Element* Array<T>::Data()
{
    return m_memBlock;
}

template <typename T>
inline const typename Array<T>::Element* Array<T>::Data() const
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
inline typename Array<T>::Element& Array<T>::operator[] (size_t idx)
{
    #ifdef DEBUG
        try {
            if(idx > m_size - 1 || idx < 0) 
                throw std::out_of_range("Array index out of bounds\n");
        } catch(const std::exception& ex) {
            std::cout << "Exception occurred: " << ex.what();
            return m_memBlock[0];
        }
    #else 
        if(idx > m_size) 
            idx = m_size;
        if(idx < 0) 
            idx = 0;
    #endif 
        return m_memBlock[idx]; 
}

template <typename T>
inline const typename Array<T>::Element& Array<T>::operator[] (size_t idx) const
{
    #ifdef DEBUG
        try {
            if(idx > m_size - 1 || idx < 0) 
                throw std::out_of_range("Array index out of bounds\n");
        } catch(const std::exception& ex) {
            std::cout << "Exception occurred: " << ex.what() << std::endl;
            return m_memBlock[0];
        }
    #else 
        if(idx > m_size) 
            idx = m_size;
        if(idx < 0) 
            idx = 0;
    #endif 
        return m_memBlock[idx]; 
}

template <typename T>
inline const T& Array<T>::At(size_t idx) const 
{
    return m_memBlock[idx].m_data;
}

template <typename T>
inline void Array<T>::Append (const T& element_data)
{
    // Append(...) will add the T data to the next available space in this Array object.  
    // if the Array is "full", it will resize to accomodate the space in which case
    // T data will be placed at index = previous m_size;
    if(m_count == m_size)
    {
        size_t newSize = m_count + m_growBy;
        Element* tempBlock = new (std::nothrow) Element[newSize]; //std::nothrow returns nullptr if resize allocation fails
        if(tempBlock)
        {
            for(size_t i = 0; i < m_count; ++i) {
            #if 0
                // Deep copy of the data in the existing Array - less efficient
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
    m_memBlock[m_count] = Element(element_data);
    m_count++;
}

template <typename T>
inline void Array<T>::SetElement(size_t idx, const T& element_data)
{
    // the Data element_data is set at the specified idx
    // if Idx is > size, the array will be resized so that idx = newSize-1
    if(idx > m_size - 1) {
        size_t newSize = idx + 1;
        Element* tempBlock = new (std::nothrow) Element[newSize];
        if(tempBlock) {
            for(size_t i = 0; i < m_size; ++i) {
                tempBlock[i] = std::move(m_memBlock[i]);
            }
            delete[] m_memBlock;
            m_memBlock = tempBlock;
            m_size = newSize;
            m_count++;// SetElement only increments the Size of the Array if the index of the element being set is bigger than th current size
        }
        else {
            throw std::runtime_error("Memory Allocation failed: Array::SetElement(size_t, const T&)\n");
        }
    }

    m_memBlock[idx].m_data = element_data;
    if(m_memBlock[idx].m_empty) {
        m_memBlock[idx].m_empty = false;
        m_count++;
    }
}

template <typename T>
inline const void Array<T>::PrintContents() const 
{
    for(size_t i = 0; i < m_count; ++i) {
        std::cout << m_memBlock[i].m_data << std::endl;
    }
}

template <typename T>
inline void Array<T>::Remove(const size_t idx)
{
    #ifdef DEBUG
        if(idx < m_size)
        {
            bool decrementCount = !(m_memBlock[idx].m_empty);
            for(size_t i = idx; i < m_size - 1; ++i) {
                m_memBlock[i].~Element();   // if T of Element has dynamically allocated memory, desctructor must be called
                m_memBlock[i] = m_memBlock[i + 1];
            }
            this->m_memBlock[m_size-1].~Element();
            this->m_memBlock[m_size-1] = Element();
            this->m_memBlock[m_size-1].m_empty = true;

            if(decrementCount)
                m_count--;
        }
        else
            throw std::out_of_range("Index not within range for Array\n");
    #else
        if(!(idx < m_size))
            idx = m_size-1;
     
        bool decrementCount = !(m_memBlock[idx].m_empty);
        for(size_t i = idx; i < m_size - 1; ++i) {
            m_memBlock[i].~Element();   // if T of Element has dynamically allocated memory, desctructor must be called
            m_memBlock[i] = m_memBlock[i + 1];
        }
        this->m_memBlock[m_size-1].~Element();
        this->m_memBlock[m_size-1] = Element();
        this->m_memBlock[m_size-1].m_empty = tru 
        if(decrementCount)
            m_count--;
    #endif
}

template <typename T>
inline void Array<T>::RemoveAll()
{
    int i = m_size - 1;
    for(; i >= 0; i--) {
        this->Remove(i);
    }
}




#endif