#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <vector>

#include "mergesort.hpp"
#include "quicksort.hpp"

void test_mergesort();
void test_quicksort();

int main() {
    test_mergesort();
    test_quicksort();
    std::cout << "Sorting assertions finished without problems!" << std::endl;

    return 0;
}

void test_mergesort() {
    // No cmp merge sort with array
    std::array<int, 8> a{{6, 12, 11, -16, 32, 4, 9}};
    merge_sort(a.begin(), a.end());
    assert(std::is_sorted(a.begin(), a.end()));

    // Custom cmp merge sort
    std::vector<int> v2 = std::vector({5, 4, 2, 1, 8, 5, 9, 16, -6});
    auto cmp1 = [](const int lhs, const int rhs) { return lhs < rhs; };
    merge_sort(v2.begin(), v2.end(), cmp1);
    assert(std::is_sorted(v2.begin(), v2.end(), cmp1));

    // Custom cmp merge sort  2
    std::vector<int> v3 = std::vector({15, 3, 28, 10, 5, 9, 16, -6});
    auto cmp2 = [](const int lhs, const int rhs) { return lhs > rhs; };
    merge_sort(v3.begin(), v3.end(), cmp2);
    assert(std::is_sorted(v3.begin(), v3.end(), cmp2));
}

void test_quicksort() {
    // No cmp quick sort with array
    std::array<int, 8> a{{6, 12, 11, -16, 32, 4, 9}};
    quick_sort(a.begin(), a.end());
    assert(std::is_sorted(a.begin(), a.end()));

    // Custom cmp quick sort
    std::vector<int> v2 = std::vector({5, 4, 2, 1, 8, 5, 9, 16, -6});
    auto cmp1 = [](const int lhs, const int rhs) { return lhs < rhs; };
    quick_sort(v2.begin(), v2.end(), cmp1);
    assert(std::is_sorted(v2.begin(), v2.end(), cmp1));

    // Custom cmp quick sort  2
    std::vector<int> v3 = std::vector({15, 3, 28, 10, 5, 9, 16, -6});
    auto cmp2 = [](const int lhs, const int rhs) { return lhs > rhs; };
    quick_sort(v3.begin(), v3.end(), cmp2);
    assert(std::is_sorted(v3.begin(), v3.end(), cmp2));
}