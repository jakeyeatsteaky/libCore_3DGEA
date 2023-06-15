#ifndef LIST_NODE_H
#define LIST_NODE_H

template <typename T>
class ListNode
{
public:
#if 0
Some notes on rule of 5:
    - copy constructor/assignment operator arguments should be passed by const reference
    - Move constructor/assignment operator arguments: rvalue referrence cannot be const
    - noexcept for move constructor/assignment operator
    - check if theyre the same for assignment operators
#endif

    inline ListNode(): m_data(), m_next(nullptr) {}
    inline ListNode(T& data): m_data(data), m_next(nullptr) {}
    inline ListNode(T&& data): m_data(std::move(data)), m_next(nullptr) {}
    inline ListNode(const ListNode& other): m_data(other.m_data), m_next(other.m_next){}
    inline const ListNode& operator=(const ListNode& other){
        if(this != &other) {
            this->m_data = other.m_data;
            this->m_next = other.m_next;
        }
        return *this;
    }
    inline ListNode(ListNode&& other) noexcept : m_data(std::move(other.m_data)), m_next(std::move(other.m_next)) {
        other.m_next = nullptr;
    }
    inline const ListNode& operator=(ListNode&& other) noexcept {
        if(this != &other) {
            this->m_data = std::move(other.m_data);
            this->m_next = std::move(other.m_next);
            other.m_next = nullptr;
        }
        return *this;
    } 
    inline ~ListNode() {
        ListNode* current = m_next;
        while(current) {
            ListNode* next = current->m_next;
            delete current;
            current = next;
        }
    }
    inline ListNode* GetNext() const { return m_next; }
    inline T GetData() const { return m_data; }
    inline void Insert(const T& data, size_t idx) {}
    inline void PushBack(const T& data);
    inline void Delete(size_t idx){}
    inline ListNode& Find(T value) const{}
    inline ListNode& GetNode(size_t idx) const{}


private:
    T m_data;
    ListNode* m_next;
};

template <typename T>
inline void ListNode<T>::PushBack(const T& data)
{
    ListNode* current = this;
    while(current->m_next)
        current = current->m_next;
    current->m_next = new ListNode(data);
}

#endif