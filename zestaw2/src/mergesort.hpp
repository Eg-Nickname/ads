
// Created by eg_nickname on 10/15/25.
//

#ifndef SORTING_MERGESORT_H
#define SORTING_MERGESORT_H

#include <iterator>

template <typename RandomAccessIt, typename Compare>
void merge_sort(RandomAccessIt first, RandomAccessIt last, Compare cmp) {
    std::size_t len = last - first;

    if (len > 1) {
        std::size_t mid = len / 2;
        merge_sort(first, first + mid, cmp);
        merge_sort(first + mid, last, cmp);
        inplace_merge(first, first + mid, last, cmp);
    }
}

template <typename RandomAccessIt>
void merge_sort(RandomAccessIt first, RandomAccessIt last) {
    merge_sort(
        first, last,
        std::less<typename std::iterator_traits<RandomAccessIt>::value_type>());
}

#endif // SORTING_MERGESORT_H