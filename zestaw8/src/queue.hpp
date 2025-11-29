#ifndef MYQUEUE_HPP
#define MYQUEUE_HPP

#include <cassert>
#include <cstddef>
#include <iostream>
#include <stack>

// Interfejs kolejki.
template <typename T>
class MyQueue {
    // zależne od implementacji
    std::stack<T> input;
    std::stack<T> output;

    private:
    void stack_pour();

    public:
    MyQueue(); // default constructor
    ~MyQueue();
    MyQueue(const MyQueue& other); // copy constructor
    MyQueue(MyQueue&& other);      // move constructor
    MyQueue&
    operator=(const MyQueue& other); // copy assignment operator, return *this
    MyQueue&
    operator=(MyQueue&& other); // move assignment operator, return *this
    bool empty() const;         // checks if the container has no elements
    std::size_t size() const;   // liczba elementów w kolejce
    void push(const T& item);   // dodanie na koniec, push_back(item)
    void push(T&& item);        // dodanie na koniec, push_back(std::move(item))
    T& front();                 // zwraca koniec, nie usuwa
    T& back();                  // zwraca koniec, nie usuwa
    void pop();                 // usuwa początek kolejki, pop_front()
    void clear();               // czyszczenie listy z elementów

    // Cant do in stack implementation without additional stack
    void display();
};

template <typename T>
MyQueue<T>::MyQueue() {
    this->input = std::stack<T>();
    this->output = std::stack<T>();
}

template <typename T>
MyQueue<T>::~MyQueue() {}

template <typename T>
MyQueue<T>::MyQueue(const MyQueue<T>& other) {
    this->input = other.input;
    this->output = other.output;
}

template <typename T>
MyQueue<T>::MyQueue(MyQueue&& other) {
    this->input = std::move(other.input);
    this->output = std::move(other.output);
}

template <typename T>
MyQueue<T>& MyQueue<T>::operator=(const MyQueue& other) {
    if (this != &other) {
        this->input = other.input;
        this->output = other.output;
    }
    return *this;
}

template <typename T>
MyQueue<T>& MyQueue<T>::operator=(MyQueue&& other) {
    if (this != &other) {
        this->input = std::move(other.input);
        this->output = std::move(other.output);
    }
    return *this;
}

template <typename T>
bool MyQueue<T>::empty() const {
    return this->input.size() == 0 && this->output.size() == 0;
}

template <typename T>
std::size_t MyQueue<T>::size() const {
    return this->input.size() + this->output.size();
}

template <typename T>
void MyQueue<T>::push(const T& item) {
    this->input.push(item);
}

template <typename T>
void MyQueue<T>::push(T&& item) {
    this->input.push(std::move(item));
}

template <typename T>
T& MyQueue<T>::front() {
    assert(!this->empty());
    // Move elements from input to end if end empty
    if (this->output.empty()) {
        this->stack_pour();
    }

    // If output still empty we have only one element in input
    if (this->output.empty()) {
        return this->input.top();
    }
    return this->output.top();
}

template <typename T>
T& MyQueue<T>::back() {
    assert(!this->empty());
    return this->input.top();
}

template <typename T>
void MyQueue<T>::pop() {
    assert(!this->empty());

    if (this->output.empty()) {
        this->stack_pour();
    }
    if (this->output.empty()) {
        this->input.pop();
    } else {
        this->output.pop();
    }
}

template <typename T>
void MyQueue<T>::clear() {
    while (!this->output.empty()) {
        this->output.pop();
    }
    while (!this->input.empty()) {
        this->input.pop();
    }
}

template <typename T>
void MyQueue<T>::display() {
    if (this->empty()) {
        std::cout << "Empty queue!" << std::endl;
        return;
    }
    std::stack<T> temp;
    // Empty queue to temp stack and then display it in reverse
    while (!this->empty()) {
        temp.push(this->front());
        this->pop();
    }
    // Put back all item into queue
    // We have to maintain one item in input stack to to provide .back() method
    std::cout << temp.top() << "->";
    this->input.push(temp.top());
    temp.pop();
    // Rest of items go to output stack for correct order
    while (!temp.empty()) {
        std::cout << temp.top() << "->";
        this->output.push(temp.top());
        temp.pop();
    }
    std::cout << std::endl;
}

template <typename T>
void MyQueue<T>::stack_pour() {
    // We have to leave one element in input to get element from .back()
    if (this->input.empty()) {
        return;
    }

    T copy = this->input.top();
    this->input.pop();

    while (!this->input.empty()) {
        this->output.push(this->input.top());
        this->input.pop();
    }
    // return last element of list
    this->input.push(copy);
}

#endif