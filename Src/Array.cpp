// #include "Array.h"

// template <typename T>
// size_t Array<T>::Size() const {
//     return m_quantity;
// }

// template <typename T>
// T* Array<T>::Data() {
//     return m_memBlock;
// }

// template <typename T>
// const T* Array<T>::Data() const {
//     return m_memBlock;
// }

// template <typename T>
// T& Array<T>::operator[] (size_t idx) {
// #ifdef DEBUG
//     if(idx > m_maxQuantity - 1 || idx < 0) 
//         throw std::out_of_range("Array index out of bounds\n");
// #else 
//     if(idx > m_maxQuantity) 
//         idx = m_maxQuantity;
//     if(idx < 0) 
//         idx = 0;
// #endif 
//     return m_memBlock[idx]; 
// }

// template <typename T>
// const T& Array<T>::operator[] (size_t idx) const {
// #ifdef DEBUG
//     if(idx > m_maxQuantity - 1 || idx < 0) 
//         throw std::out_of_range("Array index out of bounds\n");
// #else 
//     if(idx > m_maxQuantity) 
//         idx = m_maxQuantity;
//     if(idx < 0) 
//         idx = 0;
// #endif 
//     return m_memBlock[idx]; 
// }

// template <typename T>
// void Array<T>::Append(const T& element)
// {
//     // Add element to array at position = quantity, and will increment quantity by 1
//     // If the memory block for this array is full, it will dynamically resize to accomodate the new element
//     if(m_quantity == m_maxQuantity)
//     {
//         size_t newSize = m_quantity + m_growBy;
//         T* tempBlock = new (std::nothrow) T[newSize]; //std::nothrow returns nullptr if resize allocation fails
//         if(tempBlock)
//         {
//             for(size_t i = 0; i < m_quantity; ++i) {
//             #if 0
//                 // Deep copy of the data in the existing array - less efficient
//                 // There is support for move semantics so we're gonna use that
//                 // T needs to support move semantics for this to work,
//                 // Automatic fail state will be to perform a deep copy so additional
//                 // error checking is not necessary
//                 tempBlock[i] = m_memBlock[i];
//             #else
//                 tempBlock[i] = std::move(m_memBlock[i]);
//             #endif
            
//             }
//             delete[] m_memBlock;
//             m_memBlock = tempBlock;
//             m_maxQuantity = newSize;
//         }

//         else {
//             throw std::runtime_error("Memory Allocation Failed: Array::Append()\n");
//         }
//     }

//     m_memBlock[m_quantity] = element;
//     m_quantity++;
// }

// template <typename T>
// void Array<T>::SetElement(size_t idx, const T& element)
// {
//     // Set element at any index.  If the index is outside the size of the array, resize so that idx = newQuantity-1
//     if(idx > m_maxQuantity) {
//         size_t newSize = idx + 1;
//         T* tempBlock = new (std::nothrow) T[newSize];
//         if(tempBlock) {
//             for(size_t i = 0; i < m_maxQuantity; ++i) {
//                 tempBlock[i] = std::move(m_memBlock[i]);
//             }
//             delete[] m_memBlock;
//             m_memBlock = tempBlock;
//             m_maxQuantity = newSize;
//         }

//         else {
//             throw std::runtime_error("Memory Allocation failed: Array::SetElement(size_t, const T&)\n");
//         }
//     }
//     else {
//         m_memBlock[idx] = element;
//     }
//     m_quantity++;
// }
