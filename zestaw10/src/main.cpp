#include <cassert>
#include <iostream>

#include "tree.hpp"

void empty_tree_test() {
    auto int_tree = BinarySearchTree<int>();
    assert(int_tree.check_bst());
    auto float_tree = BinarySearchTree<double>();
    assert(float_tree.check_bst());

    auto ulong_tree = BinarySearchTree<unsigned long>();
    assert(ulong_tree.check_bst());
}

void int_tree() {
    // Hand made correct tree
    auto root = new BSTNode<int>(20);
    auto c1 = new BSTNode<int>(10);
    auto c2 = new BSTNode<int>(30);
    root->left = c1;
    root->right = c2;
    auto c3 = new BSTNode<int>(-5);
    auto c6 = new BSTNode<int>(15);
    c1->left = c3;
    c1->right = c6;
    auto c7 = new BSTNode<int>(25);
    auto c8 = new BSTNode<int>(35);
    c2->left = c7;
    c2->right = c8;
    auto int_tree = BinarySearchTree<int>(root);
    //        |---35
    //    |---30
    //    |   |---25
    // ---20
    //    |   |---15
    //    |---10
    //    |   |----5
    assert(int_tree.check_bst());
    // Handmade incorrect trees
    c8->value = 0;
    //        |---0
    //    |---30
    //    |   |---25
    // ---20
    //    |   |---15
    //    |---10
    //    |   |----5
    assert(!int_tree.check_bst());
    // Fix tree
    c8->value = 35;
    auto c9 = new BSTNode<int>(40);
    c7->right = c9;
    //        |---35
    //    |---30
    //    |   |   |---40
    //    |   |---25
    // ---20
    //    |   |---15
    //    |---10
    //    |   |----5
    // ===============
    // 40 > 25 but it should be smaller than 30
    assert(!int_tree.check_bst());
    // fix tree
    c7->right = nullptr;
    c9->value = 18;
    c7->left = c9;
    //    |   |---35
    //    |---30
    //    |   |---25
    //    |   |   |---18
    // ---20
    //    |   |---15
    //    |---10
    //    |   |----5
    // 18 < 25 but it should be greater than 20
    assert(!int_tree.check_bst());
}

void double_tree() {
    auto root = new BSTNode<double>(20.5);
    auto c1 = new BSTNode<double>(10.3);
    auto c2 = new BSTNode<double>(30.1);
    root->left = c1;
    root->right = c2;
    auto c3 = new BSTNode<double>(-5.6);
    auto c6 = new BSTNode<double>(15.22);
    c1->left = c3;
    c1->right = c6;
    auto c7 = new BSTNode<double>(25.11);
    auto c8 = new BSTNode<double>(35.87);
    c2->left = c7;
    c2->right = c8;
    auto double_tree = BinarySearchTree<double>(root);
    //        |   |---35.87
    //    |---30.1
    //    |   |---25.11
    // ---20.5
    //    |   |---15.22
    //    |---10.3
    //    |   |----5.6
    assert(double_tree.check_bst());
    auto c9 = new BSTNode<double>(29.87);
    c8->left = c9;
    //    |   |---35.87
    //    |   |   |---29.87
    //    |---30.1
    //    |   |---25.11
    // ---20.5
    //    |   |---15.22
    //    |---10.3
    //    |   |----5.6
    // 29.87 < 35.87 but > 30.1
    assert(!double_tree.check_bst());
}

auto main() -> int {
    empty_tree_test();
    int_tree();
    double_tree();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}