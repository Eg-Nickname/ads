#ifndef OrderedList_H
#define OrderedList_H

#include <cassert> // assert()
#include <concepts>
#include <cstddef>
#include <iostream> // deklaracje strumieni cout, cin, cerr
#include <stdexcept>

// Ensure our inner type is comparable
template <std::totally_ordered T>
struct OrderedNode {
    T value;
    OrderedNode* next;
    OrderedNode() : value(T()), next(nullptr) {} // konstruktor domyslny
    OrderedNode(const T& item, OrderedNode* ptr = nullptr)
        : value(item), next(ptr) {}
    OrderedNode(T&& item, OrderedNode* ptr = nullptr)
        : value(std::move(item)), next(ptr) {}
    ~OrderedNode() {} // destruktor
};

template <std::totally_ordered T>
class OrderedList {
    OrderedNode<T>*head, *tail;
    std::size_t length;

    public:
    OrderedList() : head(nullptr), tail(nullptr), length(0) {}
    ~OrderedList(); // tu trzeba wyczyscic wezly

    OrderedList(const OrderedList& other); // copy constructor
    // usage:   OrderedList<int> list2(list1);

    OrderedList(OrderedList&& other); // move constructor NIEOBOWIAZKOWE
    // usage:   OrderedList<int> list2(std::move(list1));

    OrderedList& operator=(
        const OrderedList& other); // copy assignment operator, return *this
    // usage:   list2 = list1;

    OrderedList&
    operator=(OrderedList&& other); // move assignment operator, return *this
    // usage:   list2 = std::move(list1); NIEOBOWIAZKOWE

    bool empty() const { return head == nullptr; }
    std::size_t size() const; // O(n) bo trzeba policzyc

    // T& front() const { return head->value; } // zwraca poczatek, nie usuwa

    /// Fixed version
    T& front() const {
        if (head) {
            return head->value;
        }
        throw std::out_of_range("Trying to get from from empty list");
    }

    T& back() const {
        // assert(!this->empty())
        if (tail) {
            return tail->value;
        }
        throw std::out_of_range(
            "Trying to get last element from from empty list");
    }

    // void pop_back();      // usuwa koniec O(n)
    void clear();         // czyszczenie listy z elementow O(n)
    void display() const; // O(n)
    void reverse();       // O(n) NIEOBOWIAZKOWE

    T& operator[](std::size_t pos); // podstawienie L[pos]=item, odczyt L[pos]
    const T& operator[](std::size_t pos) const; // dostep do obiektu const

    int index(const T& item); // jaki index na liscie (-1 gdy nie ma) O(n)

    bool operator==(
        const OrderedList& rhs) const; // used for assertions if lists are equal

    void insert(const T& item); // add element to list
    void erase(const T& item);  // remove element from list
    bool contains(const T& item) const;
    OrderedNode<T>* get_head() const;
    void push_back(const T& item);
    void push_back(T&& item);

    // Inner class interface
    private:
    void erase_pos(std::size_t pos);             // Good
    void insert(std::size_t pos, const T& item); // inserts item before pos,
    void insert(std::size_t pos, T&& item);      // inserts item before pos,
    void pop_front();                            // usuwa poczatek O(1)
    size_t find_first_bigger(const T& item);     // returns pos element
    void push_front(const T& item);              // O(1)
    void push_front(T&& item);                   // O(1)
};

template <std::totally_ordered T>
OrderedList<T>::~OrderedList() {
    // I sposob.
    for (OrderedNode<T>* node; !empty();) {
        node = head->next; // zapamietujemy
        delete head;
        head = node; // kopiowanie wskaznika
    }
    // II sposob.
    // while (!empty()) { pop_front(); }
}

template <std::totally_ordered T>
void OrderedList<T>::push_front(const T& item) {
    this->length += 1;
    if (!empty()) {
        head = new OrderedNode<T>(item, head);
    } else {
        head = tail = new OrderedNode<T>(item);
    }
}

template <std::totally_ordered T>
void OrderedList<T>::push_back(const T& item) {
    this->length += 1;
    if (!empty()) {
        tail->next = new OrderedNode<T>(item);
        tail = tail->next;
    } else {
        head = tail = new OrderedNode<T>(item);
    }
}

template <std::totally_ordered T>
void OrderedList<T>::display() const {
    OrderedNode<T>* node = head;
    while (node != nullptr) {
        std::cout << node->value << " ";
        node = node->next;
    }
    std::cout << std::endl;
}

template <std::totally_ordered T>
void OrderedList<T>::pop_front() {
    assert(!empty());
    this->length -= 1;
    OrderedNode<T>* node = head;
    if (head == tail) {
        head = tail = nullptr;
    } else {
        head = head->next;
    }
    delete node;
}

// template <std::totally_ordered T>
// void OrderedList<T>::pop_back() {
//     assert(!empty());
//     this->length -= 1;
//     OrderedNode<T>* node = tail; // zapamietujemy
//     if (head == tail) {          // jeden wezel na liscie
//         head = tail = nullptr;
//     } else { // wiecej niz jeden wezel na liscie
//         // Szukamy poprzednika ogona.
//         OrderedNode<T>* before = head;
//         while (before->next != tail) {
//             before = before->next;
//         }
//         tail = before;
//         tail->next = nullptr;
//     }
//     delete node;
// }

template <std::totally_ordered T>
void OrderedList<T>::clear() {
    while (!this->empty()) {
        this->pop_front();
    }
}

template <std::totally_ordered T>
OrderedList<T>::OrderedList(const OrderedList& other)
    : head(nullptr), tail(nullptr), length(0) {
    OrderedNode<T>* node = other.head;
    while (node != nullptr) {
        this->push_back(node->value);
        node = node->next;
    }
}

template <std::totally_ordered T>
OrderedList<T>::OrderedList(OrderedList&& other)
    : head(nullptr), tail(nullptr), length(0) {
    this->head = other.head;
    this->tail = other.tail;
    this->length = other.length;
    other.head = nullptr;
    other.tail = nullptr;
    other.length = 0;
}

template <std::totally_ordered T>
OrderedList<T>& OrderedList<T>::operator=(const OrderedList& other) {
    if (this != &other) {
        // Added after 04-11-2025
        this->clear();

        OrderedNode<T>* copied_node = other.head;
        while (copied_node != nullptr) {
            this->push_back(copied_node->value);
            copied_node = copied_node->next;
        }
    }
    return *this;
}

template <std::totally_ordered T>
OrderedList<T>& OrderedList<T>::operator=(OrderedList<T>&& other) {
    if (this != &other) {
        this->head = other.head;
        this->tail = other.tail;
        this->length = other.length;
        other.head = nullptr;
        other.tail = nullptr;
        other.length = 0;
    }
    return *this;
}

template <std::totally_ordered T>
std::size_t OrderedList<T>::size() const {
    return this->length;
} // O(1) liczymy na bierzaco

template <std::totally_ordered T>
void OrderedList<T>::push_front(T&& item) {
    this->length += 1;
    if (!empty()) {
        head = new OrderedNode<T>(std::move(item), head);
    } else {
        head = tail = new OrderedNode<T>(std::move(item));
    }
}

template <std::totally_ordered T>
void OrderedList<T>::push_back(T&& item) {
    this->length += 1;
    if (!empty()) {
        tail->next = new OrderedNode<T>(std::move(item));
        tail = tail->next;
    } else {
        head = tail = new OrderedNode<T>(std::move(item));
    }
} // O(1), L.push_back(std::move(item)) NIEOBOWIAZKOWE

template <std::totally_ordered T>
void OrderedList<T>::reverse() {
    // No need for rotation;
    if (this->length < 2) {
        return;
    }

    OrderedNode<T>* cur = head;
    OrderedNode<T>* prev = nullptr;
    this->tail = head;
    while (cur != nullptr) {
        OrderedNode<T>* next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    this->head = prev;

} // O(n) NIEOBOWIAZKOWE

// Operacje z indeksami. NIEOBOWIAZKOWE
template <std::totally_ordered T>
T& OrderedList<T>::operator[](std::size_t pos) {
    if (this->length <= pos) {
        throw std::out_of_range("Trying to acces element out of range");
    }
    OrderedNode<T>* node = head;
    for (std::size_t node_count = 0; node_count < pos; node_count++) {
        node = node->next;
    }
    return node->value;
} // podstawienie L[pos]=item, odczyt L[pos]

template <std::totally_ordered T>
const T& OrderedList<T>::operator[](std::size_t pos) const {
    if (this->length <= pos) {
        throw std::out_of_range("Trying to acces element out of range");
    }
    OrderedNode<T>* node = head;
    for (std::size_t node_count = 0; node_count < pos; node_count++) {
        node = node->next;
    }
    return node->value;
} // dostep do obiektu const

template <std::totally_ordered T>
void OrderedList<T>::erase_pos(std::size_t pos) {
    if (this->length <= pos) {
        throw std::out_of_range("Trying to remove element out of range");
    }

    if (pos == 0) {
        this->pop_front();
        return;
    }

    this->length -= 1;
    OrderedNode<T>* node = head;
    // Go to pos-1
    for (std::size_t node_count = 0; node_count < pos - 1; node_count++) {
        node = node->next;
    }

    OrderedNode<T>* next_node = node->next;
    node->next = next_node->next;
    if (next_node == tail) {
        tail = node;
    }
    delete next_node;
}

template <std::totally_ordered T>
int OrderedList<T>::index(const T& item) {
    std::size_t node_index = 0;
    OrderedNode<T>* node = head;
    while (node != nullptr) {
        if (node->value == item) {
            return node_index;
        }
        node_index += 1;
        node = node->next;
    }
    return -1;
} // jaki index na liscie (-1 gdy nie ma) O(n)

template <std::totally_ordered T>
void OrderedList<T>::insert(std::size_t pos, const T& item) {
    if (this->length < pos) {
        throw std::out_of_range("Trying to remove element out of range");
    }
    if (pos == 0) {
        this->push_front(item);
        return;
    }
    if (pos == length) {
        this->push_back(item);
        return;
    }

    this->length += 1;
    OrderedNode<T>* node = head;
    // Go to pos-1
    for (std::size_t node_count = 0; node_count < pos - 1; node_count++) {
        node = node->next;
    }

    OrderedNode<T>* new_node = new OrderedNode<T>(item, node->next);
    node->next = new_node;
} // inserts item before pos,

template <std::totally_ordered T>
void OrderedList<T>::insert(std::size_t pos, T&& item) {
    if (this->length < pos) {
        throw std::out_of_range("Trying to insert element out of range");
    }
    if (pos == 0) {
        this->push_front(std::move(item));
        return;
    }
    if (pos == length) {
        this->push_back(std::move(item));
        return;
    }

    this->length += 1;
    OrderedNode<T>* node = head;
    // Go to pos-1
    for (std::size_t node_count = 0; node_count < pos - 1; node_count++) {
        node = node->next;
    }

    OrderedNode<T>* new_node = new OrderedNode<T>(std::move(item), node->next);
    node->next = new_node;
} // inserts item before pos,

template <std::totally_ordered T>
bool OrderedList<T>::operator==(const OrderedList<T>& rhs) const {
    // If lists dont have equal length we dont iterate over
    if (this->length != rhs.length) {
        return false;
    }
    OrderedNode<T>* cur_lhs = this->head;
    OrderedNode<T>* cur_rhs = rhs.head;

    // If only one of them is null ptr we have bug earlier in program
    while (cur_lhs != nullptr && cur_rhs != nullptr) {
        assert(cur_lhs != nullptr);
        assert(cur_rhs != nullptr);
        if (cur_lhs->value != cur_rhs->value) {
            return false;
        }
        cur_lhs = cur_lhs->next;
        cur_rhs = cur_rhs->next;
    }
    return true;
} // used for assertions if lists are equal

template <std::totally_ordered T>
size_t OrderedList<T>::find_first_bigger(const T& item) {
    if (this->size() == 0) {
        return 0;
    }
    size_t idx = 0;
    OrderedNode<T>* node = this->head;
    while (node != nullptr && node->value < item) {
        idx++;
        node = node->next;
    }
    return idx;
}

template <std::totally_ordered T>
void OrderedList<T>::insert(const T& item) {
    size_t idx = this->find_first_bigger(item);
    this->insert(idx, item);
}

template <std::totally_ordered T>
void OrderedList<T>::erase(const T& item) {
    auto node = this->head;
    size_t idx = 0;
    while (node != nullptr) {
        if (node->value == item) {
            erase_pos(idx);
            return;
        } else if (node->value > item) {
            return;
        }
        idx++;
        node = node->next;
    }
}

template <std::totally_ordered T>
bool OrderedList<T>::contains(const T& item) const {
    auto node = this->head;
    while (node != nullptr) {
        if (node->value == item) {
            return true;
        } else if (node->value > item) {
            return false;
        }
        node = node->next;
    }
    return false;
}
template <std::totally_ordered T>
OrderedNode<T>* OrderedList<T>::get_head() const {
    return this->head;
}

#endif