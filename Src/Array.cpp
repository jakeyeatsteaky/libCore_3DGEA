#include "Array.h"

template <typename T>
size_t Array<T>::Size() const {
    return m_quantity;
}

template <typename T>
T* Array<T>::Data() {
    return m_memBlock;
}

template <typename T>
const T* Array<T>::Data() const {
    return m_memBlock;
}

template <typename T>
T& Array<T>::operator[] (size_t idx) {
#ifdef DEBUG
    if(idx > m_maxQuantity - 1 || idx < 0) 
        throw std::out_of_range("Array index out of bounds\n");
#else 
    if(idx > m_maxQuantity) 
        idx = m_maxQuantity;
    if(idx < 0) 
        idx = 0;
#endif 
    return m_memBlock[idx]; 
}

template <typename T>
const T& Array<T>::operator[] (size_t idx) const {
#ifdef DEBUG
    if(idx > m_maxQuantity - 1 || idx < 0) 
        throw std::out_of_range("Array index out of bounds\n");
#else 
    if(idx > m_maxQuantity) 
        idx = m_maxQuantity;
    if(idx < 0) 
        idx = 0;
#endif 
    return m_memBlock[idx]; 
}

template <typename T>
void Array<T>::Append(const T& element)
{
#ifdef DEBUG

#else

#endif
}

template <typename T>
void Array<T>::SetElement(size_t idx, const T& element)
{

}
