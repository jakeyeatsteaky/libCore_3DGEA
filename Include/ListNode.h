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
    inline ListNode(const T& data): m_data(data), m_next(nullptr) {}
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
            current = next;
            delete current;
        }
    }
    inline ListNode* GetNext() const { return m_next; }
    inline T GetData() const { return m_data; }
    inline void PushBack(const T& data);
    inline ListNode* Delete(size_t idx);
    inline const ListNode* Find(const T& value) const;
    inline const ListNode* GetNode(size_t idx) const;
    inline void PrintNodes() const;


private:
    T m_data;
    ListNode* m_next;

};

template <typename T>
inline ListNode<T>* ListNode<T>::Delete(size_t idx)
{
    size_t count = 0;
    bool objectDeleted = false;
    if(idx == 0 && this->m_next) {
        ListNode* nodeToDelete = this->m_next;
        this->m_data = nodeToDelete->m_data;
        this->m_next = nodeToDelete->m_next;
        delete nodeToDelete;
        return this;
    }

    ListNode<T>* current = this;
    ListNode<T>* head = current;
    count++;
    while(current) {
        if(count == idx) {
            ListNode<T>* nodeToDelete = current->m_next;
            current->m_next = nodeToDelete->m_next;
            delete nodeToDelete;
            objectDeleted = true;
            break;
        }
        else {
            count++;
            current = current->m_next;
        }
    }

    if(!objectDeleted)
        std::cout << "Index: " << idx << " not found in List\n";

    return head;
    
}

template <typename T>
inline void ListNode<T>::PushBack(const T& data)
{
    ListNode* current = this;
    while(current->m_next)
        current = current->m_next;
    current->m_next = new ListNode<T>(data);
}

template <typename T>
inline void ListNode<T>::PrintNodes() const 
{
    std::cout << "Node 1: " << this->m_data << std::endl;
    ListNode* current = this->m_next;
    int count = 1;
    while(current){
        std::cout << "Node " << ++count << ": " << current->m_data << std::endl;
        current = current->m_next;
    }
    std::cout << " ---------------------\n";
}

template <typename T> 
inline const ListNode<T>* ListNode<T>::GetNode(size_t idx) const 
{
    if(idx == 0)
        return this;

    ListNode* current = this->m_next;
    size_t count = 1;
    while(current) {
        if (count == idx)
            return current;
        current = current->m_next;
        ++count;
    }
    std::cout << "Index: " << idx << " does not exist in this list\n";
    return this;
}

template <typename T>
inline const ListNode<T>* ListNode<T>::Find(const T& value) const 
{
    if(value == this->m_data)
        return this;

    ListNode* current = this->m_next;
    while(current) {
        if (current->m_data == value)
            return current;
        current = current->m_next;
    }
    std::cout << "No node with value: " << value << " exists in this List\n";
    return nullptr;
}


#endif