#include <cassert>
#include <iostream>

#include "tree.hpp"

void empty_tree_test() {
    auto i_tree = RandomBinaryTree<int>();
    assert(i_tree.calc_total_iter() == 0);
    assert(i_tree.calc_total_rec() == 0);

    auto f_tree = RandomBinaryTree<double>();
    assert(f_tree.calc_total_iter() == 0.0);
    assert(f_tree.calc_total_rec() == 0.0);
}
void int_filled_tree() {
    auto int_tree = RandomBinaryTree<int>();
    int_tree.insert(10);
    int_tree.insert(7);
    int_tree.insert(15);
    int_tree.insert(-20);
    int_tree.insert(5);
    int_tree.insert(77);
    assert(int_tree.calc_total_iter() == 94);
    assert(int_tree.calc_total_rec() == 94);
    int_tree.insert(-100);
    assert(int_tree.calc_total_iter() == -6);
    assert(int_tree.calc_total_rec() == -6);
}
void float_filled_tree() {
    auto float_tree = RandomBinaryTree<double>();
    double sum = 0.0;
    float_tree.insert(1.37);
    sum += 1.37;
    float_tree.insert(6.22);
    sum += 6.22;
    float_tree.insert(123.53);
    sum += 123.53;
    float_tree.insert(-5.87);
    sum += -5.87;
    assert(float_tree.calc_total_iter() == sum);
    assert(float_tree.calc_total_rec() == sum);
    float_tree.insert(-222.666);
    sum += -222.666;
    assert(float_tree.calc_total_iter() == sum);
    assert(float_tree.calc_total_rec() == sum);
}

auto main() -> int {
    empty_tree_test();
    int_filled_tree();
    float_filled_tree();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}