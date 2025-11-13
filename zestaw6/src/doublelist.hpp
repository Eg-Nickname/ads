// doublelist.h

#ifndef DOUBLELIST_H
#define DOUBLELIST_H

#include <cassert>  // assert()
#include <iostream> // deklaracje strumieni cout, cin, cerr

template <typename T>
struct DoubleNode {
    // the default access mode and default inheritance mode are public
    T value;
    DoubleNode *next, *prev;
    // konstruktor domyslny (niepotrzebny)
    DoubleNode() : value(T()), next(nullptr), prev(nullptr) {}
    DoubleNode(const T& item, DoubleNode* nptr = nullptr,
               DoubleNode* pptr = nullptr)
        : value(item), next(nptr), prev(pptr) {} // konstruktor
    DoubleNode(T&& item, DoubleNode* nptr = nullptr, DoubleNode* pptr = nullptr)
        : value(std::move(item)), next(nptr), prev(pptr) {} // move constructor
    ~DoubleNode() {}                                        // destruktor
};

template <typename T>
class DoubleList {
    DoubleNode<T>* nil;
    std::size_t len;

    public:
    DoubleList();
    ~DoubleList(); // tu trzeba wyczyscic wezly

    DoubleList(const DoubleList& other); // copy constructor
    // usage:   DoubleList<int> list2(list1);

    DoubleList(DoubleList&& other); // move constructor NIEOBOWIAZKOWE
    // usage:   DoubleList<int> list2(std::move(list1));

    DoubleList& operator=(
        const DoubleList& other); // copy assignment operator, return *this
    // usage:   list2 = list1;

    DoubleList&
    operator=(DoubleList&& other); // move assignment operator, return *this
    // usage:   list2 = std::move(list1); NIEOBOWIAZKOWE

    bool operator==(const DoubleList<T>& rhs) const;
    bool operator!=(const DoubleList<T>& rhs) const { return !(*this == rhs); }

    bool empty() const { return nil->next == nil; }

    T& front() const {
        assert(!empty());
        return nil->next->value;
    } // zwraca początek, nie usuwa
    T& back() const {
        assert(!empty());
        return nil->prev->value;
    } // zwraca koniec, nie usuwa

    std::size_t size() const;       // O(n) bo trzeba policzyc
    void push_front(const T& item); // O(1)
    void push_front(T&& item);      // O(1) NIEOBOWIAZKOWE
    void push_back(const T& item);  // O(1)
    void push_back(T&& item);       // O(1) NIEOBOWIAZKOWE
    void pop_front();               // usuwa poczatek O(1)
    void pop_back();                // usuwa koniec O(1)
    void clear();                   // czyszczenie listy z elementow O(n)
    void display();                 // O(n)
    void display_reversed();        // O(n)

    // Operacje z indeksami. NIEOBOWIAZKOWE
    T& operator[](std::size_t pos); // podstawienie L[pos]=item, odczyt L[pos]
    const T& operator[](std::size_t pos) const; // dostep do obiektu const
    void erase(std::size_t pos);
    int index(const T& item); // jaki index na liscie (-1 gdy nie ma) O(n)
    void insert(std::size_t pos, const T& item); // inserts item before pos,
    void insert(std::size_t pos, T&& item);      // inserts item before pos,
    // Jezeli pos=0, to wstawiamy na poczatek.
    // Jezeli pos=size(), to wstawiamy na koniec.
};

template <typename T>
void DoubleList<T>::push_front(const T& item) {
    DoubleNode<T>* node = new DoubleNode<T>(item, nil->next, nil);
    this->len += 1;
    nil->next->prev = node;
    nil->next = node;
}

template <typename T>
void DoubleList<T>::pop_front() {
    assert(!empty());
    this->len -= 1;
    DoubleNode<T>* node = nil->next; // zapamiętujemy
    node->next->prev = node->prev;   // ogólny schemat usuwania
    node->prev->next = node->next;
    delete node;
}

// ========================================================
template <typename T>
DoubleList<T>::DoubleList() : len(0) {
    this->nil = new DoubleNode<T>();
    this->nil->next = this->nil;
    this->nil->prev = this->nil;
}

template <typename T>
DoubleList<T>::~DoubleList() {
    while (!empty()) {
        this->pop_front();
    }
    // Delete guard node at the end
    delete nil;
} // tu trzeba wyczyscic wezly

template <typename T>
DoubleList<T>::DoubleList(const DoubleList<T>& other) : DoubleList() {
    DoubleNode<T>* copy_node = other.nil->prev;
    // Copy all nodes from other list
    while (copy_node != other.nil) {
        this->push_front(copy_node->value);
        copy_node = copy_node->prev;
    }
} // copy constructor
// usage:   DoubleList<int> list2(list1);

template <typename T>
DoubleList<T>::DoubleList(DoubleList<T>&& other) {
    this->nil = other.nil;
    other.nil = new DoubleNode<T>();
    other.nil->next = other.nil;
    other.nil->prev = other.nil;
    other.len = 0;
} // move constructor NIEOBOWIAZKOWE
// usage:   DoubleList<int> list2(std::move(list1));

template <typename T>
DoubleList<T>& DoubleList<T>::operator=(const DoubleList<T>& other) {
    if (this != &other) {
        // Remove old elements
        this->clear();

        // Copy all elements from other
        DoubleNode<T>* copy_node = other.nil->prev;
        // Copy all nodes from other list
        while (copy_node != other.nil) {
            this->push_front(copy_node->value);
            copy_node = copy_node->prev;
        }
    }
    return *this;
} // copy assignment operator, return *this
// usage:   list2 = list1;

template <typename T>
DoubleList<T>& DoubleList<T>::operator=(DoubleList<T>&& other) {
    if (this != &other) {
        // Remove old elements
        this->clear();
        this->nil = other.nil;
        this->len = other.len;
        other.nil = new DoubleNode<T>();
        other.nil->next = other.nil;
        other.nil->prev = other.nil;
        other.len = 0;
    }
    return *this;
} // move assignment operator, return *this
// usage:   list2 = std::move(list1); NIEOBOWIAZKOWE

template <typename T>
bool DoubleList<T>::operator==(const DoubleList<T>& rhs) const {
    if (this->len != rhs.len) {
        return false;
    }
    DoubleNode<T>* lhs_node = this->nil->next;
    DoubleNode<T>* rhs_node = rhs.nil->next;
    // rhs_node is nil at the same time as lhs_node
    while (lhs_node != this->nil) {
        if (lhs_node->value != rhs_node->value) {
            return false;
        }
        lhs_node = lhs_node->next;
        rhs_node = rhs_node->next;
    }
    return true;
}

template <typename T>
std::size_t DoubleList<T>::size() const {
    return this->len;
} // O(1) bo nie trzeba policzyc

template <typename T>
void DoubleList<T>::push_front(T&& item) {
    DoubleNode<T>* node = new DoubleNode<T>(std::move(item), nil->next, nil);
    this->len += 1;
    nil->next->prev = node;
    nil->next = node;
} // O(1) NIEOBOWIAZKOWE

template <typename T>
void DoubleList<T>::push_back(const T& item) {
    DoubleNode<T>* node = new DoubleNode<T>(item, nil, nil->prev);
    this->len += 1;
    nil->prev->next = node;
    nil->prev = node;
} // O(1)

template <typename T>
void DoubleList<T>::push_back(T&& item) {
    DoubleNode<T>* node = new DoubleNode<T>(std::move(item), nil, nil->prev);
    this->len += 1;
    nil->prev->next = node;
    nil->prev = node;
} // O(1) NIEOBOWIAZKOWE

template <typename T>
void DoubleList<T>::pop_back() {
    assert(!empty());
    this->len -= 1;
    DoubleNode<T>* node = nil->prev; // zapamiętujemy
    node->next->prev = node->prev;   // ogólny schemat usuwania
    node->prev->next = node->next;
    delete node;
} // usuwa koniec O(1)

template <typename T>
void DoubleList<T>::clear() {
    while (!empty()) {
        this->pop_front();
    }
} // czyszczenie listy z elementow O(n)

template <typename T>
void DoubleList<T>::display() {
    auto print_node = this->nil->next;
    while (print_node != this->nil) {
        std::cout << print_node->value;
        print_node = print_node->next;
        if (print_node != this->nil) {
            std::cout << " - ";
        }
    }
    std::cout << std::endl;
} // O(n)

template <typename T>
void DoubleList<T>::display_reversed() {
    auto print_node = this->nil->prev;
    while (print_node != this->nil) {
        std::cout << print_node->value;
        print_node = print_node->prev;
        if (print_node != this->nil) {
            std::cout << " - ";
        }
    }
    std::cout << std::endl;
} // O(n)

// Operacje z indeksami. NIEOBOWIAZKOWE
template <typename T>
T& DoubleList<T>::operator[](std::size_t pos) {
    // Check if we are not indexing out of bounds
    assert(this->len > pos);
    // as we have cyclic implementation we can do pos(mod)len

    auto node = this->nil->next;
    for (std::size_t node_count = 0; node_count < pos; node_count++) {
        node = node->next;
    }
    return node->value;
} // podstawienie L[pos]=item, odczyt L[pos]

template <typename T>
const T& DoubleList<T>::operator[](std::size_t pos) const {
    // Check if we are not indexing out of bounds
    assert(this->len > pos);
    // as we have cyclic implementation we can do pos(mod)len

    auto node = this->nil->next;
    for (std::size_t node_count = 0; node_count < pos; node_count++) {
        node = node->next;
    }
    return node->value;
} // dostep do obiektu const

template <typename T>
void DoubleList<T>::erase(std::size_t pos) {
    // Check if we are not indexing out of bounds
    assert(this->len > pos);
    // as we have cyclic implementation we can do pos(mod)len
    auto node = this->nil->next;
    for (std::size_t node_count = 0; node_count < pos; node_count++) {
        node = node->next;
    }

    this->len -= 1;
    node->next->prev = node->prev;
    node->prev->next = node->next;
    delete node;
}

template <typename T>
int DoubleList<T>::index(const T& item) {
    auto node = this->nil->next;
    for (std::size_t idx = 0; node != this->nil; idx += 1) {
        if (node->value == item) {
            return idx;
        }
        node = node->next;
    }
    return -1;
} // jaki index na liscie (-1 gdy nie ma) O(n)

template <typename T>
void DoubleList<T>::insert(std::size_t pos, const T& item) {
    // Check if we are not indexing out of bounds
    assert(this->len >= pos);
    // as we have cyclic implementation we can do pos(mod)len

    auto node = this->nil->next;
    for (std::size_t node_count = 0; node_count < pos; node_count++) {
        node = node->next;
    }
    // we are at node indexted pos and we have to insert element before it
    // we cant go to pos -1 before pos 0 is edge case
    DoubleNode<T>* new_node = new DoubleNode<T>(item, node, node->prev);
    this->len += 1;
    node->prev->next = new_node;
    node->prev = new_node;
} // inserts item before pos,

template <typename T>
void DoubleList<T>::insert(std::size_t pos, T&& item) {
    // Check if we are not indexing out of bounds
    assert(this->len >= pos);
    // as we have cyclic implementation we can do pos(mod)len

    DoubleNode<T>* node = this->nil->next;
    for (std::size_t node_count = 0; node_count < pos; node_count++) {
        node = node->next;
    }
    // we are at node indexted pos and we have to insert element before it
    // we cant go to pos -1 before pos 0 is edge case
    DoubleNode<T>* new_node =
        new DoubleNode<T>(std::move(item), node, node->prev);
    this->len += 1;
    node->prev->next = new_node;
    node->prev = new_node;
} // inserts item before pos,
// Jezeli pos=0, to wstawiamy na poczatek.
// Jezeli pos=size(), to wstawiamy na koniec.

#endif

// EOF
