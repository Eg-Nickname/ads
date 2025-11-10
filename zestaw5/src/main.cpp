#include <cassert>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <sstream> // display tests

#include "doublelist.hpp"

/// Base list for all other tests
DoubleList<int32_t> gen_list() {
    DoubleList<int32_t> l = DoubleList<int32_t>();
    l.push_front(4);
    l.push_front(8);
    l.push_front(16);
    l.push_front(2);
    l.push_front(11);
    l.push_front(7);
    return l;
}

// Used in all other tests
void cmp_op_test() {
    auto l1 = gen_list();
    auto l2 = gen_list();

    // We generated same lists
    assert(l1 == l2);

    l2.push_front(11);
    // Lists should be diffrent after push to only one
    assert(l1 != l2);

    l1.push_front(11);
    // Now lists have same elements and same len
    assert(l1 == l2);

    l1.push_front(12);
    l2.push_front(13);
    // Test if lists with diffrent elements but same len are not the same
    assert(l1 != l2);
}

void constructor_test() {
    auto l1 = gen_list();
    // Copy constructor
    auto l2 = l1; // copy constructor

    // Lists should be the same
    assert(l1 == l2);
    l2.push_front(11);
    assert(l1 != l2);

    // Move constructor
    auto l3 = std::move(l1);
    assert(l3 != l1);
    assert(l1.size() == 0);
}

void assign_op_test() {
    auto l1 = gen_list();
    l1.push_front(11);
    auto l2 = gen_list();
    assert(l1 != l2);
    std::size_t l1_size = l1.size();

    // Copy assignment
    l2 = l1; // copy assignment
    assert(l1 == l2);
    assert(l2.size() == l1_size);
    l2.push_front(12);
    assert(l1 != l2);

    // Move assignment
    l2 = std::move(l1);
    assert(l1.empty());
    assert(l1.size() == 0);
    assert(l2.size() == l1_size);
}

void empty_test() {
    auto l1 = gen_list();
    assert(!l1.empty());
    l1.clear();
    assert(l1.empty());
}

void front_test() {
    auto l1 = DoubleList<int32_t>();
    l1.push_front(11);
    assert(l1.front() == 11);
    l1.push_front(13);
    assert(l1.front() == 13);
}

void back_test() {
    auto l1 = DoubleList<int32_t>();
    l1.push_front(11);
    assert(l1.back() == 11);
    l1.push_front(13);
    assert(l1.back() == 11);
}

void size_test() {
    auto l1 = DoubleList<int32_t>();
    assert(l1.size() == 0);
    l1.push_front(10);
    l1.push_front(11);
    assert(l1.size() == 2);
}

void push_front_test() {
    auto l = gen_list();
    std::size_t l_len = l.size();
    l.push_front(10);
    assert(l.front() == 10);
    l.push_front(20);
    assert(l.front() == 20);
    assert(l.size() == l_len + 2);

    // Test copy push
    std::string s1 = "kotek";
    auto l3 = DoubleList<std::string>();
    l3.push_front(s1);
    assert(s1 == "kotek");
    assert(l3.front() == "kotek");

    l3.push_front(std::move(s1));
    assert(s1 == "");
    assert(l3.front() == "kotek");
}

void push_back_test() {
    auto l = gen_list();
    std::size_t l_len = l.size();
    l.push_back(10);
    assert(l.back() == 10);
    l.push_back(20);
    assert(l.back() == 20);
    assert(l.size() == l_len + 2);

    // Test copy push
    std::string s1 = "kotek";
    auto l3 = DoubleList<std::string>();
    l3.push_back(s1);
    assert(s1 == "kotek");
    assert(l3.back() == "kotek");

    l3.push_back(std::move(s1));
    assert(s1 == "");
    assert(l3.back() == "kotek");
}

void pop_front_test() {
    auto l = gen_list();
    std::size_t l_len = l.size();
    l.push_front(11);
    l.push_front(12);
    l.pop_front();
    assert(l.front() == 11);
    assert(l.size() == l_len + 1);
}

void pop_back_test() {
    auto l = gen_list();
    std::size_t l_len = l.size();
    l.push_back(11);
    l.push_back(12);
    l.pop_back();
    assert(l.back() == 11);
    assert(l.size() == l_len + 1);
}

void clear_test() {
    auto l = gen_list();
    assert(l.size() != 0);
    l.clear();
    assert(l.size() == 0);
}

void display_test() {
    auto l1 = gen_list(); // 7 - 11 - 2 - 16 - 8 - 4

    // From https://en.cppreference.com/w/cpp/io/basic_ios/rdbuf.html
    std::ostringstream local;
    auto cout_buff = std::cout.rdbuf(); // save pointer std::cout buffers
    std::cout.rdbuf(local.rdbuf());

    // DISPLAY TEXT
    l1.display();

    // Restore cout
    std::cout.rdbuf(cout_buff);

    // Check display
    assert(local.str() == "7 - 11 - 2 - 16 - 8 - 4\n");
}

void display_reversed_test() {
    auto l1 = gen_list(); // 7 - 11 - 2 - 16 - 8 - 4

    // From https://en.cppreference.com/w/cpp/io/basic_ios/rdbuf.html
    std::ostringstream local;
    auto cout_buff = std::cout.rdbuf(); // save pointer std::cout buffers
    std::cout.rdbuf(local.rdbuf());

    // DISPLAY TEXT
    l1.display_reversed();

    // Restore cout
    std::cout.rdbuf(cout_buff);

    // Check display
    assert(local.str() == "4 - 8 - 16 - 2 - 11 - 7\n");
}

void acces_op_test() {
    auto l1 = gen_list(); // 7 - 11 - 2 - 16 - 8 - 4
    // Check first
    assert(l1[0] == 7);
    // Check middle
    assert(l1[2] == 2);
    // Check end
    assert(l1[5] == 4);

    l1[0] = 0;
    l1[1] = 1;
    l1[5] = 5;

    // Check first
    assert(l1[0] == 0);
    // Check middle
    assert(l1[1] == 1);
    // Check end
    assert(l1[5] == 5);
}

void erase_test() {
    auto l1 = gen_list(); // 7 - 11 - 2 - 16 - 8 - 4
    l1.erase(1);          // remove 11
    assert(l1[0] == 7);
    assert(l1[1] == 2);
    l1.erase(4); // remove last
    assert(l1[3] == 8);
    assert(l1.size() == 4);
    l1.erase(0); // remove first
    assert(l1[0] == 2);
}

void index_test() {
    auto l1 = gen_list(); // 7 - 11 - 2 - 16 - 8 - 4
    assert(l1.index(8) == 4);
    assert(l1.index(7) == 0);
    assert(l1.index(4) == 5);
    assert(l1.index(22) == -1);
}

void insert_test() {
    auto l1 = gen_list(); // 7 - 11 - 2 - 16 - 8 - 4
    l1.insert(0, 12);
    assert(l1[0] == 12);
    l1.insert(7, 17);
    assert(l1[7] == 17);
    l1.insert(1, 19);
    assert(l1[1] == 19);
    assert(l1.size() == 9);

    // Test for empty list
    auto l2 = DoubleList<uint32_t>();
    l1.insert(0, 12);
    assert(l1[0] == 12);

    // Test copy insert
    std::string s1 = "kotek";
    auto l3 = DoubleList<std::string>();
    l3.insert(0, s1);
    assert(s1 == "kotek");
    assert(l3[0] == "kotek");

    l3.insert(0, std::move(s1));
    assert(s1 == "");
    assert(l3[0] == "kotek");

    assert(l3.size() == 2);
}

auto main() -> int {
    // cmp then used in other tests
    cmp_op_test();
    // Neeeded for copy constructor
    clear_test();
    // used in other tests
    empty_test();

    constructor_test();
    assign_op_test();
    front_test();
    back_test();
    size_test();
    push_front_test();
    push_back_test();
    pop_front_test();
    pop_back_test();
    display_test();
    display_reversed_test();
    acces_op_test();
    erase_test();
    index_test();
    insert_test();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}