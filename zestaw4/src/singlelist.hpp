// singlelist.h

#ifndef SINGLELIST_H
#define SINGLELIST_H

#include <cassert> // assert()
#include <cstddef>
#include <iostream> // deklaracje strumieni cout, cin, cerr
#include <stdexcept>

template <typename T> struct SingleNode {
    // the default access mode and default inheritance mode are public
    T value;
    SingleNode* next;
    SingleNode() : value(T()), next(nullptr) {} // konstruktor domyslny
    SingleNode(const T& item, SingleNode* ptr = nullptr)
        : value(item), next(ptr) {}
    SingleNode(T&& item, SingleNode* ptr = nullptr)
        : value(std::move(item)), next(ptr) {}
    ~SingleNode() {} // destruktor
};

template <typename T> class SingleList {
    SingleNode<T>*head, *tail;
    std::size_t length;

    public:
    SingleList() : head(nullptr), tail(nullptr), length(0) {}
    ~SingleList(); // tu trzeba wyczyscic wezly

    SingleList(const SingleList& other); // copy constructor
    // usage:   SingleList<int> list2(list1);

    SingleList(SingleList&& other); // move constructor NIEOBOWIAZKOWE
    // usage:   SingleList<int> list2(std::move(list1));

    SingleList& operator=(
        const SingleList& other); // copy assignment operator, return *this
    // usage:   list2 = list1;

    SingleList&
    operator=(SingleList&& other); // move assignment operator, return *this
    // usage:   list2 = std::move(list1); NIEOBOWIAZKOWE

    bool empty() const { return head == nullptr; }
    std::size_t size() const;       // O(n) bo trzeba policzyc
    void push_front(const T& item); // O(1), L.push_front(item)
    void
    push_front(T&& item); // O(1), L.push_front(std::move(item)) NIEOBOWIAZKOWE
    void push_back(const T& item); // O(1), L.push_back(item)
    void
    push_back(T&& item); // O(1), L.push_back(std::move(item)) NIEOBOWIAZKOWE

    // Nullptr deref for empty list!
    // T& front() const { return head->value; } // zwraca poczatek, nie usuwa

    /// Fixed version
    T& front() const {
        // ALTERNATIVE:
        // assert(!this->empty())
        if (head) {
            return head->value;
        }
        throw std::out_of_range("Trying to get from from empty list");
    } // zwraca poczatek, nie usuwa

    // Nullptr deref for empty list!
    // T& back() const { return tail->value; } // zwraca koniec, nie usuwa
    T& back() const {
        // ALTERNATIVE:
        // assert(!this->empty())
        if (tail) {
            return tail->value;
        }
        throw std::out_of_range(
            "Trying to get last element from from empty list");
    } // zwraca poczatek, nie usuwa

    void pop_front();     // usuwa poczatek O(1)
    void pop_back();      // usuwa koniec O(n)
    void clear();         // czyszczenie listy z elementow O(n)
    void display() const; // O(n)
    void reverse();       // O(n) NIEOBOWIAZKOWE

    // Operacje z indeksami. NIEOBOWIAZKOWE
    T& operator[](std::size_t pos); // podstawienie L[pos]=item, odczyt L[pos]
    const T& operator[](std::size_t pos) const; // dostep do obiektu const
    void erase(std::size_t pos);
    int index(const T& item); // jaki index na liscie (-1 gdy nie ma) O(n)
    void insert(std::size_t pos, const T& item); // inserts item before pos,
    void insert(std::size_t pos, T&& item);      // inserts item before pos,
    // Jezeli pos=0, to wstawiamy na poczatek.
    // Jezeli pos=size(), to wstawiamy na koniec.

    bool operator==(
        const SingleList& rhs) const; // used for assertions if lists are equal
};

template <typename T> SingleList<T>::~SingleList() {
    // I sposob.
    for (SingleNode<T>* node; !empty();) {
        node = head->next; // zapamietujemy
        delete head;
        head = node; // kopiowanie wskaznika
    }
    // II sposob.
    // while (!empty()) { pop_front(); }
}

template <typename T> void SingleList<T>::push_front(const T& item) {
    this->length += 1;
    if (!empty()) {
        head = new SingleNode<T>(item, head);
    } else {
        head = tail = new SingleNode<T>(item);
    }
}

template <typename T> void SingleList<T>::push_back(const T& item) {
    this->length += 1;
    if (!empty()) {
        tail->next = new SingleNode<T>(item);
        tail = tail->next;
    } else {
        head = tail = new SingleNode<T>(item);
    }
}

template <typename T> void SingleList<T>::display() const {
    SingleNode<T>* node = head;
    while (node != nullptr) {
        std::cout << node->value << " ";
        node = node->next;
    }
    std::cout << std::endl;
}

template <typename T> void SingleList<T>::pop_front() {
    assert(!empty());
    this->length -= 1;
    SingleNode<T>* node = head; // zapamietujemy
    if (head == tail) {         // jeden wezel na liscie
        head = tail = nullptr;
    } else { // wiecej niz jeden wezel na liscie
        head = head->next;
    }
    delete node;
}

template <typename T> void SingleList<T>::pop_back() {
    assert(!empty());
    this->length -= 1;
    SingleNode<T>* node = tail; // zapamietujemy
    if (head == tail) {         // jeden wezel na liscie
        head = tail = nullptr;
    } else { // wiecej niz jeden wezel na liscie
        // Szukamy poprzednika ogona.
        SingleNode<T>* before = head;
        while (before->next != tail) {
            before = before->next;
        }
        tail = before;
        tail->next = nullptr;
    }
    delete node;
}

template <typename T> void SingleList<T>::clear() {
    while (!this->empty()) {
        this->pop_front();
    }
} // czyszczenie listy z elementow O(n)

template <typename T>
SingleList<T>::SingleList(const SingleList& other)
    : head(nullptr), tail(nullptr), length(0) {
    SingleNode<T>* node = other.head;
    while (node != nullptr) {
        this->push_back(node->value);
        node = node->next;
    }
} // copy constructor
// usage:   SingleList<int> list2(list1);

template <typename T>
SingleList<T>::SingleList(SingleList&& other)
    : head(nullptr), tail(nullptr), length(0) {
    this->head = other.head;
    this->tail = other.tail;
    this->length = other.length;
    other.head = nullptr;
    other.tail = nullptr;
    other.length = 0;
} // move constructor NIEOBOWIAZKOWE
// usage:   SingleList<int> list2(std::move(list1));

template <typename T>
SingleList<T>& SingleList<T>::operator=(const SingleList& other) {
    if (this != &other) {
        // Added after 04-11-2025
        this->clear(); // We have to free our memory

        SingleNode<T>* copied_node = other.head;
        while (copied_node != nullptr) {
            this->push_back(copied_node->value);
            copied_node = copied_node->next;
        }
    }
    return *this;
} // copy assignment operator, return *this
// usage:   list2 = list1;

template <typename T>
SingleList<T>& SingleList<T>::operator=(SingleList<T>&& other) {
    if (this != &other) {
        this->head = other.head;
        this->tail = other.tail;
        this->length = other.length;
        other.head = nullptr;
        other.tail = nullptr;
        other.length = 0;
    }
    return *this;
} // move assignment operator, return *this
// usage:   list2 = std::move(list1); NIEOBOWIAZKOWE

template <typename T> std::size_t SingleList<T>::size() const {
    return this->length;
} // O(1) liczymy na bierzaco

template <typename T> void SingleList<T>::push_front(T&& item) {
    this->length += 1;
    if (!empty()) {
        head = new SingleNode<T>(std::move(item), head);
    } else {
        head = tail = new SingleNode<T>(std::move(item));
    }
} // O(1), L.push_front(std::move(item)) NIEOBOWIAZKOWE

template <typename T> void SingleList<T>::push_back(T&& item) {
    this->length += 1;
    if (!empty()) {
        tail->next = new SingleNode<T>(std::move(item));
        tail = tail->next;
    } else {
        head = tail = new SingleNode<T>(std::move(item));
    }
} // O(1), L.push_back(std::move(item)) NIEOBOWIAZKOWE

template <typename T> void SingleList<T>::reverse() {
    // No need for rotation;
    if (this->length < 2) {
        return;
    }

    SingleNode<T>* cur = head;
    SingleNode<T>* prev = nullptr;
    this->tail = head;
    while (cur != nullptr) {
        SingleNode<T>* next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    this->head = prev;

} // O(n) NIEOBOWIAZKOWE

// Operacje z indeksami. NIEOBOWIAZKOWE
template <typename T> T& SingleList<T>::operator[](std::size_t pos) {
    if (this->length <= pos) {
        throw std::out_of_range("Trying to acces element out of range");
    }
    SingleNode<T>* node = head;
    for (std::size_t node_count = 0; node_count < pos; node_count++) {
        node = node->next;
    }
    return node->value;
} // podstawienie L[pos]=item, odczyt L[pos]

template <typename T>
const T& SingleList<T>::operator[](std::size_t pos) const {
    if (this->length <= pos) {
        throw std::out_of_range("Trying to acces element out of range");
    }
    SingleNode<T>* node = head;
    for (std::size_t node_count = 0; node_count < pos; node_count++) {
        node = node->next;
    }
    return node->value;
} // dostep do obiektu const

template <typename T> void SingleList<T>::erase(std::size_t pos) {
    if (this->length <= pos) {
        throw std::out_of_range("Trying to remove element out of range");
    }

    if (pos == 0) {
        this->pop_front();
        return;
    }

    this->length -= 1;
    SingleNode<T>* node = head;
    // Go to pos-1
    for (std::size_t node_count = 0; node_count < pos - 1; node_count++) {
        node = node->next;
    }

    SingleNode<T>* next_node = node->next;
    node->next = next_node->next;
    if (next_node == tail) {
        tail = node;
    }
    delete next_node;
}

template <typename T> int SingleList<T>::index(const T& item) {
    std::size_t node_index = 0;
    SingleNode<T>* node = head;
    while (node != nullptr) {
        if (node->value == item) {
            return node_index;
        }
        node_index += 1;
        node = node->next;
    }
    return -1;
} // jaki index na liscie (-1 gdy nie ma) O(n)

template <typename T>
void SingleList<T>::insert(std::size_t pos, const T& item) {
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
    SingleNode<T>* node = head;
    // Go to pos-1
    for (std::size_t node_count = 0; node_count < pos - 1; node_count++) {
        node = node->next;
    }

    SingleNode<T>* new_node = new SingleNode<T>(item, node->next);
    node->next = new_node;
} // inserts item before pos,

template <typename T> void SingleList<T>::insert(std::size_t pos, T&& item) {
    if (this->length < pos) {
        throw std::out_of_range("Trying to remove element out of range");
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
    SingleNode<T>* node = head;
    // Go to pos-1
    for (std::size_t node_count = 0; node_count < pos - 1; node_count++) {
        node = node->next;
    }

    SingleNode<T>* new_node = new SingleNode<T>(std::move(item), node->next);
    node->next = new_node;
} // inserts item before pos,

template <typename T>
bool SingleList<T>::operator==(const SingleList<T>& rhs) const {
    // If lists dont have equal length we dont iterate over
    if (this->length != rhs.length) {
        return false;
    }
    SingleNode<T>* cur_lhs = this->head;
    SingleNode<T>* cur_rhs = rhs.head;

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

#endif