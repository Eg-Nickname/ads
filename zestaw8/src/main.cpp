#include <cassert>
#include <cstdint>
#include <iostream>
#include <string>

#include "queue.hpp"

MyQueue<uint32_t> gen_queue() {
    auto q = MyQueue<uint32_t>();
    q.push(10);
    q.push(18);
    q.push(20);
    return q;
}

void pour_push_pop_test() {
    // Create simple queue
    auto q = MyQueue<uint32_t>();
    q.push(10);
    q.push(20);
    q.push(30);
    // Front trigers pour so we expect to get 10
    assert(q.front() == 10);
    assert(q.back() == 30);
    // we remove element to check if rest of the queue was moved correctly
    q.pop();
    assert(q.front() == 20);
    assert(q.back() == 30);
    // Adding new element to check behaviour of changed queue with new element
    q.push(40);
    // validate expected results
    assert(q.front() == 20);
    assert(q.back() == 40);
    q.pop();
    assert(q.front() == 30);
    assert(q.back() == 40);
    q.pop();
    assert(q.front() == 40);
    assert(q.back() == 40);
}

void constructor_test() {
    // Copy Constructor
    auto q1 = gen_queue();
    auto q2 = q1; // copy constructor
    assert(q1.back() == q2.back());
    q1.push(22);
    assert(q1.back() != q2.back());
    assert(q1.front() == q2.front());
    q1.pop();
    q2.pop();
    assert(q1.front() == q2.front());
    q1.pop();
    q2.pop();
    assert(q1.front() == q2.front());
    q1.pop();
    q2.pop();
    assert(q2.empty());
    assert(q1.front() == 22);

    // Move constructor
    auto q3 = gen_queue();
    auto q4 = std::move(q3);
    assert(q3.empty());
    assert(q4.front() == 10);
    q4.pop();
    assert(q4.front() == 18);
    q4.pop();
    assert(q4.front() == 20);
    q4.pop();
    assert(q4.empty());
}

void assign_op_test() {
    // Copy assign operator
    auto q1 = gen_queue();
    auto q2 = gen_queue();
    q2.push(44); // make it different then q1
    q2 = q1;
    assert(q1.back() == q2.back());
    q1.push(22);
    assert(q1.back() != q2.back());
    assert(q1.front() == q2.front());
    q1.pop();
    q2.pop();
    assert(q1.front() == q2.front());
    q1.pop();
    q2.pop();
    assert(q1.front() == q2.front());
    q1.pop();
    q2.pop();
    assert(q2.empty());
    assert(q1.front() == 22);

    // Move assign op
    auto q3 = gen_queue();
    auto q4 = gen_queue();
    q4.push(222);
    q4 = std::move(q3);

    assert(q3.empty());
    assert(q4.front() == 10);
    q4.pop();
    assert(q4.front() == 18);
    q4.pop();
    assert(q4.front() == 20);
    q4.pop();
    assert(q4.empty());
}

void empty_test() {
    auto q1 = gen_queue();
    q1.pop();
    q1.pop();
    q1.pop();
    assert(q1.empty());
    auto q2 = MyQueue<uint32_t>();
    assert(q2.empty());
}

void size_test() {
    auto q1 = gen_queue();
    assert(q1.size() == 3);
    q1.push(22);
    assert(q1.size() == 4);
    q1.pop();
    q1.pop();
    assert(q1.size() == 2);
}

void push_test() {
    auto q = MyQueue<std::string>();
    std::string s1 = "kotek";
    q.push(s1);
    assert(q.front() == "kotek");
    assert(s1 == "kotek");
    std::string s2 = "psotek";
    q.push(std::move(s2));
    assert(q.back() == "psotek");
    assert(s2 == "");
}

void front_test() {
    auto q = MyQueue<uint32_t>();
    q.push(16);
    assert(q.front() == 16);
    q.push(32);
    assert(q.front() == 16);
    q.pop();
    assert(q.front() == 32);
}

void back_test() {
    auto q = MyQueue<uint32_t>();
    q.push(16);
    assert(q.back() == 16);
    q.push(32);
    assert(q.back() == 32);
    q.push(64);
    assert(q.back() == 64);
    q.push(128);
    assert(q.back() == 128);
}

void pop_test() {
    auto q = gen_queue();
    uint32_t item = q.front();
    q.pop();
    assert(item != q.front());
    q.pop();
    q.pop();
    assert(q.empty());
}

void clear_test() {
    auto q = gen_queue();
    q.push(111);
    assert(!q.empty());
    q.clear();
    assert(q.empty());
}

auto main() -> int {
    pour_push_pop_test();
    constructor_test();
    assign_op_test();
    empty_test();
    size_test();
    push_test();
    front_test();
    back_test();
    pop_test();
    clear_test();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}