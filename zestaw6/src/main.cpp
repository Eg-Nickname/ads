#include "vector_deque.hpp"
#include <cassert>
#include <iostream>
MyVecDeque<int32_t> gen_deque() {
    // User facing deque: 9 - 10 - 11 - 12 - 13
    // Internal: 11 -> 12 -> 13  0  0  0  0  9 -> 10 ->
    auto vd = MyVecDeque<int32_t>(8);
    vd.push_back(11);
    vd.push_back(12);
    vd.push_back(13);
    vd.push_front(10);
    vd.push_front(9);
    return vd;
}

void constructor_test() {
    auto vd1 = gen_deque();
    // Copy constructor
    auto vd2 = vd1;
    assert(vd1 == vd2);
    assert(vd1.size() == vd2.size());
    vd1.push_back(11);
    assert(vd1 != vd2);

    // Move constructor test
    auto vd3 = std::move(vd1);
    assert(vd3.size() != 0);
    assert(vd1.size() == 0);
}

void acces_op_test() {
    // User facing deque: 9 - 10 - 11 - 12 - 13
    // Internal: 11 -> 12 -> 13  0  0  0  0  9 -> 10 ->
    auto vd = gen_deque();
    assert(vd[0] == 9);
    assert(vd[1] == 10);
    assert(vd[2] == 11);
    assert(vd[3] == 12);
    assert(vd[4] == 13);

    auto vd4 = MyVecDeque<int32_t>(8);
    vd4.push_front(13);
    vd4.push_front(12);
    vd4.push_front(11);
    assert(vd4[0] == 11);
}
void cmp_op_test() {
    auto vd1 = gen_deque();
    auto vd2 = gen_deque();
    assert(vd1 == vd2);
    vd1.push_back(11);
    assert(vd1 != vd2);
    vd2.push_back(11);
    assert(vd1 == vd2);

    auto vd3 = MyVecDeque<int32_t>(8);
    vd3.push_back(11);
    vd3.push_back(12);
    vd3.push_back(13);
    auto vd4 = MyVecDeque<int32_t>(8);
    vd4.push_front(13);
    vd4.push_front(12);
    vd4.push_front(11);
    // vd3 and vd4 same que contents but different internal representation
    assert(vd3 == vd4);
}
void size_test() {
    auto vd = gen_deque();
    assert(vd.size() == 5);
    vd.push_back(11);
    vd.push_back(11);
    vd.push_back(11);
    vd.push_back(11);
    assert(vd.size() == 9);
    auto vd1 = MyVecDeque<int32_t>();
    assert(vd1.size() == 0);
}

void assign_op_test() {
    auto vd1 = gen_deque();
    auto vd2 = gen_deque();
    vd1.push_front(13);
    // Coppy assignment op
    vd2 = vd1;
    assert(vd1 == vd2);
    vd2.push_back(11);
    assert(vd1 != vd2);
    // Move assignment op
    vd1 = std::move(vd2);
    assert(vd2.size() == 0);
}

void empty_test() {
    auto vd = gen_deque();
    assert(!vd.empty());
    auto vd1 = MyVecDeque<int32_t>();
    assert(vd1.empty());
}

void front_test() {
    auto vd = gen_deque();
    vd.push_front(11);
    assert(vd.front() == 11);
    vd.push_front(13);
    assert(vd.front() == 13);
    vd.front() = 5;
    assert(vd.front() == 5);
}

void back_test() {
    auto vd = gen_deque();
    vd.push_back(11);
    assert(vd.back() == 11);
    vd.push_back(13);
    assert(vd.back() == 13);
    vd.back() = 5;
    assert(vd.back() == 5);
}

void push_front_test() {
    auto vd = gen_deque();
    // Move push
    vd.push_front(11);
    assert(vd.front() == 11);
    vd.push_front(13);
    assert(vd.front() == 13);
    // Explicit copy / move push
    std::string s = "kotki";
    auto vds = MyVecDeque<std::string>(4);
    vds.push_front(s);
    assert(vds.size() == 1);
    assert(s == "kotki");
    vds.push_front(std::move(s));
    assert(s == "");
    assert(vds.front() == "kotki");
}

void push_back_test() {
    auto vd = gen_deque();
    // Move push
    vd.push_back(11);
    assert(vd.back() == 11);
    vd.push_back(13);
    assert(vd.back() == 13);

    // Explicit copy / move push
    std::string s = "kotki";
    auto vds = MyVecDeque<std::string>(4);
    vds.push_back(s);
    assert(vds.size() == 1);
    assert(s == "kotki");
    vds.push_back(std::move(s));
    assert(s == "");
    assert(vds.back() == "kotki");
}

void pop_front_test() {
    auto vd = gen_deque();
    vd.push_front(11);
    vd.push_front(22);
    assert(vd.front() == 22);
    vd.pop_front();
    assert(vd.front() == 11);
}

void pop_back_test() {
    auto vd = gen_deque();
    vd.push_back(11);
    vd.push_back(22);
    assert(vd.back() == 22);
    vd.pop_back();
    assert(vd.back() == 11);
}

void clear_test() {
    auto vd = gen_deque();
    assert(!vd.empty());
    vd.clear();
    assert(vd.size() == 0);
    assert(vd.empty());
}

void display_test() {
    // TODO
}

void display_reversed_test() {
    // TODO
}

void erase_test() {
    // User facing deque: 9 - 10 - 11 - 12 - 13
    // Internal: 11 -> 12 -> 13  0  0  0  0  9 -> 10 ->
    auto vd = gen_deque();
    // Internal: 11 -> 12 -> 13  0  0  0  0  9  9 ->
    // (9 without -> is treated as non queue element)
    vd.erase(1);
    assert(vd[0] == 9);
    assert(vd[1] == 11);
    // Internal: 12 -> 13  13  0  0  0  0  9  9 ->
    vd.erase(1);
    assert(vd[0] == 9);
    assert(vd[1] == 12);
    assert(vd[2] == 13);
    assert(vd.size() == 3);
}

void index_test() {
    // User facing deque: 9 - 10 - 11 - 12 - 13
    auto vd = gen_deque();
    assert(vd.index(8) == -1);
    assert(vd.index(9) == 0);
    assert(vd.index(13) == 4);
    assert(vd.index(11) == 2);
}

void insert_test() {
    // TODO
}

auto main() -> int {
    // Used for other tests eg. ==
    acces_op_test();
    cmp_op_test();
    size_test();
    constructor_test();
    assign_op_test();
    empty_test();
    front_test();
    back_test();
    push_front_test();
    push_back_test();
    pop_front_test();
    pop_back_test();
    clear_test();
    display_test();
    display_reversed_test();
    erase_test();
    index_test();
    insert_test();

    // vecdeq.debug_print();
    auto vd = gen_deque();
    // vd.debug_print();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}