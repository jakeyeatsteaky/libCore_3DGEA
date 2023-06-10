#ifndef ARRAY_DEPRECATED_H
#define ARRAY_DEPRECATED_H
#include <iostream>


template <typename T>
class Array_Deprecated
{
public:


    inline Array_Deprecated(size_t size = 1, size_t growBy = 1): 
        m_count(0), 
        m_size(size), 
        m_growBy(growBy) 
    {
        m_memBlock = new T[m_size]; // "new" operator calls default constructors for T.  Using malloc requires for loop of 'placement new' to initialize elements with default constructor
    }

    inline Array_Deprecated(const Array_Deprecated& other): 
        m_count(other.m_count), 
        m_size(other.m_size), 
        m_growBy(other.m_growBy) 
    {
        
        m_memBlock = new T[m_size];
        for(size_t i = 0; i < m_size; ++i) {
            m_memBlock[i] = other.m_memBlock[i];
        }        
    }

    inline Array_Deprecated(Array_Deprecated&& other) noexcept :
        m_memBlock(other.m_memBlock),
        m_count(other.m_count),
        m_size(other.m_size),
        m_growBy(other.m_growBy) {
            other.m_memBlock = nullptr;
            other.m_count = 0;
            other.m_size = 0;
        }

    inline ~Array_Deprecated() {
        delete[] m_memBlock;
    }

    inline Array_Deprecated& operator=(const Array_Deprecated& other) {
        if (&other == this)
            return *this;
        
        delete[] m_memBlock; // free existing resources

        m_size = other.m_size;
        m_count = other.m_count;
        m_growBy = other.m_growBy;

        m_memBlock = new T[m_count];
        for(size_t i = 0; i < m_count; ++i) {
            m_memBlock[i] = other.m_memBlock[i];
        }

        return *this;
    }

    inline Array_Deprecated& operator=(Array_Deprecated&& other) noexcept {
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
    T* m_memBlock;
    bool* m_isSet;
    size_t m_count;
    size_t m_size;
    size_t m_growBy;
};


template <typename T>
inline size_t Array_Deprecated<T>::Size() const
{
    return m_size;
}

template <typename T>
inline T* Array_Deprecated<T>::Data()
{
    return m_memBlock;
}

template <typename T>
inline const T* Array_Deprecated<T>::Data() const
{
    return m_memBlock;
}

template <typename T>
inline const size_t Array_Deprecated<T>::GetCount() const
{
    return m_count;
}

template <typename T>
inline const size_t Array_Deprecated<T>::GetGrowBy() const
{
    return m_growBy;
}

template <typename T>
inline T& Array_Deprecated<T>::operator[] (size_t idx)
{
    #ifdef DEBUG
        if(idx > m_size - 1 || idx < 0) 
            throw std::out_of_range("Array_Deprecated index out of bounds\n");
    #else 
        if(idx > m_size) 
            idx = m_size;
        if(idx < 0) 
            idx = 0;
    #endif 
        return m_memBlock[idx]; 
}

template <typename T>
inline const T& Array_Deprecated<T>::operator[] (size_t idx) const
{
    #ifdef DEBUG
        if(idx > m_size - 1 || idx < 0) 
            throw std::out_of_range("Array_Deprecated index out of bounds\n");
    #else 
        if(idx > m_size) 
            idx = m_size;
        if(idx < 0) 
            idx = 0;
    #endif 
        return m_memBlock[idx]; 
}

template <typename T>
inline void Array_Deprecated<T>::Append (const T& element)
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
            throw std::runtime_error("Memory Allocation Failed: Array_Deprecated::Append()\n");
        }
    }
    m_memBlock[m_count] = element;
    m_count++;
}

template <typename T>
inline void Array_Deprecated<T>::SetElement(size_t idx, const T& element)
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
            throw std::runtime_error("Memory Allocation failed: Array_Deprecated::SetElement(size_t, const T&)\n");
        }
    }
    else {
        m_memBlock[idx] = element;
    }
}





#endif