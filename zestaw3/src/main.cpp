#include "arraylist.hpp"
#include <cassert>
#include <exception>
#include <iostream>

/// Test [] operator
void acces_op_test() {
    ArrayList<int> l = ArrayList<int>(4);
    l.push_back(4);
    l.push_back(8);
    l.push_back(16);
    // Normal acces
    assert(l[0] == 4);
    // Trying to acces out of bounds
    try {
        assert(l[4] == 0);
        // Code should trhow excception acces_out of bounds
        assert(false);
    } catch (std::exception &_e) {
        // If we are here we catched out of bounds exception
        assert(true);
    }
    // Assigning with []
    l[0] = 12;
    assert(l[0] == 12);

    // out of bounds assigment
    try {
        l[4] = 0;
        // Code should trhow excception acces_out of bounds
        assert(false);
    } catch (std::exception &_e) {
        // If we are here we catched out of bounds exception
        assert(true);
    }
}

/// Test .push_back() function
void push_back_test() {
    ArrayList<int> l = ArrayList<int>(8);
    // Pushingelements
    l.push_back(10);
    l.push_back(11);
    l.push_back(12);
    // List shouldnt be empty after inserting
    assert(!l.empty());
    // List should contain 3 elements
    assert(l.size() == 3);
    // List should have 12 at index []
    assert(l[2] == 12);

    // TEST push_back && variant
    ArrayList<std::string> l2 = ArrayList<std::string>(3);
    std::string s = std::string("kot");
    // string is coppied
    l2.push_back(s);
    assert(s == "kot");

    // string s is moved
    l2.push_back(std::move(s));
    assert(s == "");
}

/// Test constructors copy and move
void constructor_test() {
    ArrayList<int> l1 = ArrayList<int>(8);
    // Pushingelements
    l1.push_back(10);
    l1.push_back(11);
    l1.push_back(12);
    // Copy constructor
    ArrayList<int> l2 = l1;
    // List should be identical
    assert(l1 == l2);
    l1.push_back(14); // We change only l1 and l2 should remain unchanged
    assert(l1 != l2);

    // Test move constructor
    ArrayList<int> l3 = std::move(l2);
    // Now l3 should have elements of l2 and l2 should be discarded
    assert(l3[0] == 10); // just chceck for 1st element
    assert(l2.empty());  // l2 should be empty after move
}

/// Test clearing of elements
void clear_test() {
    ArrayList<int> l1 = ArrayList<int>(8);
    // Pushingelements
    l1.push_back(10);
    l1.push_back(11);
    l1.push_back(12);
    // Check if we placed elements in list
    assert(!l1.empty());
    l1.clear();
    // List should be empty after clear
    assert(l1.empty());
}

/// Test = operator
void assign_op_test() {
    ArrayList<int> l1 = ArrayList<int>(8);
    // Pushingelements
    l1.push_back(10);
    l1.push_back(11);
    l1.push_back(12);
    // Copy constructor
    ArrayList<int> l2 = ArrayList<int>(8);
    l2 = l1;
    // l1 and l2 should be equal after = op
    assert(l1 == l2);
    // After = move op l1 should be empty and lists are not equal
    l2 = std::move(l1);
    assert(l1 != l2);
    assert(l1.empty());
}

/// Test .front() and .back() functions
void front_back_test() {
    ArrayList<int> l1 = ArrayList<int>(8);
    try {
        l1.front();
        // Function should throw exception on empty list
        assert(false);
    } catch (std::exception &_e) {
        assert(true);
    }

    try {
        l1.back();
        // Function should throw exception on empty list
        assert(false);
    } catch (std::exception &_e) {
        assert(true);
    }

    // Pushing elements
    l1.push_back(10);
    l1.push_back(11);
    l1.push_back(12);

    assert(l1.front() == 10);
    l1.front() = 15;
    assert(l1.front() == 15);
    assert(l1.back() == 12);
    l1.back() = 18;
    assert(l1.back() == 18);
}

void push_front_test() {
    ArrayList<int> l1 = ArrayList<int>(8);
    l1.push_back(1);
    l1.push_back(2);
    l1.push_back(3);
    ArrayList<int> l2 = ArrayList<int>(8);
    l2.push_front(3);
    l2.push_front(2);
    l2.push_front(1);

    assert(l1 == l2);
    l2.push_front(4);
    assert(l2[0] == 4);

    ArrayList<std::string> l3 = ArrayList<std::string>(8);
    std::string s1 = "kot";
    l3.push_front(s1);
    l3.push_front(s1);
    // s1 unchanged with normal push
    assert(s1 == "kot");
    s1 += "2";
    // s1 move push vetsion
    l3.push_front(std::move(s1));
    assert(s1 == "");
    assert(l3[0] == "kot2");
}

/// Test .pop_front() .pop_back()
void pop_test() {
    ArrayList<int> l = ArrayList<int>(8);
    l.push_back(4);
    l.push_back(8);
    l.push_back(16);
    l.push_back(32);
    l.push_back(64);

    assert(l[0] == 4);
    l.pop_front();
    assert(l[0] == 8);
    assert(l.back() == 64);

    l.pop_back();
    assert(l.back() == 32);
    assert(l[0] == 8);
}

/// Test sorting list
void sort_test() {
    ArrayList<int> l = ArrayList<int>(8);
    l.push_back(16);
    l.push_back(8);
    l.push_back(64);
    l.push_back(32);
    l.push_back(4);

    l.sort();
    assert(l[0] == 4);
    assert(l[1] == 8);
    assert(l[2] == 16);
    assert(l[3] == 32);
    assert(l[4] == 64);
}

/// Test reversing list
void reverse_test() {
    ArrayList<int> l1 = ArrayList<int>(8);
    l1.push_back(10);
    l1.push_back(14);
    l1.push_back(5);
    l1.push_back(66);
    l1.push_back(1);
    l1.push_back(3);
    l1.push_back(12);
    l1.reverse();
    assert(l1[0] == 12);
    assert(l1[1] == 3);
    assert(l1[2] == 1);
    assert(l1[3] == 66);
    assert(l1[4] == 5);
    assert(l1[5] == 14);
    assert(l1[6] == 10);
}

/// Test erasing element
void erase_test() {
    ArrayList<int> l1 = ArrayList<int>(8);
    l1.push_back(10);
    l1.push_back(14);
    l1.push_back(5);
    l1.push_back(66);
    l1.push_back(1);
    l1.push_back(3);
    l1.push_back(12);
    auto len = l1.size();
    l1.erase(10);
    // We didnt erase any element
    assert(len == l1.size());

    // remove l1[1] = 14
    l1.erase(1);
    assert(len - 1 == l1.size());
    // All elements moved one to left
    assert(l1[1] == 5);
}

/// Test index function
void index_test() {
    ArrayList<int> l1 = ArrayList<int>(8);
    l1.push_back(10);
    l1.push_back(14);
    l1.push_back(5);
    l1.push_back(66);
    l1.push_back(1);
    l1.push_back(3);
    l1.push_back(12);

    // No item with this value
    assert(l1.index(333) == -1);
    // Corect value pos
    assert(l1.index(12) == 6);
    assert(l1.index(14) == 1);
    assert(l1.index(66) == 3);
}

/// Test inserting item at pos
void insert_test() {
    ArrayList<int> l1 = ArrayList<int>(5);
    l1.push_back(10);
    l1.push_back(3);
    l1.push_back(12);
    // Front insertion
    l1.insert(0, 77);
    assert(l1[0] == 77);
    // Back insertion
    l1.insert(4, 88);
    assert(l1[4] == 88);
    l1.insert(2, 99);
    // Check if all elements are preserved and on correct positions
    assert(l1[0] == 77);
    assert(l1[1] == 10);
    assert(l1[2] == 99);
    assert(l1[3] == 3);
    assert(l1[4] == 12);
    assert(l1[5] == 88);

    try {
        l1.insert(100, 22);
        // Index ut of bounds throw exception
        assert(false);
    } catch (std::exception &_e) {
        assert(true);
    }
    try {
        l1.insert(2, 22);
        // List full throw exception
        assert(false);
    } catch (std::exception &_e) {
        assert(true);
    }

    // Test insert with move semantics
    ArrayList<std::string> l2 = ArrayList<std::string>(8);
    l2.push_back("kot1");
    l2.push_back("kot2");
    l2.push_back("kot3");
    std::string s = "pies";
    l2.insert(1, std::move(s));
    assert(s == "");
    assert(l2[1] == "pies");
}

auto main() -> int {
    acces_op_test();
    push_back_test();
    constructor_test();
    clear_test();
    assign_op_test();
    front_back_test();
    pop_test();
    sort_test();
    reverse_test();
    erase_test();
    index_test();

    // SOME OTHER THINGS
    ArrayList<int> l = ArrayList<int>(10);
    l.push_back(10);
    l.push_back(11);
    l.push_back(12);
    // std::cout << l << std::endl;
    ArrayList<int> l2 = l;
    l.push_back(13);
    // l2.push_back(14);
    // std::cout << l << std::endl;
    // std::cout << l2 << std::endl;

    return 0;
}
