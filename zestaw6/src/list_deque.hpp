#ifndef LIST_DEQUE_HPP
#define LIST_DEQUE_HPP

// Interfejs kolejki dwustronnej
#include "doublelist.hpp"
#include <cstddef>

template <typename T>
class MyListDeque {
    DoubleList<T> queue;

    public:
    MyListDeque();
    ~MyListDeque();
    MyListDeque(const MyListDeque& other);
    MyListDeque(MyListDeque&& other);
    MyListDeque& operator=(const MyListDeque& other);
    MyListDeque& operator=(MyListDeque&& other);
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
};

template <typename T>
MyListDeque<T>::MyListDeque() {
    this->queue = DoubleList<T>();
}

template <typename T>
MyListDeque<T>::~MyListDeque() {}

template <typename T>
MyListDeque<T>::MyListDeque(const MyListDeque& other) {
    this->queue = DoubleList<T>(other.queue);
}

template <typename T>
MyListDeque<T>::MyListDeque(MyListDeque&& other) {
    this->queue = DoubleList<T>(std::move(other.queue));
}

template <typename T>
MyListDeque<T>& MyListDeque<T>::operator=(const MyListDeque& other) {
    this->queue = other.queue;
}

template <typename T>
MyListDeque<T>& MyListDeque<T>::operator=(MyListDeque&& other) {
    this->queue = std::move(other.queue);
}

template <typename T>
bool MyListDeque<T>::empty() const {
    this->queue.empty();
}

template <typename T>
std ::size_t MyListDeque<T>::size() const {
    this->queue.size();
}

template <typename T>
void MyListDeque<T>::push_front(const T& item) {
    this->queue.push_front(item);
}

template <typename T>
void MyListDeque<T>::push_front(T&& item) {
    this->queue.push_front(std::move(item));
}

template <typename T>
void MyListDeque<T>::push_back(const T& item) {
    this->queue.push_back(item);
}

template <typename T>
void MyListDeque<T>::push_back(T&& item) {
    this->queue.push_back(std::move(item));
}

template <typename T>
T& MyListDeque<T>::front() {
    this->queue.front();
}

template <typename T>
T& MyListDeque<T>::back() {
    this->queue.back();
}

template <typename T>
void MyListDeque<T>::pop_front() {
    this->queue.pop_front();
}

template <typename T>
void MyListDeque<T>::pop_back() {
    this->queue.pop_back();
}

template <typename T>
void MyListDeque<T>::clear() {
    this->queue.clear();
}

template <typename T>
void MyListDeque<T>::display() {
    this->queue.display();
}

template <typename T>
void MyListDeque<T>::display_reversed() {
    this->queue.display_reversed();
}

template <typename T>
T& MyListDeque<T>::operator[](std::size_t pos) {
    return this->queue[pos];
}

template <typename T>
const T& MyListDeque<T>::operator[](std::size_t pos) const {
    return this->queue[pos];
}

template <typename T>
void MyListDeque<T>::erase(std::size_t pos) {
    this->queue.erase();
}

template <typename T>
int MyListDeque<T>::index(const T& item) {
    this->queue.index(item);
}

template <typename T>
void MyListDeque<T>::insert(std::size_t pos, const T& item) {
    this->queue.insert(pos, item);
}

template <typename T>
void MyListDeque<T>::insert(std::size_t pos, T&& item) {
    this->queue.insert(pos, std::move(item));
}

#endif
