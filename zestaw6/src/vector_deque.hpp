#ifndef VECTOR_DEQUE_HPP
#define VECTOR_DEQUE_HPP

// Interfejs kolejki dwustronnej
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <vector>

template <typename T>
class MyVecDeque {
    private:
    std::vector<T> vecdeq;
    std::size_t head;
    std::size_t tail;

    public:
    MyVecDeque();
    MyVecDeque(std::size_t size);
    ~MyVecDeque();
    MyVecDeque(const MyVecDeque& other);
    MyVecDeque(MyVecDeque&& other);
    MyVecDeque& operator=(const MyVecDeque& other);
    MyVecDeque& operator=(MyVecDeque&& other);
    bool operator==(const MyVecDeque<T>& rhs) const;
    bool operator!=(const MyVecDeque<T>& rhs) const { return !(*this == rhs); }
    bool empty() const;
    std::size_t size() const;
    void push_front(const T& item);
    void push_front(T&& item);
    void push_back(const T& item);
    void push_back(T&& item);
    T& front();
    T& back();
    void pop_front();
    void pop_back();
    void clear();
    void display();
    void display_reversed();
    T& operator[](std::size_t pos);
    const T& operator[](std::size_t pos) const;
    void erase(std::size_t pos);
    int index(const T& item);
    void insert(std::size_t pos, const T& item);
    void insert(std::size_t pos, T&& item);

    void debug_print() const; // prints whole underlying vector
    private:
    bool full();
    bool inbouds_check(
        std::size_t i) const; // checks if passed index is inside queue
    void resize(); // resize vector to allow insertion of new elements
    // we have to move [0, queue_end] elements after old end.
    T& index_at(std::size_t pos);
    const T& index_at(std::size_t pos) const;
};

template <typename T>
MyVecDeque<T>::MyVecDeque() : MyVecDeque(10) {}

template <typename T>
MyVecDeque<T>::MyVecDeque(std::size_t size)
    : head(0), tail(0), vecdeq(size + 1) {
    this->vecdeq.resize(size + 1);
}

template <typename T>
MyVecDeque<T>::~MyVecDeque() {
    // nothing to do std::vector destructor frees memory
}

template <typename T>
MyVecDeque<T>::MyVecDeque(const MyVecDeque& other)
    : head(other.head), tail(other.tail), vecdeq(other.vecdeq) {}

template <typename T>
MyVecDeque<T>::MyVecDeque(MyVecDeque&& other)
    : head(other.head), tail(other.tail), vecdeq(std::move(other.vecdeq)) {
    other.head = 0;
    other.tail = 0;
    other.vecdeq.resize(1);
}

template <typename T>
MyVecDeque<T>& MyVecDeque<T>::operator=(const MyVecDeque& other) {
    if (this != &other) {
        this->vecdeq = other.vecdeq;
        this->head = other.head;
        this->tail = other.tail;
    }
    return *this;
}

template <typename T>
MyVecDeque<T>& MyVecDeque<T>::operator=(MyVecDeque&& other) {
    if (this != &other) {
        this->vecdeq = std::move(other.vecdeq);
        this->head = other.head;
        this->tail = other.tail;
        other.head = 0;
        other.tail = 0;
        other.vecdeq.resize(1);
    }
    return *this;
}

template <typename T>
bool MyVecDeque<T>::operator==(const MyVecDeque<T>& rhs) const {
    if (this->size() != rhs.size()) {
        return false;
    }
    // [] needed
    for (std::size_t i = 0; i < this->size(); ++i) {
        if (this->index_at(0) != rhs.index_at(0)) {
            std::cout << "Failed " << (this->index_at(i))
                      << "==" << (rhs.index_at(0)) << " at i =" << i
                      << std::endl;
            return false;
        }
    }
    return true;
}

template <typename T>
bool MyVecDeque<T>::empty() const {
    return head == tail;
}

template <typename T>
std ::size_t MyVecDeque<T>::size() const {
    return (tail - head + this->vecdeq.size()) % this->vecdeq.size();
}

template <typename T>
void MyVecDeque<T>::push_front(const T& item) {
    if (this->full()) {
        this->resize();
    }
    this->head = (this->head + this->vecdeq.size() - 1) % this->vecdeq.size();
    this->vecdeq[head] = item;
}

template <typename T>
void MyVecDeque<T>::push_front(T&& item) {
    if (this->full()) {
        this->resize();
    }
    this->head = (this->head + this->vecdeq.size() - 1) % this->vecdeq.size();
    this->vecdeq[head] = std::move(item);
}

template <typename T>
void MyVecDeque<T>::push_back(const T& item) {
    if (this->full()) {
        this->resize();
    }
    this->vecdeq[tail] = item;
    this->tail = (this->tail + this->vecdeq.size() + 1) % this->vecdeq.size();
}

template <typename T>
void MyVecDeque<T>::push_back(T&& item) {
    if (this->full()) {
        this->resize();
    }
    this->vecdeq[tail] = std::move(item);
    this->tail = (this->tail + this->vecdeq.size() + 1) % this->vecdeq.size();
}

template <typename T>
T& MyVecDeque<T>::front() {
    return this->vecdeq[this->head];
}

template <typename T>
T& MyVecDeque<T>::back() {
    return this
        ->vecdeq[(this->tail + this->vecdeq.size() - 1) % this->vecdeq.size()];
}

template <typename T>
void MyVecDeque<T>::pop_front() {
    assert(this->size() > 0);
    this->head = (this->head + 1) % this->vecdeq.size();
}

template <typename T>
void MyVecDeque<T>::pop_back() {
    assert(this->size() > 0);
    this->tail = (this->tail + this->vecdeq.size() - 1) % this->vecdeq.size();
}

template <typename T>
void MyVecDeque<T>::clear() {
    this->head = 0;
    this->tail = 0;
}

template <typename T>
void MyVecDeque<T>::display() {
    // TODO
}

template <typename T>
void MyVecDeque<T>::display_reversed() {
    // TODO
}

template <typename T>
T& MyVecDeque<T>::index_at(std::size_t pos) {
    assert(pos < this->size());
    std::size_t internal_pos = (this->head + pos) % this->vecdeq.size();
    return this->vecdeq[internal_pos];
}

template <typename T>
T& MyVecDeque<T>::operator[](std::size_t pos) {
    return this->index_at(pos);
}

template <typename T>
const T& MyVecDeque<T>::index_at(std::size_t pos) const {
    assert(pos < this->size());
    std::size_t internal_pos = (this->head + pos) % this->vecdeq.size();
    return this->vecdeq[internal_pos];
}

template <typename T>
const T& MyVecDeque<T>::operator[](std::size_t pos) const {
    return this->index_at(pos);
}

template <typename T>
void MyVecDeque<T>::erase(std::size_t pos) {
    // if pos < tail we copy elements from tail to pos
    std::size_t internal_pos = (this->head + pos) % this->vecdeq.size();
    if (internal_pos < tail) {
        std::copy(this->vecdeq.begin() + internal_pos + 1,
                  this->vecdeq.begin() + this->tail,
                  this->vecdeq.begin() + internal_pos);
        this->tail =
            (this->tail + this->vecdeq.size() - 1) % this->vecdeq.size();
    } else {
        // if pos > head we copy head to internal pos
        std::copy_backward(this->vecdeq.begin() + this->head,
                           this->vecdeq.begin() + internal_pos,
                           this->vecdeq.begin() + internal_pos + 1);

        this->head = (this->head + 1) % this->vecdeq.size();
    }
}

template <typename T>
int MyVecDeque<T>::index(const T& item) {
    for (std::size_t i = 0; i < this->size(); i++) {
        if (item == this->index_at(i)) {
            return i;
        }
    }
    return -1;
}

template <typename T>
void MyVecDeque<T>::insert(std::size_t pos, const T& item) {
    if (this->full()) {
        this->resize();
    }
    // TODO work out edge cases and moving
    std::size_t internal_pos = (this->head + pos) % this->vecdeq.size();
    if (internal_pos < tail && tail + 1 != this->vecdeq.size()) {
        std::copy_backward(this->vecdeq.begin() + internal_pos,
                           this->vecdeq.begin() + this->tail,
                           this->vecdeq.begin() + this->tail + 1);
        this->tail =
            (this->tail + this->vecdeq.size() + 1) % this->vecdeq.size();
    } else {
        // if pos > head we copy head to internal pos
        std::copy(this->vecdeq.begin() + this->head,
                  this->vecdeq.begin() + internal_pos,
                  this->vecdeq.begin() - 1);

        this->head =
            (this->head + this->vecdeq.size() - 1) % this->vecdeq.size();
    }
}

template <typename T>
void MyVecDeque<T>::insert(std::size_t pos, T&& item) {}

template <typename T>
void MyVecDeque<T>::resize() {
    std::size_t old_size = this->vecdeq.size();
    if (old_size != 0) {
        this->vecdeq.resize(old_size * 2); // resize vector
        // Move elements 0..tail if tail < head
        if (this->tail < this->head) {
            std::copy(this->vecdeq.begin(), vecdeq.begin() + this->tail,
                      this->vecdeq.begin() + old_size);
            this->tail += old_size;
        }
    } else {
        this->vecdeq.resize(1);
    }
}

template <typename T>
bool MyVecDeque<T>::full() {
    return (tail + 1) % this->vecdeq.size() == head;
}

template <typename T>
void MyVecDeque<T>::debug_print() const {
    // Gray dummy elemenents
    // Green head
    // Red tail+1
    // yellow queelements
    for (std::size_t i = 0; i < vecdeq.size(); i++) {
        if (i == this->tail)
            std::cout << "\033[1;31m" << this->vecdeq[i] << "\033[0m, ";
        else if (i == this->head)
            std::cout << "\033[1;32m" << this->vecdeq[i] << "\033[0m, ";
        else if (this->inbouds_check(i))
            std::cout << "\033[1;33m" << this->vecdeq[i] << "\033[0m, ";
        else
            std::cout << this->vecdeq[i] << ", ";
    }
    std::cout << std::endl;
}

template <typename T>
bool MyVecDeque<T>::inbouds_check(std::size_t i) const {
    return (this->head > this->tail && (i >= this->head || i < this->tail)) ||
           (this->head < this->tail && i >= this->head && i < this->tail);
}

#endif
