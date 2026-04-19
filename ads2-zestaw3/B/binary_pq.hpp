#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>

#ifndef BINARY_PQ_HPP

class BinaryPqTests;

template <typename T, typename CMP>
class BinaryPq {
    friend BinaryPqTests;
    std::vector<T> heap{};
    CMP cmp_fn;

    public:
    BinaryPq(CMP fn) : cmp_fn(fn) {}
    void insert(T e);
    T pop();

    void display() {
        for (auto& e : heap) {
            std::cout << e << ",";
        }
    }

    bool empty() { return this->heap.empty(); }
    size_t size() { return this->heap.size(); }
};

template <typename T, typename CMP>
void BinaryPq<T, CMP>::insert(T e) {
    heap.push_back(e);

    size_t pos = heap.size() - 1;
    while (true) {
        if (pos == 0) {
            break;
        }

        size_t parent = (pos - 1) / 2;

        if (cmp_fn(heap[parent], heap[pos])) {
            std::swap(heap[parent], heap[pos]);
        } else {
            break;
        }
        pos = parent;
    }
}

template <typename T, typename CMP>
T BinaryPq<T, CMP>::pop() {
    if (heap.size() == 0) {
        throw std::out_of_range("Queue empty");
    }

    std::swap(this->heap[0], this->heap.back());
    T ret = heap.back();
    heap.pop_back();

    size_t pos = 0;
    while (true) {
        size_t lhs = pos * 2 + 1;
        size_t rhs = pos * 2 + 2;

        if (rhs >= heap.size()) {
            if (lhs < heap.size() && !cmp_fn(heap[lhs], heap[pos])) {
                std::swap(heap[lhs], heap[pos]);
            }
            break;
        }
        // We are at the end
        // Get smaller priority child
        if (!cmp_fn(heap[lhs], heap[rhs])) {
            std::swap(heap[lhs], heap[pos]);
            pos = lhs;
        } else {
            std::swap(heap[rhs], heap[pos]);
            pos = rhs;
        }
    }

    return ret;
}

#endif