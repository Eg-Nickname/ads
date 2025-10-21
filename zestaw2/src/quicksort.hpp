//
// Created by eg_nickname on 10/15/25.
//

#ifndef SORTING_QUICKSORT_H
#define SORTING_QUICKSORT_H

#include <algorithm>
#include <iterator>

template <typename RandomAccessIt, typename Compare>
void quick_sort(RandomAccessIt first, RandomAccessIt last, Compare cmp) {
    auto len = last - first;
    if (len > 1) {
        auto pivot_val = *(last - 1);
        auto current = first;
        for (auto it = first; it != (last - 1); ++it) {
            if (cmp(*it, pivot_val)) {
                std::iter_swap(current, it);
                current += 1;
            }
        }
        std::iter_swap(current, last - 1);
        quick_sort(first, current, cmp);
        quick_sort(++current, last, cmp);
    }
}

template <typename RandomAccessIt>
void quick_sort(RandomAccessIt first, RandomAccessIt last) {
    quick_sort(
        first, last,
        std::less<typename std::iterator_traits<RandomAccessIt>::value_type>());
}
#endif // SORTING_QUICKSORT_H