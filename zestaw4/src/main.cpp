#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>

#include "singlelist.hpp"

/// Generate simple list for reuse in tests
SingleList<int32_t> gen_list() {
    SingleList<int32_t> l = SingleList<int32_t>();
    l.push_back(4);
    l.push_back(8);
    l.push_back(16);
    l.push_back(2);
    l.push_back(11);
    l.push_back(7);

    assert(l.size() == 6);
    return l;
}

/// Test == operator uset later in tests
void cmp_test() {
    SingleList<int32_t> l1 = gen_list();
    SingleList<int32_t> l2 = gen_list();
    assert(l1 == l2);
    l1.push_back(0);
    assert(l1 != l2);
    SingleList<int32_t> l3 = SingleList<int32_t>();
    assert(l1 != l3);
}

/// Copy constructor and move constructor tests
void constructor_test() {
    // Copy constructor_test
    SingleList<int32_t> l1 = gen_list();
    SingleList<int32_t> l2 = SingleList<int32_t>(l1);
    // Lists are the same after copy constructor
    assert(l1 == l2);
    l1.push_back(0);
    // Lists are not equal after pushing element to list
    assert(l1 != l2);

    // Move constructor test
    SingleList<int32_t> l3 = SingleList<int32_t>(std::move(l1));
    assert(l1 != l3);
    assert(l1.size() == 0);
    assert(l3.size() != 0);
}

/// normal and move = operator tets
void assign_op_test() {
    // Copy assign op
    SingleList<int32_t> l1 = gen_list();
    SingleList<int32_t> l2 = l1;
    // Lists are the same after copy assign op
    assert(l1 == l2);
    l1.push_back(0);
    // Lists are not equal after push to one
    assert(l1 != l2);
    SingleList<int32_t> l3 = std::move(l2);
    assert(l3 != l2);
    assert(l2.size() == 0);

    // Added after 04-11-2025
    // Test for freeing memory
    SingleList<int32_t> l4 = gen_list();
    l4.push_back(66);
    l4 = SingleList<int32_t>();
    assert(l4.size() == 0);
}

/// Get head.value of list
void front_test() {
    SingleList<int32_t> l1 = SingleList<int32_t>();
    l1.push_back(10);
    l1.push_back(13);
    l1.push_back(15);

    assert(l1.front() == 10);

    SingleList<int32_t> l2 = SingleList<int32_t>();
    // For fixed code
    try {
        // List empty throw exception
        l2.front();
        assert(false);
    } catch (std::exception &_e) {
        assert(true);
    }
}

/// Get tail.value of list
void back_test() {
    SingleList<int32_t> l1 = gen_list();
    l1.push_back(15);

    assert(l1.back() == 15);
    SingleList<int32_t> l2 = SingleList<int32_t>();
    // For fixed code
    try {
        // List empty throw exception
        l2.back();
        assert(false);
    } catch (std::exception &_e) {
        assert(true);
    }
}

void push_back_test() {
    SingleList<int32_t> l1 = SingleList<int32_t>();
    l1.push_back(10);
    // For testing purpose we assume .back works correctly
    assert(l1.back() == 10);
    l1.push_back(22);
    assert(l1.back() == 22);
    // Check if list size was incrementeds
    assert(l1.size() == 2);

    // est for move version
    std::string str1 = "kot";
    SingleList<std::string> l2 = SingleList<std::string>();
    l2.push_back(str1); // copy push
    assert(str1 == "kot");
    std::string str2 = "kot2";
    l2.push_back(std::move(str2)); // move push
    assert(str2 == "");
    assert(l2.size() == 2);
    assert(l2.back() == "kot2");
}

void push_front_test() {
    SingleList<int32_t> l1 = SingleList<int32_t>();
    l1.push_front(10);
    // For testing purpose we assume .front works correctly
    assert(l1.front() == 10);
    l1.push_front(22);
    assert(l1.front() == 22);
    // Check if list size was incrementeds
    assert(l1.size() == 2);

    // test for move version
    std::string str1 = "kot";
    SingleList<std::string> l2 = SingleList<std::string>();
    l2.push_front(str1); // copy push
    assert(str1 == "kot");
    std::string str2 = "kot2";
    l2.push_front(std::move(str2)); // move push
    assert(str2 == "");
    assert(l2.size() == 2);
    assert(l2.front() == "kot2");
}

void pop_front_test() {
    // l1 :=  4 -> 8 -> 16 -> 2 -> 11 -> 7
    SingleList<int32_t> l1 = gen_list();
    l1.pop_front();
    assert(l1.front() == 8);
    assert(l1.size() == 5);

    l1.pop_front();
    assert(l1.front() == 16);
    assert(l1.size() == 4);
}

void pop_back_test() {
    // l1 :=  4 -> 8 -> 16 -> 2 -> 11 -> 7
    SingleList<int32_t> l1 = gen_list();
    l1.pop_back();
    assert(l1.back() == 11);
    assert(l1.size() == 5);

    l1.pop_back();
    assert(l1.back() == 2);
    assert(l1.size() == 4);
}

void clear_test() {
    SingleList<int32_t> l1 = gen_list();
    l1.clear();
    assert(l1.empty());
}

void reverse_test() {
    // l1 :=  4 -> 8 -> 16 -> 2 -> 11 -> 7
    SingleList<int32_t> l1 = gen_list();
    // l1 :=  4 <- 8 <- 16 <- 2 <- 11 <- 7
    l1.reverse();
    assert(l1[0] == 7);
    assert(l1[1] == 11);
    assert(l1[2] == 2);
    assert(l1[3] == 16);
    assert(l1[4] == 8);
    assert(l1[5] == 4);
}

void acces_op_test() {
    // l1 :=  4 -> 8 -> 16 -> 2 -> 11 -> 7
    SingleList<int32_t> l1 = gen_list();
    assert(l1[0] == 4);
    assert(l1[4] == 11);
    l1[4] = 18;
    assert(l1[4] == 18);
    assert(l1[5] == 7);

    try {
        // Out of bounds access
        l1[10];
        assert(false);
    } catch (std::exception &_e) {
        assert(true);
    }
}

void erase_test() {
    // l1 :=  4 -> 8 -> 16 -> 2 -> 11 -> 7
    SingleList<int32_t> l1 = gen_list();

    l1.erase(0); // l1 :=  8 -> 16 -> 2 -> 11 -> 7
    assert(l1.front() == 8);

    l1.erase(4); // l1 :=  8 -> 16 -> 2 -> 11
    assert(l1.back() == 11);

    l1.erase(1); // l1 :=  8 -> 2 -> 11
    assert(l1[0] == 8);
    assert(l1[1] == 2);
    assert(l1[2] == 11);
}

void index_test() {
    // l1 :=  4 -> 8 -> 16 -> 2 -> 11 -> 7
    SingleList<int32_t> l1 = gen_list();
    assert(l1.index(4) == 0);
    assert(l1.index(16) == 2);
    assert(l1.index(7) == 5);
    assert(l1.index(444) == -1);
}

void insert_test() {
    // l1 :=  4 -> 8 -> 16 -> 2 -> 11 -> 7
    SingleList<int32_t> l1 = gen_list();
    // Front insert
    l1.insert(0, 13); // l1 := 13 -> 4 -> 8 -> 16 -> 2 -> 11 -> 7
    assert(l1.front() == 13);

    // Back inset
    l1.insert(7, 18); // l1 := 13 -> 4 -> 8 -> 16 -> 2 -> 11 -> 7 -> 18
    assert(l1.back() == 18);

    // Middle insert
    l1.insert(2, 66); // l1 := 13 -> 4 -> *66*-> 8 -> 16 -> 2 -> 11 -> 7 -> 18
    assert(l1[1] == 4);
    assert(l1[2] == 66);
    assert(l1[3] == 8);

    // TODO test move and non move insert with string list
    std::string str1 = "kot";
    SingleList<std::string> l2 = SingleList<std::string>();
    l2.push_back(str1); // copy push
    l2.push_back(str1); // copy push
    l2.push_back(str1); // copy push
    assert(str1 == "kot");
    std::string str2 = "kot2";
    l2.insert(1, std::move(str2)); // move push
    assert(str2 == "");
    assert(l2[1] == "kot2");
}

auto main() -> int {
    // has to be first becouse all other tests depend on correct behaviour of
    // .push_back()
    push_back_test();
    // Needs to be second to check if we correctly added element (circular
    // depedency of push_back and back tests)
    back_test();

    cmp_test();
    constructor_test();
    assign_op_test();

    front_test();
    // Push front tests depend ond working .puhs_back and front method
    push_front_test();

    pop_front_test();
    clear_test();
    reverse_test();
    acces_op_test();
    erase_test();
    index_test();
    insert_test();

    std::cout << "Tests passed!" << std::endl;
    return 0;
}